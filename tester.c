#include "minishell.h"

/*

** Changelog:
	- Toegevoegd:
	copy_output en copy_input
*/

void            tester(t_lexer *sort, t_command *command)
{
    // LEXER TESTER
    printf("--------------------LEXER------------------------------:\n");
	while (sort)
	{
		printf("node-str = [%s], token_general = [%d]\n", sort->str, sort->token[token_general]);
		sort = sort->next_sort;	
	 }
	
//PARSER TESTER
	t_output	*copy_output;
	t_input		*copy_input;
	int 		n;

	copy_output = command->output;
	copy_input = command->input;
	while (command)
	{
		n = 0;
        printf("--------------------PARSER------------------------------:\n");
		printf("--------------------start Node------------------------------:\n");
		printf("node---builtin = [%d]\n", command->builtin);
    	printf("node---pipe before[%d]\n", command->pipe_before);
		printf("node---pipe after[%d]\n", command->pipe_after);
    	printf("node---sem[%d]\n", command->sem);
		while (copy_output)
		{
			printf("node---str_output[%s], token = [%d]\n", copy_output->str_output, copy_output->token);
			copy_output = copy_output->next_output;
		}
		while (copy_input)
		{
			printf("node---str_intput[%s]\n", copy_input->str_input);
			copy_input = copy_input->next_input;
		}
		if (command->array)
		{
			while (command->array[n])
			{
				printf("node-str[%d] = [%s]\n", n, command->array[n]);
			n++;
		}
		}
		printf("--------------------End Node------------------------:\n");
        printf("------------------------------------------------------:\n");
        printf("------------------------------------------------------:\n");
        printf("------------------------------------------------------:\n");

		command = command->next_command;
	}
}

