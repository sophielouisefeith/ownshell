/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:18 by sfeith        #+#    #+#                 */
/*   Updated: 2021/05/15 20:52:12 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/wait.h>


/* when using pipes or redirections you run two programmes therefore we nee to make use 
of a parent and a child */

/*Omdat beide processen dezelfde programmacode gebruiken, namelijk die van
 het originele proces dat de fork uitvoerde, moet deze programmacode zowel 
 de functionaliteit van het ouderproces als die van het kindproces bevatten. 
 Welke van de twee uitgevoerd moet worden, wordt bepaald aan de hand van de returnwaarde 
 van fork(): in het kindproces geeft fork() de waarde 0 terug als returnwaarde en in het ouderproces 
 de PID van het nieuw gecreëerde proces (deze is altijd groter dan 0: het procesid 0 is gereserveerd 
 voor het speciale init-proces dat tijdens het opstarten van het systeem gecreëerd wordt).

If return 	 0 		het is gelukt met het creeren van een child process/
If return	 -1 		het is niet gelukt met het creeren van een child process.
If return	 + 		fork() returns a positive value, the process ID of the child process, to the parent. The returned process ID is of type pid_t defined in sys/types.h. Normally, the process ID is an integer. Moreover, a process can use function getpid() to retrieve the process ID assigned to this process.
PID = PROCESS ID ;)
*/

static void		invoke_another_program(t_command **command, t_env **envb)
{
	int			pid;
	int			status;
	char		**array;

	printf("forkchild\n");
	signal(SIGINT, signal_reset);
	signal(SIGQUIT, signal_reset);
	array = env_ll_to_array(*envb);
	pid = fork();
	if (pid == -1)
		write(1, strerror(errno), ft_strlen(strerror(errno)));
	if (pid == 0)
	{
		printf("forkchild\n");
		execve((*command)->array[0], (*command)->array, array);
		errno_error((*command)->array[0], *command);
		exit(g_exit_status);
	}
	if (pid != 0)
	{
		printf("forkchild\n");
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			sighandler_execve(WTERMSIG(status));
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		free_array(array);
	}
}

/* decide which processes to run */
void			builtin_another_program(t_command **command, t_env **envb)
{
	if ((*command)->builtin == builtin_no || (*command)->builtin == executable)
	{
		printf("builtin antother programm/n");
		invoke_another_program(command, envb);
	}
	if ((*command)->builtin != builtin_no_com && (*command)->builtin !=
			builtin_no && (*command)->builtin != executable)
		execute_builtin(command, envb);
}

static void		determine_fdout(t_command **command, t_execute **exe,
									t_env **envb, int i)
{
	if (i == (*exe)->len_list - 1)
		(*exe)->fdout = fill_fdout((*command)->output, (*exe)->tmpout);
	else if ((*command)->sem && (*command)->output)
	{
		execute_output(command, exe, envb);
		(*exe)->fdout = dup((*exe)->tmpout);
	}
	else if ((*command)->pipe_after)
	{
		if ((*command)->pipe_after && (*command)->output)
			execute_output(command, exe, envb);
		pipe((*exe)->fdpipe);
		(*exe)->fdout = (*exe)->fdpipe[1];
		(*exe)->fdin = (*exe)->fdpipe[0];
	}
	else
		(*exe)->fdout = dup((*exe)->tmpout);
	dup2((*exe)->fdout, 1);
	close((*exe)->fdout);
}

static int		determine_fdin(t_command *command, t_execute **exe)
{
	if (command->input)
	{
		(*exe)->fdin = open(command->input->str_input, O_RDONLY);
		if ((*exe)->fdin == -1)
		{
			errno = ENOENT;
			return (errno_error(command->input->str_input, command));
		}
	}
	dup2((*exe)->fdin, 0);
	close((*exe)->fdin);
	return (0);
}



/* execute 
1. malloc check
2. loop through the command list

 */
void			*execute(t_command **command, t_env **envb)
{
	t_execute	*exe;
	int			res;

	initialise_execute(*command, &exe);
	while (exe->i < exe->len_list)
	{
		complete_path(command, *envb);
		res = determine_fdin(*command, &exe);
		if (res == 3)
			return (clean_exit_execute(&exe));
		check_specials(command, *envb);
		if (g_own_exit != 999 && (*command)->builtin == 0 && (*command)->array)
			error_command((*command)->array[0], 1, *command);
		else
			g_own_exit = 0;
		determine_fdout(command, &exe, envb, exe->i);
		if (!(((*command)->sem || (*command)->pipe_after) &&
			(*command)->output))
			builtin_another_program(command, envb);
		if ((*command)->sem)
			exe->fdin = dup(exe->tmpin);
		*command = (*command)->next_command;
		exe->i++;
	}
	return (clean_exit_execute(&exe));
}
