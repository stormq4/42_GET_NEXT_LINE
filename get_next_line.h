#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 10
# define TRUE 1
# define FALSE 0
# include <stdlib.h>

char	*get_next_line(int fd);
char 	*gnl_change_buffer(char *line, char *buffer);
void	*gnl_memmove(void *dst, const void *src, size_t len);
size_t	gnl_strlen(char *str);
// void	gnl_bzero(char *str);

#endif
