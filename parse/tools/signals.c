/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:59:18 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/01 02:50:41 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int signum)
{
    (void)signum;
	while (wait(NULL) != -1)
	{
		continue ;
	}
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	exit_code(1, EDIT);
}

void setup_signal_handlers()
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}
