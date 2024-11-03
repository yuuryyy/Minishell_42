/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:19:43 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/03 04:11:48 by kaafkhar         ###   ########.fr       */
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

int	exec_env(t_cmd_tab *table, t_list *env, int flag)
{
	pid_t	pid;
	int		status;

	if (flag == SINGLE)
		if (infile_opn(table) || outfile_opn(table))
			return (1);
	if (table->cmd[1])
	{
		put_built_err("env: ", NULL, "no argumets/options !!");
		return (1);
	}
	pid = fork();
	if (pid == -1)
		return (put_error(FORKMSG, NULL), 1);
	if (pid == 0)
		if (exec(table, env) == -1)
			exit (BINARY_ERROR);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (exit_code(WEXITSTATUS(status), EDIT));
	return (exit_code(EXIT_SUCCESS, EDIT));
}

int	ft_unset(t_args *args, char **cmd, int flag)
{
	int	i;

	i = 1;
	exit_code(EXIT_SUCCESS, EDIT);
	if (flag == SINGLE)
		if (infile_opn(args->table) || outfile_opn(args->table))
			return (1);
	while (cmd[i])
	{
		if (!is_valid(cmd[i]))
			put_built_err("unset: ", cmd[i], NOTVALID);
		else
			remove_env_var(args, cmd[i]);
		i++;
	}
	return (exit_code(0, RETRIEVE));
}
