

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	c1;

	i = 0;
	c1 = c;
	while (s[i] != '\0')
		i++;
	if (c1 == '\0')
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == c1)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
