/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:41:54 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/21 18:55:23 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_opn(t_cmd_tab *cmd)
{
	int		fdin;

	if (cmd->in != NULL)
	{
		if (check_files(cmd->data, cmd->in, INPUT))
			return (1);
		fdin = open(cmd->in, O_RDONLY, 0644);
		if (fdin == -1)
			return (put_error(cmd->data, OPENMSG, NULL), 1);
		if (cmd->heredoc == false)
		{
			if (dup2(fdin, STDIN_FILENO == -1))
				return (close(fdin), put_error(cmd->data, DUP2SG, NULL), 1);
		}
		close(fdin);
	}
	if (cmd->heredoc == true)
	{
		if (dup2(cmd->fd_heredoc, STDIN_FILENO == -1))
			return (close(cmd->fd_heredoc),
				put_error(cmd->data, DUP2SG, NULL), 1);
		close(cmd->fd_heredoc);
	}
	return (0);
}

int	append_red(t_cmd_tab *cmd)
{
	int		apnd;

	if (check_files(cmd->data, cmd->append, OUTPUT))
		return (1);
	apnd = open(cmd->append, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (apnd == -1)
		return (put_error(cmd->data, OPENMSG, NULL), 1);
	if (cmd->red_out == APND)
	{
		if (dup2(apnd, STDOUT_FILENO) == -1)
			return (close(apnd), put_error(cmd->data, DUP2SG, NULL), 1);
	}
	close(apnd);
}

int	outfile_opn(t_cmd_tab *cmd)
{
	int		fdout;

	if (cmd->out != NULL)
	{
		if (check_files(cmd->data, cmd->out, OUTPUT))
			return (1);
		fdout = open(cmd->out, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fdout == -1)
			return (put_error(cmd->data, OPENMSG, NULL), 1);
		if (cmd->red_out == REDOUT)
		{
			if (dup2(fdout, STDOUT_FILENO) == -1)
				return (close(fdout), put_error(cmd->data, DUP2SG, NULL), 1);
		}
		close(fdout);
	}
	if (cmd->append != NULL)
		return (append_red(cmd));
	return (0);
}
