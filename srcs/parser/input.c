#include "minishell.h"

static t_input		*ll_new_node_input(char *str_input)
{
	t_input		*new;

	new = (t_input *)malloc(sizeof(t_input));
	if (!new)
		malloc_fail();
	new->str_input = str_input;
	new->next_input = NULL;
	return (new);
}

static void			ll_lstadd_back_input(t_input **input, t_input *new)
{
	t_input		*list_input;

	list_input = *input;
	if (list_input)
	{
		while (list_input->next_input)
			list_input = list_input->next_input;
		list_input->next_input = new;
	}
	else
		*input = new;
}

/* fill the input  for example file1 < hallo */ 
void				input_fill(t_lexer **sort, t_command **tmp)
{
	t_input		*tmp_input;
	char		*str;

	*sort = (*sort)->next_sort;
	str = ft_strdup((*sort)->str);
	if (str == NULL)
		malloc_fail();
	tmp_input = ll_new_node_input(str);
	ll_lstadd_back_input(&(*tmp)->input, tmp_input);
}
