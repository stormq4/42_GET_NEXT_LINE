#include "get_next_line.h"
#include <stdlib.h>

size_t	gnl_strlen(char *str)
{
	size_t len;
	
	len = 0;
	while(str[len] != 0 && len < BUFFER_SIZE && str[len] != '\n')
		len++;
	return (len);
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
