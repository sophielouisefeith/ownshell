#include "minishell.h"

static int		lstsize(t_command *command)
{
	int			c;

	c = 0;
	while (command)
	{
		command = command->next_command;
		c++;
	}
	return (c);
}

int				fill_fdout(t_output *output, int tmpout)
{
	
	int			fdout;

	if (output)
	{
		while (output)
		{
			/*make a newfile  output*/
			//printf("fileoutput\n");
			if (output && output->token == token_redirection_greater)
			{
				fdout = open(output->str_output,\
				O_RDWR | O_CREAT | O_TRUNC, 0644);
				//printf("add a new file\n");
			}
			else if (output && output->token == \
			token_redirection_dgreater)
			{
				//printf("append content\n");
				fdout = open(output->str_output, \
				O_RDWR | O_CREAT | O_APPEND, 0644);   /*append we add the output to the file*/
			}
			output = output->next_output;
		}
	}
	else
		fdout = dup(tmpout);
	return (fdout);
}

void			execute_output(t_command **command, t_execute **exe,
								t_env **envb)
{
	
	(*exe)->fdout = fill_fdout((*command)->output, (*exe)->tmpout);
	dup2((*exe)->fdout, 1);
	close((*exe)->fdout);
	builtin_another_program(command, envb);
}

void			*clean_exit_execute(t_execute **exe)
{
	dup2((*exe)->tmpin, 0);
	dup2((*exe)->tmpout, 1);
	close((*exe)->tmpin);
	close((*exe)->tmpout);
	free(*exe);
	return (0);
}


/* when empty return malloc fail
*/

void			initialise_execute(t_command *command, t_execute **exe)
{
	*exe = (t_execute *)malloc(sizeof(t_execute));
	if (!(*exe))
		malloc_fail();
	(*exe)->len_list = lstsize(command);
	(*exe)->tmpin = dup(0);
	(*exe)->tmpout = dup(1);
	(*exe)->fdin = dup((*exe)->tmpin);
	(*exe)->i = 0;
}
