
#include "minishell.h"

int				env(t_env *envb)
{
	int		ret;

	ret = 0;
	while (envb)
	{
		if (envb->equal)
		{
			ret = write(1, envb->name, ft_strlen(envb->name));
			ret = write(1, "=", 1);
			ret = write(1, envb->value, ft_strlen(envb->value));
			ret = write(1, "\n", 1);
		}
		envb = envb->next;
	}
	return (ret);
}
