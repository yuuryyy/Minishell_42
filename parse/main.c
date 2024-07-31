/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/30 06:10:46 by youssra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	s()
// {
// 	system("leaks minishell");
// }


errno = 0;

int main(int ac, char **av, char **env)
{
	t_args	cmd_line;
	char	*tmp;

	// atexit(s);
	(void)ac; (void)av;
	ft_bzero(&cmd_line, sizeof(t_args));
	environment(env, &cmd_line);
	cmd_line.line = readline("bash~$ ");
	tmp = ft_strdup(cmd_line.line);
	if (!words_list(tmp, &cmd_line))
		printf("%d\n", errno);
	free(tmp);
	// for(int i = 0; cmd_line.path[i]; i++)
	t_token *tmp2 = cmd_line.tokens;
	while (tmp2)
	{
		printf("------\ncontent====%s\n", (char *)tmp2->content);
		printf("type====%d\n", tmp2->type);
		printf("space====%d\n", tmp2->space);
		tmp2 = tmp2->next;
	}
	free_struct(&cmd_line);
	// execve("/bin/l"s"", av, NULL);
}
