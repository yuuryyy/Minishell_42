/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:59:18 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/03 21:09:53 by kaafkhar         ###   ########.fr       */
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
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
