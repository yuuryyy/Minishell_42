/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:02:23 by youssra           #+#    #+#             */
/*   Updated: 2024/07/21 05:25:52 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	environment(char **envp, t_args *cmd_line)
{
	t_list	*node;
	t_list	*prev;
	int		i;
	char	*str;
	char	**pathh;

	str = getenv("PATH");
	pathh = ft_split(str, ':');
	prev = NULL;
	cmd_line->path = pathh;
	i  = 0;
	while (envp[i])
	{
		node = ft_lstnew(envp[i]);
		node->previous = prev;
		prev = node;
		ft_lstadd_back(&cmd_line->env, node);
		i++;
	}
}

void	free_array(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_struct(t_args *cmd_line)
{
	if (cmd_line->line)
		free(cmd_line->line);
	// if (cmd_line->commands)
	// 	ft_lstclear(&cmd_line->commands, );
	// if (cmd_line->env)
	// 	ft_lstclear(&cmd_line->env);
	if (cmd_line->path)
		free_array(cmd_line->path);
}

void	syntax_error(t_args	*cmd_line,char *line)
{
	ft_putstr_fd("bash: parse error\n", 2);
	free(line);
	cmd_line->exit_code = 1;
}

int	replace_literal_token(t_args *cmd_line, char *line)
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
				syntax_error(cmd_line, line);
				return (0);
			}
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
			{
				if (line[i] == '<')
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
				syntax_error(cmd_line, line);
				return (0);
			}
		}
		i++;
	}
	return (1);
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
