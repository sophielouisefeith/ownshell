/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 13:14:37 by msiemons      #+#    #+#                 */
/*   Updated: 2021/05/11 13:48:04 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env			*ll_new_node_env(char *name, char *value, int equal)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = name;
	new->equal = equal;
	new->value = value;
	new->equal = equal;
	new->next = NULL;
	return (new);
}

void			ll_lstadd_back_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = *env;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*env = new;
}

/* here we save the env list in a linked list, so we can later easily go through all the details */
t_env			*save_env(char **env)
{
	t_env		*save_env;
	t_env		*tmp;
	char		**array;
	int			y;

	save_env = NULL;
	y = 0;
	while (env[y])
	{
		array = ft_split(env[y], '=');
		tmp = ll_new_node_env(array[0], array[1], 1);
		ll_lstadd_back_env(&save_env, tmp);
		free(array);
		array = NULL;
		y++;
		
	}
	//printf("*********************** FIRST PEACH OF ENV****************** [%s]/n", env[0]);
	
	return (save_env);
}
