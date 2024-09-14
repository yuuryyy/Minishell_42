/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:11:48 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/09/13 22:11:59 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_builtin(t_args *args, t_cmd_tab *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
    {
        ft_echo(args, cmd->cmd);
        return (1);
    }
    else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
    {
        ft_cd(args, cmd->cmd);
        return (1);
    }
    else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
    {
        ft_pwd(args, cmd->cmd);
        return (1);
    }
    else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
    {
        ft_export(args, cmd->cmd);
        return (1);
    }
    else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
    {
        ft_unset(args, cmd->cmd);
        return (1);
    }
    else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
    {
        ft_env(args, cmd->cmd);
        return (1);
    }
    else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
    {
        ft_exit(args, cmd->cmd);
        return (1);
    }
    return (0);
}
