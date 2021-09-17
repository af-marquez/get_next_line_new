#include "get_next_line.h"

char	*ft_get_line(char *keep)
{
	int		i;
	char	*s;

	i = 0;
	if (!keep[i])
		return (NULL);
	while (keep[i] && keep[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (keep[i] && keep[i] != '\n')
	{
		s[i] = keep[i];
		i++;
	}
	if (keep[i] == '\n')
	{
		s[i] = keep[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_keep(char *keep)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	while (keep[i] && keep[i] != '\n')
		i++;
	if (!keep[i])
	{
		free(keep);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(keep) - i + 1));
	if (!s)
		return (NULL);
	i++;
	c = 0;
	while (keep[i])
		s[c++] = keep[i++];
	s[c] = '\0';
	free(keep);
	return (s);
}

char	*ft_read_keep(int fd, char *keep)
{
	char	*buff;
	int		bytes_read;

	buff = malloc(( sizeof(char) * BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(keep, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		keep = ft_strjoin(keep, buff);
	}
	free(buff);
	return (keep);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*keep;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	keep = ft_read_keep(fd, keep);
	if (!keep)
		return (NULL);
	line = ft_get_line(keep);
	keep = ft_keep(keep);
	return (line);
}