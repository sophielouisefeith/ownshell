

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char const *s1a;
	unsigned char const *s2a;
	size_t				i;

	s1a = s1;
	s2a = s2;
	i = 0;
	while (i < n)
	{
		if (s1a[i] != s2a[i])
			return (s1a[i] - s2a[i]);
		i++;
	}
	return (0);
}
