/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:02:23 by youssra           #+#    #+#             */
/*   Updated: 2024/07/23 06:23:08 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(char *line)
{
	ft_putstr_fd("bash: syntax error\n", 2);
	free(line);
}

int	replace_literal_token(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
			{
				if (line[i] == '<')
					line[i] = IN;
				else if (line[i] == ' ')
					line[i] = SPACE;
				else if (line[i] == '>')
					line[i] = OUT;
				else if (line[i] == '|')
					line[i] = PIPE;
				else if (line[i] == '\'')
					line[i] = SQ;
				i++;
			}
			if (!line[i])
			{
				syntax_error( line);
				return (0);
			}
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
			{
				if (line[i] == ' ')
					line[i] = SPACE;
				else if (line[i] == '<')
					line[i] = IN;
				else if (line[i] == '>')
					line[i] = OUT;
				else if (line[i] == '|')
					line[i] = PIPE;
				else if (line[i] == '$')
					line[i] = DS;
				else if (line[i] == '\"')
					line[i] = DQ;
				i++;
			}
			if (!line[i])
			{
				syntax_error( line);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

// t_list	*tokenize(char *line)
// {
	
	
// }

void	seperate_tokens(t_args *cmd_line)
{
	char	*new;
	int		i;
	char	c;
	int		k;


	i = 0;
	while (cmd_line->line[i])
	{
		if (is_seperator(cmd_line->line[i]))
			cmd_line->token_num++;
		i++;
	}
	new = malloc(ft_strlen(cmd_line->line) + (cmd_line->token_num * 2) + 1);
	i = 0;
	k = 0;
	while (cmd_line->line[i])
	{
		if (is_seperator(cmd_line->line[i]))
		{
			new[k++] = ' ';
			c = cmd_line->line[i];
			while (cmd_line->line[i] && cmd_line->line[i] == c)
				new[k++] = cmd_line->line[i++];
			new[k++] = ' ';
		}
		else
			new[k++] = cmd_line->line[i++];
	}
	new[k] = '\0';
	free(cmd_line->line);
	cmd_line->line = new;
}

char	*remove_quotes(char *line)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] != '\"' && line[i] != '\'')
			len++;
		i++;
	}
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] != '\"' && line[i] != '\'')
		{
			new[len] = line[i];
			len++;
		}
		i++;
	}
	free(line);
	new[len] = '\0';
	return (new);
}


