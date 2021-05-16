#include "minishell.h"
#define COLOR_PROMPT	"\033[1;34YOUR-OWN-BASH-$ \033[0m"

void			ctrl_d(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

void			signal_reset(int sig_num)
{
	(void)sig_num;
}

void			sighandler_execve(int status)
{
	if (status == SIGINT)
		write(1, "\n", 1);
	if (status == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	g_exit_status = status + 128;
}

void			sighandler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 1;
		write(1, "\b\b  \n", 5);
		write(1, COLOR_PROMPT, 23);
	}
	if (signum == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}
