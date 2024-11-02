/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:19:43 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/02 20:04:59 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echo(t_cmd_tab *table,int flag)
{
    bool newline;
    int i;

	if (flag == SINGLE)
		if (infile_opn(table) || outfile_opn(table))
			return (1);
	newline = true;
	i = 1;
    while (table->cmd[i] && ft_strncmp(table->cmd[i], "-n", 3) == 0)
    {
        newline = false;
        i++;
    }
    while (table->cmd[i])
    {
       write(STDOUT_FILENO, table->cmd[i], ft_strlen(table->cmd[i]));
        if (table->cmd[i + 1])
           write(STDOUT_FILENO, " ", 1);
		i++;
    }
    if (newline)
       write(STDOUT_FILENO, "\n", 1);
	return (exit_code(EXIT_SUCCESS, EDIT));
}

int pwd(t_cmd_tab *table, char **cmd, int flag)
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

int	array_len(char **str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int exec_exit(t_args *args, t_cmd_tab *cmd, int flag)
{
    int len;
	int	code;

	if (flag == SINGLE)
	{
		if (infile_opn(cmd) || outfile_opn(cmd))
			return (1);
		printf("exit\n");
	}
    len = array_len(cmd->cmd);
	if (len == 1)
		return (free_struct(args), exit(0), 0);
    if (len > 1)
    {
        if (!is_num(cmd->cmd[1]))
        {
			put_built_err("exit: ", cmd->cmd[1], NUMERICARG);
			free_struct(args);
            exit(exit_code(EXIT_OUTOFRANGE, EDIT));
        }
		else if (len == 2 && is_num(cmd->cmd[1]))
		{
			code = exit_code(ft_atoi(cmd->cmd[1]), EDIT);
			free_struct(args);
			exit(code);
		}
		put_built_err("exit: ", NULL, TOOMANYARG);
    }
	return (0);
}

int exec_env(t_cmd_tab *table, t_list *env, int flag)
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

void	remove_env_var(t_args *args, char *argument)
{
	char		*env_var;
	t_list		*prev;
	t_list		*current;

	prev = NULL;
	current = args->env;
	while (current)
	{
		env_var = (char *)current->content;
		if (ft_strncmp(env_var, argument, ft_strlen(argument)) == 0
			&& env_var[ft_strlen(argument)] == '=')
		{
			if (prev)
				prev->next = current->next;
			else
				args->env = current->next;
			free(current->content);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
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
		if (!is_valid_identifier(cmd[i]))
			put_built_err("unset: ", cmd[i], NOTVALID);
		else
			remove_env_var(args, cmd[i]);
		i++;
	}
	return (exit_code(0, RETRIEVE));
}
