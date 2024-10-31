/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:01:15 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/31 23:14:45 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_directory_to_home(char *home)
{
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (1);
	}
	if (chdir(home) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(home);
		return (1);
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
	else if (ft_strcmp(cmd->cmd[1], "-") == 0)
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
			return (1);
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
		add_env_node(env, oldpwd_str);
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
		add_env_node(env, pwd_str);
}

int	cd(t_cmd_tab *cmd, t_list **env)
{
	char	current_path[PATH_MAX];
	char	new_path[PATH_MAX];

	if (getcwd(current_path, PATH_MAX) == NULL)
	{
		perror("cd");
		return (1);
	}
	if (handle_cd_command(cmd, *env) == 1)
		return (1);
	if (getcwd(new_path, PATH_MAX) != NULL)
	{
		update_oldpwd(env, current_path);
		update_pwd(env, new_path);
	}
	return (0);
}
