/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:45:51 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/25 09:15:27 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	free(content);
}

void	put_error(t_args *cmd_line, char *msg, char *name)
{
	(void) cmd_line;
	ft_putstr_fd("minionshell: "RED, 2);
	ft_putstr_fd(msg, 2);
	if (name)
		ft_putstr_fd(name, 2);
	ft_putstr_fd("\n"RESET, 2);
	g_errno = EXIT_FAILURE;
	// printf("\n\n<<%d>>\n\n", g_errno);
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
		if ((current->type < 5 && (!next || next->type < string))
			|| (current->type == piipe && (current == cmdline->tokens
					|| !next || next->type < string)))
			return (put_error(cmdline, SYNTAX, NULL), false);
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
