

#include <unistd.h>
#include "libft.h"

void		ft_putstr(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
}
