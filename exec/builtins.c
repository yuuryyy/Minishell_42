/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:01:15 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/03 17:27:43 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_directory_to_home(char *home)
{
	if (!home)
	{
		put_built_err("cd: ", NULL, HOMNOTSET);
		return (1);
	}
	else if (chdir(home) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(home);
		return (exit_code(EXIT_FAILURE, EDIT));
	}
	return (0);
}

int	handle_cd_command(t_cmd_tab *cmd, t_list *env)
{
	char	*oldpwd;
	char	*home;

	if (!cmd->cmd[1])
	{
		home = path(env, "HOME");
		if (change_directory_to_home(home) == 1)
			return (1);
	}
	else if (ft_strncmp(cmd->cmd[1], "-", 2) == 0)
	{
		oldpwd = path(env, "OLDPWD");
		if (change_directory_to_oldpwd(oldpwd))
			return (1);
	}
	else
	{
		if (chdir(cmd->cmd[1]) != 0)
		{
			ft_putstr_fd("cd: ", 2);
			perror(cmd->cmd[1]);
			return (exit_code(EXIT_FAILURE, EDIT));
		}
	}
	return (0);
}

void	update_oldpwd(t_list **env, char *current_path)
{
	char	*oldpwd_str;
	t_list	*oldpwd_node;

	oldpwd_str = ft_strjoin("OLDPWD=", current_path);
	oldpwd_node = find_env_node2(*env, "OLDPWD=");
	if (oldpwd_node)
	{
		free(oldpwd_node->content);
		oldpwd_node->content = oldpwd_str;
	}
	else
		ft_lstadd_back(env, ft_lstnew(oldpwd_str));
}

void	update_pwd(t_list **env, char *new_path)
{
	char	*pwd_str;
	t_list	*pwd_node;

	pwd_node = find_env_node2(*env, "PWD=");
	pwd_str = ft_strjoin("PWD=", new_path);
	if (pwd_node)
	{
		free(pwd_node->content);
		pwd_node->content = pwd_str;
	}
	else
		ft_lstadd_back(env, ft_lstnew(pwd_str));
}

int	cd(t_cmd_tab *cmd, t_list **env, int flag)
{
	char	current_path[PATH_MAX];
	char	new_path[PATH_MAX];
	int		err;

	(void)err;
	if (flag == SINGLE)
		if (infile_opn(cmd) || outfile_opn(cmd))
			return (1);
	if (getcwd(current_path, PATH_MAX) == NULL)
	{
		perror("cd");
		err = exit_code(EXIT_FAILURE, EDIT);
	}
	else if (handle_cd_command(cmd, *env) == 1)
		return (1);
	if (getcwd(new_path, PATH_MAX) != NULL)
	{
		update_oldpwd(env, current_path);
		update_pwd(env, new_path);
	}
	exit_code(EXIT_SUCCESS, EDIT);
	return (0);
}
