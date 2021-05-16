#include "minishell.h"
#include "../libft/get_next_line/get_next_line.h"
#include <signal.h>
#define COLOR_PROMPT	"YOUR-OWN-BASH-"
						


/* 
1.lexer -> sort the input into a linked list saved in a struct.
2.Parser -> Gives value to input
3.Execute -> excutes the value according to set rules

 */
void			lexer_parser_executer(char *line, t_env **envb)
{

	t_lexer		*sort;
	t_lexer		*sort_copy;
	t_command	*command;
	t_command	*command_copy;
	int			pipe_status;

	pipe_status = 0;
	sort = NULL;
	command = NULL;
	
	
	lexer(&sort, line);
	sort_copy = sort;
	printf("pipe status[%d]\n", pipe_status);
	printf("g_own_exit[%d]\n", g_own_exit);
	printf("g_own_exit[%d]\n", g_own_exit);
	while (sort && g_own_exit != 258 && g_own_exit != 3)
	{
		pipe_status = parser(&sort, &command, pipe_status);
		printf("parser pipe status[%d]\n", pipe_status);
		/* go to next node */
		if (sort)
			sort = sort->next_sort;
	}
	command_copy = command;
	free_list_lexer(&sort_copy);
	if (g_own_exit == 0)
		execute(&command, envb);
	free_list_parser(&command_copy);
}

/* here we check if we used a ctrl-c or ctrl-d if not we write our prompt */
static void		prep_start(void)
{
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	write(1, COLOR_PROMPT, 15);
}

/* Start building minishell 
env = environment variables
read input
check Signals*/
int				main(int argc, char **argv, char **env)
{
	
	t_env		*envb;
	char		*line;
	int			ret;

	ret = 1;
	/* we save the environment variables in a struct which we cal envb */
	envb = save_env(env);
	(void)argc;
	(void)argv;
	/* depening on the return value of get_next_line we loop through ret 
	we break this loop with an exit status or an ctrl-d */
	while (ret > 0)
	{
		prep_start();
		/* we will read the input */
		ret = get_next_line(0, &line);
		if (ret == 0)
			ctrl_d();
		if (ret == -1)
			set_exit_status();
		if (line[0] != '\0')
			lexer_parser_executer(line, &envb);
		g_own_exit = 0;
		free(line);
		line = NULL;
	}
	/* here we free the entire linked list of envb */
	free_env(envb);
	
	return (0);
}
