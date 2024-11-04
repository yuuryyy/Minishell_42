/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:11:48 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/04 03:53:01 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_cmd_tab *table, int flag)
{
	int		i;
	bool	newline;

	i = 1;
	if (flag == SINGLE)
		if (infile_opn(table) || outfile_opn(table))
			return (1);
	newline = parse_echo_options(table, &i);
	print_echo_args(table, i, newline);
	return (exit_code(EXIT_SUCCESS, EDIT));
}

int	pwd(t_cmd_tab *table, char **cmd, int flag)
{
	char	*cwd;

	if (flag == SINGLE)
		if (infile_opn(table) || outfile_opn(table))
			return (1);
	if (cmd[1] && *cmd[1] == '-')
		return (put_built_err("pwd: ", NULL, "extra options!!"), 1);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd");
		return (exit_code(EXIT_FAILURE, EDIT));
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (exit_code(EXIT_SUCCESS, EDIT));
}

int	exec_exit(t_args *args, t_cmd_tab *cmd, int flag)
{
	int	code;

	if (flag == SINGLE)
	{
		if (infile_opn(cmd) || outfile_opn(cmd))
			return (1);
		printf("exit\n");
	}
	code = validate_exit_argument(cmd);
	if (code == -1)
		return (1);
	perform_exit(args, code);
	return (0);
}

int	exec_builtin(t_args *args, t_cmd_tab *cmd, int flag)
{
	if (!cmd || !cmd->cmd)
		return (NOT_BUITIN);
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		return (echo(cmd, flag));
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		return (cd(cmd, &args->env, flag));
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		return (pwd(cmd, cmd->cmd, flag));
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		return (export_variable(args, cmd, flag));
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		return (exec_exit(args, cmd, flag));
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		return (exec_env(cmd, args->env, flag));
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		return (ft_unset(args, cmd->cmd, flag));
	return (NOT_BUITIN);
}
