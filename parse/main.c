/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/08 17:02:22 by youssra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	s()
{
	system("leaks minishell");
}

void	sig_handler(int signal)
{
	printf("\n\033[38;2;255;192;203m\033[1mminionshell^~^ \033[34m>$ \033[0m");
}


int g_errno = 0;

int main(int ac, char **av, char **env)
{
	t_args	cmd_line;

	// atexit(s);
	(void)ac; (void)av;
	signal(SIGINT, sig_handler);
	ft_bzero(&cmd_line, sizeof(t_args));
	environment(env, &cmd_line);
	while (42)
	{
		cmd_line.line = readline("\033[38;2;255;192;203m\033[1mminionshell^~^ \033[34m>$ \033[0m");
		if (cmd_line.line && *cmd_line.line)
			add_history(cmd_line.line);
		process_line(&cmd_line);
		//execution;
		free_current_cmdline(&cmd_line);
	}
	free_struct(&cmd_line);
	// char *cmd[] = {"ECHO","hello    world","wiliii",  NULL};
	// if (execve("/bin/ECHO", cmd, NULL) == -1)
	// 	printf("makhdamach");
}
