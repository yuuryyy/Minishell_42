/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/27 01:45:23 by ychagri          ###   ########.fr       */
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
	char	*tmp;

	atexit(s);
	(void)ac; (void)av;
	ft_bzero(&cmd_line, sizeof(t_args));
	environment(env, &cmd_line);
	cmd_line.line = readline("bash~$ ");
	// {
	tmp = ft_strdup(cmd_line.line);
	if (!words_list(tmp, &cmd_line))
		printf("%d\n", errno);
	free(tmp);
	// for(int i = 0; cmd_line.path[i]; i++)
		// printf("%s\n",cmd_line.line);
	// while (cmd_line.tokens)
	// {
	// 	printf("------\ncontent====%s\n", cmd_line.tokens->content);
	// 	printf("type====%d\n", cmd_line.tokens->type);
	// 	printf("space====%d\n", cmd_line.tokens->space);
	// 	cmd_line.tokens = cmd_line.tokens->next;
	// }
	// free_struct(&cmd_line);
	// execve("/bin/l"s"", av, NULL);
}
