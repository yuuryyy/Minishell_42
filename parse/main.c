/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/21 05:27:50 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	s()
{
	system("leaks minishell");
}
int main(int ac, char **av, char **env)
{
	t_args	cmd_line;
	char	*cmd;

	// atexit(s);
	(void)ac; (void)av;
	ft_bzero(&cmd_line, sizeof(t_args));
	environment(env, &cmd_line);
	
	cmd = readline("bash~$ ");
	// {
		replace_literal_token(&cmd_line,cmd);
		cmd_line.line = remove_quotes(cmd);
	// }
	// for(int i = 0; cmd_line.path[i]; i++)
		printf("%s\n",cmd_line.line);
	// printf("\n\n====================\n\n");
	// cmd_line.env = cmd_line.env->next;
	// while (cmd_line.env)
	// {
	// 	printf("content ======== \n%s\n ============ previous ============== \n%s\n==========", cmd_line.env->content,  cmd_line.env->previous->content);
	// 	cmd_line.env = cmd_line.env->next;
	// }
	// execve("/bin/l"s"", av, NULL);
}
