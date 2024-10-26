/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:01:15 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/26 13:30:25 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void add_env_node(t_list *env, char *new_content)
{
    t_list *new_node = malloc(sizeof(t_list));
    if (!new_node)
        return;
    
    new_node->content = new_content;
    new_node->next = env;
    env = new_node;
}

int change_directory_home_or_oldpwd(t_cmd_tab *cmd, t_list *env) 
{
    char *home = path(env, "HOME");
    char *oldpwd = path(env, "OLDPWD");

    if (!cmd->cmd[1])
    {
        if (!home)
        {
            ft_putendl_fd("cd: HOME not set", 2);
            return 1;
        }
        if (chdir(home) != 0)
        {
            ft_putstr_fd("cd: ", 2);
            perror(home);
            return 1;
        }
    }
    else if (ft_strcmp(cmd->cmd[1], "-") == 0)
    {
        if (!oldpwd)
        {
            ft_putendl_fd("cd: OLDPWD not set", 2);
            return 1;
        }
        if (chdir(oldpwd) != 0)
        {
            ft_putstr_fd("cd: ", 2);
            perror(oldpwd);
            return 1;
        }
        ft_putendl_fd(oldpwd, 1);
    }
    else
    {
        return 1; 
    }

    return 0;
}

int change_directory_specified(t_cmd_tab *cmd)
{
    if (chdir(cmd->cmd[1]) != 0)
    {
        ft_putstr_fd("cd: ", 2);
        perror(cmd->cmd[1]);
        return 1;
    }
    return 0;
}

int update_environment_variables(t_list *env, char *current_path)
{
    char new_path[PATH_MAX];

    if (getcwd(new_path, PATH_MAX) != NULL)
    {
        char *oldpwd_str = ft_strjoin("OLDPWD=", current_path);
        t_list *oldpwd_node = find_env_node2(env, "OLDPWD=");

        if (oldpwd_node)
        {
            free(oldpwd_node->content);
            oldpwd_node->content = oldpwd_str;
        }
        else
        {
            add_env_node(env, oldpwd_str);
        }

        char *pwd_str = ft_strjoin("PWD=", new_path);
        t_list *pwd_node = find_env_node2(env, "PWD=");

        if (pwd_node)
        {
            free(pwd_node->content);
            pwd_node->content = pwd_str;
        }
        else
        {
            add_env_node(env, pwd_str);
        }
    }
    return 0;
}

int cd(t_cmd_tab *cmd, t_list *env)
{
    char current_path[PATH_MAX];
    if (getcwd(current_path, PATH_MAX) == NULL)
    {
        perror("cd");
        return 1;
    }

    if (change_directory_home_or_oldpwd(cmd, env) != 0 && cmd->cmd[1])
    {
        if (change_directory_specified(cmd) != 0)
            return 1;
    }

    update_environment_variables(env, current_path);
    return 0;
}