/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsbuilts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:29:58 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/04 03:46:42 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*find_env_node(t_list *env, char *cmd)
{
	char	*env_var;
	char	*env_equal;
	int		i;
	t_list	*current;

	i = get_equal_position(cmd);
	current = env;
	while (current)
	{
		env_var = (char *)current->content;
		env_equal = ft_strchr(env_var, '=');
		if (env_equal && (ft_strncmp(env_var, cmd, i) == 0)
			&& ((size_t)(env_equal - env_var) == (size_t)i))
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_list	*find_env_node2(t_list *env, char *cmd)
{
	char		*env_var;
	int			i;
	t_list		*current;

	i = 0;
	while (cmd[i] != '=' && cmd[i])
		i++;
	current = env;
	while (current)
	{
		env_var = (char *)current->content;
		if ((ft_strncmp(env_var, cmd, i)) == 0 && env_var[i] == '=')
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	change_directory_to_oldpwd(char *oldpwd)
{
	if (!oldpwd)
	{
		put_built_err("cd: ", NULL, OLDNOTSET);
		return (1);
	}
	else if (chdir(oldpwd) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(oldpwd);
		return (exit_code(EXIT_FAILURE, EDIT));
	}
	ft_putendl_fd(oldpwd, 1);
	return (exit_code(EXIT_SUCCESS, EDIT));
}

int	validate_exit_argument(t_cmd_tab *cmd)
{
	int	len;

	len = array_len(cmd->cmd);
	if (len > 1)
	{
		if (len == 2 && cmd->cmd[1][0] == '-')
			return (exit_code(EXIT_OUTOFRANGE, EDIT));
		if (!is_num(cmd->cmd[1]) || ft_atoi(cmd->cmd[1]) > LLONG_MAX)
		{
			put_built_err("exit: ", cmd->cmd[1], NUMERICARG);
			return (exit_code(EXIT_OUTOFRANGE, EDIT));
		}
		else if (len > 2)
		{
			put_built_err("exit: ", NULL, TOOMANYARG);
			return (-1);
		}
	}
	if (len == 2)
		return (ft_atoi(cmd->cmd[1]));
	return (0);
}

int	perform_exit(t_args *args, int code)
{
	free_struct(args);
	exit(exit_code(code, RETRIEVE));
}
