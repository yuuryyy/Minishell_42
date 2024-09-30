/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:01:15 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/09/30 03:51:43 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
    if (cmd->arg)
    {
        if (chdir(cmd->arg) != 0)
            perror("cd");
    }
    else
    {
        if (chdir(path(env, "HOME")) != 0)
            perror("cd");
    }
    return 1;
}

int pwd(t_args *arg, char **cmd)
{
    (void)arg;
    (void)cmd;
    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        perror("pwd");
        return (0);
    }
    ft_putendl_fd(cwd, 1);
    free(cwd);
    return (1); 
}

void exec_exit(t_args *args, t_cmd_tab *cmd)
{
    (void)args;
    if (cmd->arg && cmd->arg[0])
    {
        if (cmd->next)
            printf("exit\nSHELL: exit: too many arguments\n");
        else if (is_num(cmd->arg))
        {
            printf("exit\n");
            exit(ft_atoi(cmd->arg));
        }
        else
        {
            printf("exit\nSHELL: exit: %s: numeric argument required\n", cmd->arg);
            exit(255);
        }
    }
    exit(0);
}

void exec_env(t_cmd_tab *cmd, t_list *env)
{
    if (cmd->arg && ft_strcmp(cmd->arg, "|") != 0)
    {
        printf("env: %s: No such file or directory\n", cmd->arg);
        return;
    }

    t_list *tmp = env;
    while (tmp)
    {
        printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
}
