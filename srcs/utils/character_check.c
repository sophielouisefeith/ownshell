/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   character_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 15:03:03 by sfeith        #+#    #+#                 */
/*   Updated: 2021/05/11 15:04:44 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*\t horizontal tab
  \n new line
  \v vertical tab
  \f new page
  \r carriage return

 */

int				is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
			|| c == ' ')
		return (1);
	return (0);
}

int				is_single_quote(char c)
{
	if (c == '\'')
		return (1);
	else
		return (0);
}

int				is_double_quote(char c)
{
	if (c == '\"')
		return (1);
	else
		return (0);
}

int				is_backslash(char c)
{
	if (c == '\\')
		return (1);
	else
		return (0);
}
