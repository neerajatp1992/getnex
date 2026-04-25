#include "get_next_line.h"

static char	*read_buf(int fd, char *temp, char *buf)
{
	int	bytes;

	bytes = 1;
	while (!ft_strchr(temp, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(temp);
			return (NULL);
		}
		buf[bytes] = '\0';
		temp = ft_strjoin_free(temp, buf);
		if (!temp)
			return (NULL);
	}
	return (temp);
}

static char	*read_line(int fd, char *temp)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free(temp);
		return (NULL);
	}
	temp = read_buf(fd, temp, buf);
	free(buf);
	return (temp);
}

static char	*get_line(char *temp)
{
	char	*line;
	int		i;

	i = 0;
	if (!temp || !temp[0])
		return (NULL);
	while (temp[i] && temp[i] != '\n')
		i++;
	line = (char *)malloc(i + (temp[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*new_temp(char *temp)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (!temp[i])
		return (free(temp), NULL);
	i++;
	res = (char *)malloc(ft_strlen(temp) - i + 1);
	if (!res)
		return (free(temp), NULL);
	while (temp[i])
		res[j++] = temp[i++];
	res[j] = '\0';
	free(temp);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	temp = read_line(fd, temp);
	if (!temp)
		return (NULL);
	line = get_line(temp);
	temp = new_temp(temp);
	return (line);
}
