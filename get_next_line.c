#include "get_next_line.h"

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

// #include <stdlib.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <fcntl.h>
// #include <string.h>

// int	main(void)
// {
// 	int	fd;
//     unsigned int i;
//     char *string;

//     fd = open("test.txt", O_RDONLY);
//     if (fd == -1) {
// 		printf("Error! Could not open file\n");
// 		exit(-1);
// 	}
//     string = get_next_line(fd);
// 	printf("%s", string);
// 	string = get_next_line(fd);
// 	printf("%s", string);
// 	string = get_next_line(fd);
// 	printf("%s", string);
// 	string = get_next_line(fd);
// 	printf("%s", string);
// 	string = get_next_line(fd);
// 	printf("%s", string);
// 	string = get_next_line(fd);
// 	printf("%s", string);
// }