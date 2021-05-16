
/* this functions write down the values of env 
*/

#include "minishell.h"

/* in the function executor we saved the
 env list in our envb struct
 We only have to get the data out ot the linked list and write it down
 */


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
		/* go next in your linked list */
		envb = envb->next;
	}
	return (ret);
}
