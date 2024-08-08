/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/08 02:13:29 by ychagri          ###   ########.fr       */
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
		// printf("\nPREV EXIT == %d\n", g_errno);
		process_line(&cmd_line);
	// 	char **tab = cmd_line.table->cmd;
	// 	while (*tab)
	// {
	// 	printf("%s\n", *tab);
	// 	tab++;
	// }
		// printf("\nCURR EXIT == %d\n", g_errno);
		free(cmd_line.line);
		free_table(&cmd_line.table);
		free_tokens(&cmd_line.tokens);
	}
	free_struct(&cmd_line);
	// char *cmd[] = {"ECHO","hello    world","wiliii",  NULL};
	// if (execve("/bin/ECHO", cmd, NULL) == -1)
	// 	printf("makhdamach");
}
