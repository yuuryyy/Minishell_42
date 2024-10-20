/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:11:48 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/19 21:09:27 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_exported_vars(t_list *env)
{
    t_list *current = env;
    while (current) {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
}

int exec_builtin(t_args *args, t_cmd_tab *cmd)
{
    if (ft_strcmp(cmd->cmd[0], "echo") == 0)
        echo(args, cmd);
    else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
        cd(cmd, args->env);
    else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
        pwd(args, cmd->cmd);
    else if (ft_strcmp(cmd->cmd[0], "export") == 0)
        export_variable(args, cmd);
    else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
        exec_exit(args, cmd);
    else if (ft_strcmp(cmd->cmd[0], "env") == 0)
        exec_env(cmd, args->env);
    // else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
    //     ft_unset(args, cmd->cmd);
    else 
        return -1;
    return 0;
}
