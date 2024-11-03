/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:19:43 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/03 22:07:32 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_seperator(char c)
{
	return (c == '|' || c == '<' || c == '>' );
}

char	*envgetter(const char *key, t_list *env)
{
	char	*value;
	char	*lookup;
	t_list	*tmp;

	if (!key || !env)
		return (NULL);
	value = NULL;
	lookup = ft_strjoin(key, "=");
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(lookup, tmp->content, ft_strlen(lookup)) == 0)
		{
			value = ft_strdup(tmp->content + ft_strlen(lookup));
			break ;
		}
		tmp = tmp->next;
	}
	free(lookup);
	return (value);
}

void	handle_envi(t_cmd_tab *table)
{
	t_list	*tmp;

	tmp = table->data->env;
	while (tmp)
	{
		if (ft_strncmp("PATH=", tmp->content, 5) == 0)
			tmp = tmp->next;
		else
		{
			ft_putendl_fd(tmp->content, STDOUT_FILENO);
			tmp = tmp->next;
		}
	}
}

int	exec_env(t_cmd_tab *table, t_list *env, int flag)
{
	pid_t	pid;
	int		status;

	if (flag == SINGLE)
		if (infile_opn(table) || outfile_opn(table))
			return (1);
	if (table->cmd[1])
		return (put_built_err("env: ", NULL, "no argumets/options !!"), 1);
	if (table->data->env_i == true)
		handle_envi(table);
	else
	{
		pid = fork();
		if (pid == -1)
			return (put_error(FORKMSG, NULL), 1);
		if (pid == 0)
			if (exec(table, env) == -1)
				return (put_error(NOTFOUNDMSG, "env"), exit(BINARY_ERROR), 127);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (exit_code(WEXITSTATUS(status), EDIT));
	}
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
