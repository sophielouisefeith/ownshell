

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	c;
	size_t	i;

	c = 0;
	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (len > c && haystack[c])
	{
		while (needle[i] == haystack[c + i] && needle[i] && c + i < len)
		{
			i++;
			if (needle[i] == '\0')
				return ((char *)haystack + c);
		}
		i = 0;
		c++;
	}
	return (NULL);
}
