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
