/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsbuilts3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 00:48:57 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/03 02:34:52 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(t_args *args, char *argument)
{
	char		*env_var;
	t_list		*prev;
	t_list		*current;

	prev = NULL;
	current = args->env;
	while (current)
	{
		env_var = (char *)current->content;
		if (ft_strncmp(env_var, argument, ft_strlen(argument)) == 0
			&& env_var[ft_strlen(argument)] == '=')
		{
			if (prev)
				prev->next = current->next;
			else
				args->env = current->next;
			free(current->content);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	array_len(char **str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	parse_echo_options(t_cmd_tab *table, int *i)
{
	bool	newline;
	int		j;

	newline = true;
	while (table->cmd[*i] && table->cmd[*i][0] == '-'
		&& table->cmd[*i][1] == 'n')
	{
		j = 1;
		while (table->cmd[*i][j] == 'n')
			j++;
		if (table->cmd[*i][j] == '\0')
		{
			newline = false;
			(*i)++;
		}
		else
			break ;
	}
	return (newline);
}

void	print_echo_args(t_cmd_tab *table, int i, bool newline)
{
	while (table->cmd[i])
	{
		write(STDOUT_FILENO, table->cmd[i], ft_strlen(table->cmd[i]));
		if (table->cmd[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}
