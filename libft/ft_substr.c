/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 13:15:30 by sfeith        #+#    #+#                 */
/*   Updated: 2021/05/11 13:15:31 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	strlen_s;

	i = 0;
	if (!s)
		return (NULL);
	strlen_s = ft_strlen(s);
	if (start > strlen_s)
		return (ft_strdup(""));
	if (strlen_s - start < len)
		len = strlen_s - start;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len && start < strlen_s)
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}
