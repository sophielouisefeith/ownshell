#include "minishell.h"

char			*tmp_tolower(char *str)
{
	char		*tmp;
	int			i;

	i = 0;
	tmp = ft_strdup(str);
	while (str[i] != '\0')
	{
		tmp[i] = ft_tolower(str[i]);
		i++;
	}
	return (tmp);
}
