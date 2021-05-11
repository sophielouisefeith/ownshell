/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   character_check2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 15:07:32 by sfeith        #+#    #+#                 */
/*   Updated: 2021/05/11 15:07:36 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** & and quotes are accepted characters in words.
*/

int				is_operator(char c)
{
	if (c == ';')
		return (token_semicolon);
	if (c == '|')
		return (token_pipe);
	if (c == '>')
		return (token_redirection_greater);
	if (c == '<')
		return (token_redirection_lesser);
	else
		return (0);
}

/*
** A metacharacter is a char that, when unquoted, separates words.
** It's is a whitespace, or one of the following characters:
** | & ; ( ) < >
*/

int				is_metachar(char c)
{
	if (is_whitespace(c) || is_operator(c))
		return (1);
	else
		return (0);
}
