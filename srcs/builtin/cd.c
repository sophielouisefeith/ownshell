
/* this following functions  simulate a working
cd from the orignal bash

note- start function on the bottom*/

#include "minishell.h"
#include <limits.h>

/* look for the old pwd and place this on 
the bottom of the env list */
static void		check_old_pwd(t_env **envb, char *old_path)
{
	t_env	*copy_env;
	t_env	*tmp;

	copy_env = *envb;
	while (copy_env)
	{
		if (!ft_strcmp("OLDPWD", copy_env->name))
		{
			free(copy_env->value);
			copy_env->value = old_path;
			return ;
		}
		copy_env = copy_env->next;
	}
	/* add to link list env */
	tmp = ll_new_node_env("OLDPWD", old_path, 1);
	if (tmp == NULL)
		malloc_fail();
	ll_lstadd_back_env(envb, tmp);
}

/* Change the current pathname with the new pathname */
static void		change_env_pwd(t_env **envb)
{
	t_env	*copy_env;
	char	*old_path;
	char	*path;

	copy_env = *envb;
	/* getcwd get's the current path name */
	path = getcwd(NULL, 0);
	if (path == NULL)
		strerror(errno);
	while (copy_env)
	{
		/* */
		if (!ft_strcmp("PWD", copy_env->name))
		{
			old_path = ft_strdup(copy_env->value);
			check_old_pwd(envb, old_path);
			free(copy_env->value);
			copy_env->value = path;
			break ;
		}
		copy_env = copy_env->next;
	}
}



static int		execute_cd_ex(t_command *command,
char *home, t_env **envb, int ret)
{
	if (!ft_strcmp(command->array[0], "~/"))
	{
		/* we set home */
		home = search_node(*envb, ft_strdup("HOME"));
		/* current directory*/
		ret = chdir(home);
		free(home);
		if (ret == -1)
			error(command);
		change_env_pwd(envb);
		return (ret);
	}
	/* fill array with current path */
	ret = chdir(command->array[0]);
	if (ret == -1)
		error(command);
	change_env_pwd(envb);
	return (ret);
}


/* 1.we read the env list and get the current value of home 
   2.wiht chdir we change the current directory with the new directory
   3.As a last stap we change the env list to make i acurate with the new path
*/
int				execute_cd(t_command *command, t_env **envb)
{
	int		ret;
	char	*home;

	ret = 0;
	home = NULL;
	if (command->array)
	{
		/* cd .. we go back*/
		return (execute_cd_ex(command, home, envb, ret));
	}
	else
	{
		/* we look for the home directory*/
		/* get out current path out of our env list */
		home = search_node(*envb, ft_strdup("HOME"));
		/*The chdir command is a system function 
		(system call) which is used to change 
		the current working directory*/
		ret = chdir(home);
		free(home);
		if (ret == -1)
			error(command);
		change_env_pwd(envb);
	}
	/* value determines if the programme runned correctly*/
	return (ret);
}
