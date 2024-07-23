/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:29:42 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/23 06:45:33 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	check_replace(char *c, int flag)
{
	if (*c == '<')
		*c = IN;
	else if (*c == ' ')
		*c = SPACE;
	else if (*c == '>')
		*c = OUT;
	else if (*c == '|')
			*c = PIPE;
	else if (*c == '\'' && flag == DS)
			*c = SQ;
	else if (*c == '$' && flag == SQ)
		*c = DS;
	else if (*c == '\"' && flag == SQ)
		*c = DQ;
}

void	replace_literal_token(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i++;
			if (line[i] == '\"')
			{
				while (line[i] && line[i] != '\"')
				{
					check_replace(&line[i], DQ);
					i++;
				}
			}
			else 
			{
				while (line[i] && line[i] != '\'')
				{
					check_replace(&line[i], SQ);
					i++;
				}
			}
		}
		if (!line[i])
			return(syntax_error( line));
		i++;
	}
}
