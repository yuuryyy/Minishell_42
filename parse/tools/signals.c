/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:59:18 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/04 04:24:02 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	if (waitpid(0, NULL, WNOHANG))
	{
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		exit_code(1, EDIT);
	}
	else
		write(STDOUT_FILENO, "\n", 1);
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigquit_handler(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
	exit_code(1, EDIT);
}
