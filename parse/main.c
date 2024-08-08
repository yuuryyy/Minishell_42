/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/08 00:50:17 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	s()
{
	system("leaks minishell");
}


int g_errno = 0;

int main(int ac, char **av, char **env)
{
	t_args	cmd_line;

	// // atexit(s);
	(void)ac; (void)av;
	ft_bzero(&cmd_line, sizeof(t_args));
	environment(env, &cmd_line);
	while (42)
	{
		cmd_line.line = readline("\033[38;2;255;192;203m\033[1mminionshell^~^ \033[34m>$ \033[0m");
		process_line(&cmd_line);
		printf("%d\n", g_errno);
	}
	// t_cmd_tab *tab = cmd_line.table;
	// 	while (tab)
	// {
	// 	printf("------\narg====%s\n", tab->arg);
	// 	printf("------\nappend====%s\n", tab->append);
	// 	printf("------\nlimi====%s\n", tab->delimiter);
	// 	printf("infile====%s\n", tab->in);
	// 	printf("outfile====%s\n", tab->out);
	// 	tab = tab->next;
	// }
	free_struct(&cmd_line);
	// char *cmd[] = {"ECHO","hello    world","wiliii",  NULL};
	// if (execve("/bin/ECHO", cmd, NULL) == -1)
	// 	printf("makhdamach");
}
