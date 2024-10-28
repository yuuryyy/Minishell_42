/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:01:15 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/27 22:46:23 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void add_env_node(t_list **env, char *new_content)
// {
//     t_list *new_node;

// 	new_node = malloc(sizeof(t_list));
//     if (!new_node)
//         return;
//     new_node->content = new_content;
//     new_node->next = env;
//     env = new_node;
// }

int change_directory_home_or_oldpwd(t_cmd_tab *cmd, t_list *env) 
{
    char *home = path(env, "HOME");
    char *oldpwd = path(env, "OLDPWD");

    if (!cmd->cmd[1])
    {
        if (!home)
			return (put_built_err("cd: ", NULL, HOMNOTSET), 1);
        if (chdir(home) != 0)
			return (ft_putstr_fd("cd: ", 2), perror(home), g_errno = 1, 1);
    }
    else if (ft_strncmp(cmd->cmd[1], "-", 2) == 0)
    {
		printf("%s\n", oldpwd);
        if (!oldpwd)
			return (put_built_err("cd: ", NULL, OLDNOTSET), 1);
        if (chdir(oldpwd) != 0)
			return (ft_putstr_fd("cd: ", 2), perror(oldpwd), g_errno = 1, 1);
        ft_putendl_fd(oldpwd, 1);
    }
	else
		return (2);
	return (0);
}

int change_directory_specified(t_cmd_tab *cmd)
{
    if (chdir(cmd->cmd[1]) != 0)
		return (put_built_err("cd: ", INTROUVABLE_FILE, cmd->cmd[1]), 1);
    return (g_errno = 0, 0);
}

int update_environment_variables(t_list *env, char *current_path)
{
    char	new_path[PATH_MAX];
	char	*oldpwd_str; 
	t_list	*oldpwd_node;
	char	*pwd_str;
	t_list	*pwd_node;

    if (getcwd(new_path, PATH_MAX) != NULL)
    {
        oldpwd_str = ft_strjoin("OLDPWD=", current_path);
        oldpwd_node = find_env_node2(env, "OLDPWD=");
        if (oldpwd_node)
        {
            free(oldpwd_node->content);
            oldpwd_node->content = oldpwd_str;
        }
        pwd_str = ft_strjoin("PWD=", new_path);
        pwd_node = find_env_node2(env, "PWD=");
        if (pwd_node)
        {
            free(pwd_node->content);
            pwd_node->content = pwd_str;
        }
        ft_lstadd_back(&env, ft_lstnew(pwd_str));
    }
    return (0);
}

int cd(t_cmd_tab *cmd, t_list *env)
{
    char current_path[PATH_MAX];

    if (getcwd(current_path, PATH_MAX) == NULL)
	{
		perror("cd");
		g_errno = 1;
	}
    else if (change_directory_home_or_oldpwd(cmd, env) == 2 && cmd->cmd[1])
        change_directory_specified(cmd);
    update_environment_variables(env, current_path);
    return (g_errno);
}