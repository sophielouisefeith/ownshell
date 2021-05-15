

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *b1;

	b1 = b;
	while (len > 0)
	{
		*b1 = (unsigned char)c;
		b1++;
		len--;
	}
	return (b);
}
