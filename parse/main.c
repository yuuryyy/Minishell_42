/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/23 05:19:19 by ychagri          ###   ########.fr       */
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

	atexit(s);
	(void)ac; (void)av;
	ft_bzero(&cmd_line, sizeof(t_args));
	environment(env, &cmd_line);
	
	cmd_line.line = readline("bash~$ ");
	// {
		replace_literal_token(cmd_line.line);
	seperate_tokens(&cmd_line);
	// for(int i = 0; cmd_line.path[i]; i++)
		printf("%s\n",cmd_line.line);
	token_list(&cmd_line);
	while (cmd_line.tokens)
	{
		printf("====%s\n", cmd_line.tokens->content);
		cmd_line.tokens = cmd_line.tokens->next;
		
	}
	
	// execve("/bin/l"s"", av, NULL);
}
