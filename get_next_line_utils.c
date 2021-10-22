#include "get_next_line.h"
#include <stdlib.h>

size_t	gnl_strlen(char *str, int bool)
{
	size_t	len;

	len = 0;
	while (str[len] != 0 && len < BUFFER_SIZE && str[len] \
	!= '\n' && bool == TRUE)
		len++;
	while (str[len] != 0 && bool == FALSE)
		len++;
	return (len);
}

void	gnl_bzero(char	*str, size_t i)
{
	while (i < BUFFER_SIZE)
	{
		str[i] = 0;
		i++;
	}
}

void	*gnl_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	if (dst > src)
	{
		while (len > 0)
		{
			((char *)dst)[len - 1] = ((char *)src)[len - 1];
			len--;
		}
		return (dst);
	}
	while (len > i)
	{
		((char *)dst)[i] = ((char *) src)[i];
		i++;
	}
	return (dst);
}

char	*gnl_reindex_buf(char *buffer, char *line)
{
	size_t	i;
	char	*tmp;
	size_t	j;
	size_t	str_lenbuf;

	str_lenbuf = gnl_strlen(buffer, TRUE);
	tmp = (char *)malloc((gnl_strlen(line, FALSE) + \
	str_lenbuf + 1) * sizeof(char));
	j = 0;
	while (line[j] != '\0')
	{
		tmp[j] = line[j];
		j++;
	}
	i = 0;
	while (i < str_lenbuf + 1 && i < BUFFER_SIZE)
	{
		tmp[j + i] = buffer[i];
		i++;
	}
	gnl_memmove(buffer, buffer + i, BUFFER_SIZE - i);
	tmp[j + i] = 0;
	gnl_bzero(buffer, BUFFER_SIZE - i);
	free(line);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	size_t		line_len;

	line = malloc(sizeof(char) * 1);
	line[0] = 0;
	buffer[BUFFER_SIZE] = 0;
	if (buffer[0] != 0)
	{
		line = gnl_reindex_buf(buffer, line);
		if (line[gnl_strlen(line, FALSE) - 1] == '\n')
			return (line);
	}
	while (read(fd, buffer, BUFFER_SIZE))
	{
		line = gnl_reindex_buf(buffer, line);
		line_len = gnl_strlen(line, FALSE);
		if (line_len && line[line_len - 1] == '\n')
			return (line);
	}
	return (line);
}
