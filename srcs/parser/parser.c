
#include "minishell.h"
/* 
System call fork() is used to create processes. It takes no arguments and returns a process ID. The purpose of fork() is to create a new process, which becomes the child process of the caller. After a new child process is created, both processes will execute the next instruction following the fork() system call. Therefore, we have to distinguish the parent from the child. This can be done by testing the returned value of fork():

If fork() returns a negative value, the creation of a child process was unsuccessful.
fork() returns a zero to the newly created child process.
fork() returns a positive value, the process ID of the child process, to the parent. The returned process ID is of type pid_t defined in sys/types.h. Normally, the process ID is an integer. Moreover, a process can use function getpid() to retrieve the process ID assigned to this process.
*/

static int		redirection(t_lexer **sort, t_command **tmp)
{
	while ((*sort)->token[token_redirection])
	{
		if ((*sort)->token[token_redirection_greater])
			output_fill(sort, tmp, token_redirection_greater);
		if ((*sort)->token[token_redirection_dgreater])
			output_fill(sort, tmp, token_redirection_dgreater);
		if ((*sort)->token[token_redirection_lesser])
			input_fill(sort, tmp);
		if ((*sort)->next_sort)
			*sort = (*sort)->next_sort;
		else
			return (1);
	}
	return (0);
}

static int		general(t_lexer **sort, char **array, int *y)
{
	while (*sort && (*sort)->token[token_general])
	{
		array[*y] = ft_strdup((*sort)->str);
		if (array[*y] == NULL)
			malloc_fail();
		(*y)++;
		if ((*sort)->next_sort)
			*sort = (*sort)->next_sort;
		else
			return (1);
	}
	return (0);
}

static void		fill_pipe_and_sem(t_lexer *sort, \
t_command **tmp, int *pipe_status)
{
	if (sort && sort->token[token_semicolon])
		(*tmp)->sem = 1;
	if (*pipe_status == 1)
	{
		(*tmp)->pipe_before = 1;
		*pipe_status = 0;
	}
	if (sort && sort->token[token_pipe])
	{
		(*tmp)->pipe_after = 1;
		*pipe_status = 1;
	}
}

static void		fill_array(t_lexer **sort, t_command **tmp)
{
	int			ret;
	int			y;

	y = 0;
	while (*sort && ((*sort)->token[token_general]
				|| (*sort)->token[token_redirection]))
	{
		ret = redirection(sort, tmp);
		if (ret == 1)
			break ;
		ret = general(sort, (*tmp)->array, &y);
		if (ret == 1)
			break ;
	}
	if ((*tmp)->array != NULL)
		(*tmp)->array[y] = 0;
}

/* we receive  the link list sort with alle the information 
fill enum builtin type fill the struct of parser
*/
int				parser(t_lexer **sort, t_command **command, int pipe_status)
{
	t_command	*tmp;
	int			num_nodes;
	int			builtin;

	g_own_exit = 0;
	tmp = NULL;
	num_nodes = 0;
	builtin = check_builtin_node(sort);
	num_nodes = count_node(sort, builtin);
	tmp = ll_new_node_command(num_nodes, builtin);
	if (tmp == NULL)
		return (malloc_fail());
	fill_array(sort, &tmp);
	fill_pipe_and_sem(*sort, &tmp, &pipe_status);
	ll_lstadd_back_command(command, tmp);
	return (pipe_status);
}
