#include "minishell.h"

/* here we safe the data we collect in a linked list this linked list is saved 
in a struct */

t_lexer			*ll_new_node_lexer(char *str, int *token)
{
	t_lexer		*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
	{
		malloc_fail();
		return (NULL);
	}
	new->str = str;
	new->token = token;
	new->next_sort = NULL;
	/* show the different nodes */
	//printf("NODES[%s]\n", new->str);
	return (new);
}

void			ll_lstadd_back_lexer(t_lexer **sort, t_lexer *new)
{
	
	t_lexer		*list;

	list = *sort;
	if (list)
	{
		while (list->next_sort)
			list = list->next_sort;
		list->next_sort = new;
	}
	else
		*sort = new;
}
