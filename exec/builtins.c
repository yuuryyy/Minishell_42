/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:01:15 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/25 12:52:53 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo(t_args *args, t_cmd_tab *cmd)
{
    (void)args;
    
    int newline = 1;
    int i = 0;

    if (cmd && !cmd->cmd[1])
    {
        printf("\n");
        return;
    }

    if (cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }

    while (cmd->cmd[++i])
    {
        printf("%s", cmd->cmd[i]);
        if (cmd->cmd[i + 1])
            printf(" ");
    }

    if (newline)
        printf("\n");
}

int cd(t_cmd_tab *cmd, t_list *env)
{
    char current_path[PATH_MAX];
    char *oldpwd = NULL;
    char *home = NULL;
    
    if (getcwd(current_path, PATH_MAX) == NULL)
    {
        perror("cd");
        return 1;
    }
    
    if (!cmd->cmd[1])
    {
        home = path(env, "HOME");
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
        oldpwd = path(env, "OLDPWD");
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
        if (chdir(cmd->cmd[1]) != 0)
        {
            ft_putstr_fd("cd: ", 2);
            perror(cmd->cmd[1]);
            return 1;
        }
    }
    char new_path[PATH_MAX];
    if (getcwd(new_path, PATH_MAX) != NULL)
    {
        char *pwd_str = ft_strjoin("PWD=", new_path);
        char *oldpwd_str = ft_strjoin("OLDPWD=", current_path);
        
        if (pwd_str && oldpwd_str)
        {
            t_list *pwd_node = find_env_node2(env, "PWD=");
            t_list *oldpwd_node = find_env_node2(env, "OLDPWD=");
            
            if (pwd_node)
            {
                pwd_node->content = pwd_str;
                free(pwd_node->content);
            }
            if (oldpwd_node)
            {
                oldpwd_node->content = oldpwd_str;
                free(oldpwd_node->content);
            }
        }
        else
        {
            free(pwd_str);
            free(oldpwd_str);
        }
    }
    return (0);
}

int pwd(t_args *arg, char **cmd)
{
    (void)arg;
    (void)cmd;
    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        perror("pwd");
        g_errno = 1;
        return g_errno;
    }
    ft_putendl_fd(cwd, 1);
    free(cwd);
    g_errno = 0;
    return g_errno; 
}

void exec_exit(t_args *args, t_cmd_tab *cmd)
{
    (void)args;
    if (cmd->arg && cmd->arg[0])
    {
        if (cmd->next)
        {
            printf("exit\nSHELL: exit: too many arguments\n");
            g_errno = 1;
        }
        else if (is_num(cmd->arg))
        {
            printf("exit\n");
            g_errno = ft_atoi(cmd->arg);
            exit(g_errno);
        }
        else
        {
            printf("exit\nSHELL: exit: %s: numeric argument required\n", cmd->arg);
            g_errno = 255;
            exit(g_errno);
        }
    }
    exit(g_errno);
}

void exec_env(t_cmd_tab *cmd, t_list *env)
{
    if (cmd->arg && ft_strcmp(cmd->arg, "|") != 0)
    {
        printf("env: %s: No such file or directory\n", cmd->arg);
        g_errno = 127;
        return;
    }

    t_list *tmp = env;
    while (tmp)
    {
        printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
    g_errno = 0;
}

int ft_unset(t_args *args, char **cmd)
{
    int i;
    i = 1;

    while (cmd[i])
    {
        t_list *prev = NULL;
        t_list *current = args->env;

        while (current)
        {
            char *env_var = (char *)current->content;
            if (ft_strncmp(env_var, cmd[i], ft_strlen(cmd[i])) == 0 && env_var[ft_strlen(cmd[i])] == '=')
            {
                if (prev)
                    prev->next = current->next;
                else
                    args->env = current->next;

                free(current->content);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
    g_errno = 0;
    return (0);
}
