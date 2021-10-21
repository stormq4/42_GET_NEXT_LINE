#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"

// char	*gnl_concatonate(char *new_line, char *line, static char *buffer, size_t buf_len)
// {
// 	size_t	line_len;
// 	size_t	i;

// 	i = 0;
// 	line_len = gnl_strlen(line, FALSE);
// 	new_line = (char *)malloc((buf_len + line_len + 1) * sizeof(char))
// 	while (i < buf_len)
// 	{
// 		new_line[i] = line[i];
// 		i++;
// 	}
// 	i = 0;
// 	while (i < buf_len)
// 	{
// 		new_line[i + buf_len] = buffer[i];
// 		i++;
// 	}
// 	new_line[i] = 0;
// 	return (new_line);
// }

size_t	gnl_checknl(char *str)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE && str[i])
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

char	*gnl_reindex_buf(char *buffer, char *line)
{
	size_t	i;
	char	*tmp;
	size_t	j;
	size_t	str_lenbuf;

	str_lenbuf = gnl_strlen(buffer);
	tmp = (char *)malloc((gnl_strlen(line) + str_lenbuf + 1) * sizeof(char));
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
	buffer[i] = 0;
	tmp[j + i] = 0;
	printf("tmp --> %s\n --\n", tmp);
	free(line);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] ;
	char		*line;
	size_t		line_len;

	line = malloc(sizeof(char) * 1);
	line[0] = 0;
	buffer[BUFFER_SIZE] = 0;
	if (buffer[0] != 0)
	{
		line = gnl_reindex_buf(buffer, line);
		if (line[gnl_strlen(line) - 1] == '\n')
		{
			printf("test voor return waarde");
			return (line);
		}
	}
	while (read(fd, buffer, BUFFER_SIZE))
	{
		// printf("line: %s\n", line);
		// printf("buffer1: %s\n", buffer);
		// printf("buffer1: %s\n", buffer);
		line = gnl_reindex_buf(buffer, line);

		line_len = gnl_strlen(line);
		if (line_len)
			if (line[gnl_strlen(line) - 2] == '\n')
				return (line);
	}
	return (line);
}

int	main(void)
{
	int	fd;
    unsigned int i;
    char *string;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
		printf("Error! Could not open file\n");
		exit(-1);
	}
    string = get_next_line(fd);
    printf("%s", string);
}