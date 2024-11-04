/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/04 04:27:28 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_errno = 0;

// mkdir -p 1//2/3/4
// shlvl

int	exit_code(int code, int flag)
{
	static int	exit_code;

	if (flag == EDIT)
		exit_code = code;
	return (exit_code);
}

void	display_prompt(t_args *cmd_line)
{
	cmd_line->line = readline(MAGINTA PROMPT CYAN">$ "ANSI_FONT_COL_RESET);
	if (cmd_line->line == NULL)
	{
		while (wait(NULL) != -1)
			continue ;
		write(STDOUT_FILENO, "exit\n", 6);
		free_struct(cmd_line);
		exit(exit_code(0, RETRIEVE));
	}
	if (*cmd_line->line)
		add_history(cmd_line->line);
	if (process_line(cmd_line) != 0)
		return ;
	execute_cmds(cmd_line);
	while (wait(0) != -1)
		continue ;
	if (dup2(cmd_line->fdin, STDIN_FILENO) == -1)
		return (put_error("dup2 error on fdin", NULL),
			free_struct(cmd_line), exit(1));
	if (dup2(cmd_line->fdout, STDOUT_FILENO) == -1)
		return (put_error("dup2 error on fdout", NULL),
			free_struct(cmd_line), exit(1));
}

int	main(int ac, char **av, char **env)
{
	t_args	cmd_line;

	(void)ac;
	(void)av;
	ft_bzero(&cmd_line, sizeof(t_args));
	environment(env, &cmd_line);
	cmd_line.fdin = dup(STDIN_FILENO);
	cmd_line.fdout = dup(STDOUT_FILENO);
	if (cmd_line.fdin == -1 || cmd_line.fdout == -1)
		return (put_error("dup2 error on fdin", NULL),
			free_struct(&cmd_line), 1);
	exit_code(0, EDIT);
	while (1)
	{
		rl_catch_signals = 0;
		setup_signal_handlers();
		free_current_cmdline(&cmd_line);
		display_prompt(&cmd_line);
	}
	return (0);
}
