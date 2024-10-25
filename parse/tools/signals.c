/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:59:18 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/25 14:53:10 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int signum)
{
    (void)signum;
	// if (g_errno != 123)
	// {
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_errno = 1;
	// }
	// else
	// {
	// 	rl_replace_line("", 0);
	// 	write(STDOUT_FILENO, "\n", 1);
    // 	rl_on_new_line();
	// 	g_errno = -1;
	// 	close(STDIN_FILENO);
	// }
}

void setup_signal_handlers()
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}
