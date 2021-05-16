#include "minishell.h"

/* Check if the quotantions are completed if 
not return error and set exit status  */
static void		check_quotation_complete(char quote, char *line, int *i)
{
	(*i)++;
	while (line[*i] != quote && line[*i])
	{
		if (is_backslash(line[*i]) && is_double_quote(line[(*i) + 1]) &&
				!is_backslash(line[(*i) - 1]))
			(*i)++;
		(*i)++;
	}
	if (line[*i] == quote)
		return ;
	else
	{
		/* not part means not part of the subject, we display > and 
		set the exit status therefore we would not continue once we arrive at the parser */
		not_part(line);
		g_own_exit = 3;
		g_exit_status = 1;
	}
}

static void		check_meta_and_quote(char *line, int *i)
{
	/* if no whitespace or operator meaning > etc */
	while ((!is_metachar(line[*i])) && line[*i])
	{
		/* if yes there will be qoutes and we will check if there double */
		if ((is_single_quote(line[*i]) || is_double_quote(line[*i])) &&
				line[(*i) - 1] != '\\')
			check_quotation_complete(line[*i], line, i);
		(*i)++;
	}
}

/* The input we receive would be divided in different str -> safed in the linked list lexer
uncommand printf to see the results */
static void		save_word(char *line, int *i, t_lexer **sort)
{
	t_lexer		*tmp;
	char		*str;
	int			*token;
	int			start;

	start = *i;
	token = allocate_memory_int_string(12);
	token[token_general] = 1;
	check_meta_and_quote(line, i);
	str = ft_substr(line, start, (*i - start));
	tmp = ll_new_node_lexer(str, token);
	// printf("NODES[%s]\n", tmp->str);
	/* put the filled note to the end of the list*/
	ll_lstadd_back_lexer(sort, tmp);
	
}

static void		save_operator(char *line, int *i, int type, t_lexer **sort)
{
	t_lexer		*tmp;
	char		*str;
	int			*token;


	/* we make space for token on the stack */
	token = allocate_memory_int_string(12);
	/* in the following if statements we will safe the correct data in str */
	if (type == token_redirection_greater && line[*i + 1] == '>')
	{
		(*i)++;
		token[token_redirection_dgreater] = 1;
		str = str_redirection_dgreater();
	}
	else
	{
		//echo goed > daar
		token[type] = 1;
		str = str_from_char(line[*i]);
	}
	if (type >= token_redirection_greater &&
			type <= token_redirection_dgreater)
		token[token_redirection] = check_redirections(line, *i, type);
	
	tmp = ll_new_node_lexer(str, token);
	/* depending on the above if statements we wil safe the str */
	// printf("str for new node[%s]\n", tmp->str);
	ll_lstadd_back_lexer(sort, tmp);
	(*i)++;
}

/* in the lexer we will save the input and safe it in a linked
 list which is saved in a struct */
void			lexer(t_lexer **sort, char *line)
{
	int			type;
	int			i;

	i = 0;
																									printf("*******line[%s]", line);
	while (line[i] && g_own_exit != 3) /* if there now closing "" */
	{
		/*we loop through white spaces*/
		while (is_whitespace(line[i]))
			i++;
		/*here we check the tokentype -> saved in an enum in the header file*/
		type = get_token_type(line, &i);
		/*if it's general it means we start with no token */
		if (type == token_general)
			save_word(line, &i, sort);
		/* here we check if pipes are used  
		example echo hallo | > hallo*/
		if (type >= token_pipe && type <= token_redirection_lesser)
			save_operator(line, &i, type, sort);
		type = 0;
	}
}
