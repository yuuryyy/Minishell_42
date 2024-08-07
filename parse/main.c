/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/08/08 00:15:27 by ychagri          ###   ########.fr       */
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
	// char	*tmp;

	// atexit(s);
	(void)ac; (void)av;
	ft_bzero(&cmd_line, sizeof(t_args));
	environment(env, &cmd_line);
	cmd_line.line = readline("\033[38;2;255;192;203m\033[1mminionshell^~^ \033[34m>$ \033[0m");
	// tmp = ft_strdup(cmd_line.line);
	// if (!words_list(tmp, &cmd_line))
	// 	printf("%d\n", g_errno);
	// free(tmp);
	// // expand_var(&cmd_line);
	// // for(int i = 0; cmd_line.path[i]; i++)
	// if (!syntax_check(&cmd_line))
	// 	exit (1);
	// command_table(&cmd_line);
	// printf("arg = %s\n", cmd_line.table->arg);
	process_line(&cmd_line);
	t_cmd_tab *tab = cmd_line.table;
		while (tab)
	{
		printf("------\narg====%s\n", tab->arg);
		printf("------\nappend====%s\n", tab->append);
		printf("------\nlimi====%s\n", tab->delimiter);
		printf("infile====%s\n", tab->in);
		printf("outfile====%s\n", tab->out);
		tab = tab->next;
	}
	// t_token *tmp2 = cmd_line.tokens;
	// while (tmp2)
	// {
	// 	printf("------\ncontent====%s\n", (char *)tmp2->content);
	// 	printf("type====%d\n", tmp2->type);
	// 	printf("space====%d\n", tmp2->space);
	// 	tmp2 = tmp2->next;
	// }
	free_struct(&cmd_line);
	// char *cmd[] = {"echo","hello    world","wiliii",  NULL};
	// execve("/usr/bin/echo", cmd, NULL);
}
