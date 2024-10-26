/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:19:43 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/26 16:53:47 by ychagri          ###   ########.fr       */
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
    if (cmd->arg && cmd->arg[0])//changer arg aver cmd
    {
        if (cmd->next)
        {
            printf("exit\nSHELL: exit: too many arguments\n");
            g_errno = 1;
        }
        else if (is_num(cmd->arg))
        {
            printf()
            printf("exit\n");
            g_errno = ft_atoi(cmd->cmd[1]);
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
