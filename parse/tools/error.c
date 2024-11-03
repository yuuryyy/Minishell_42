/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahil <sahil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:45:51 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 06:03:20 by sahil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	(void)content;
	content = NULL;
}

void	put_built_err(char *built, char *name, char *err)
{
	ft_putstr_fd("minionshell: "RED, 2);
	ft_putstr_fd(built, 2);
	ft_putstr_fd(RESET, 2);
	if (name)
		ft_putstr_fd(name, 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
	exit_code(EXIT_FAILURE, EDIT);
}

void	put_error(char *msg, char *name)
{
	ft_putstr_fd("minionshell: "RED, 2);
	if (name)
		ft_putstr_fd(name, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n"RESET, 2);
	if (ft_strncmp(msg, SYNTAX, 13) == 0)
		exit_code(SYNTAX_ERROR, EDIT);
	else if (ft_strncmp(msg, NOTFOUNDMSG, 24) == 0)
		exit_code(BINARY_ERROR, EDIT);
	else
		exit_code(EXIT_FAILURE, EDIT);
}

bool	syntax_check(t_args *cmdline)
{
	t_token	*current;
	t_token	*next;

	current = cmdline->tokens;
	while (current)
	{
		next = current->next;
		if (current->type == redout && current->next
			&& current->next->type == piipe && current->space == false)
		{
			current->next = next->next;
			free (next->content);
			free(next);
			next = current->next;
		}
		if ((current->type < 5 && (!next || next->type < piipe))
			|| (current->type == piipe && (current == cmdline->tokens
					|| !next || next->type == piipe)))
			return (false);
		current = current->next;
	}
	return (true);
}

void	free_current_cmdline(t_args *cmdline)
{
	if (!cmdline)
		return ;
	free(cmdline->line);
	cmdline->line = NULL;
	free_table(&cmdline->table);
	cmdline->table = NULL;
	free_tokens(&cmdline->tokens);
	cmdline->tokens = NULL;
}
