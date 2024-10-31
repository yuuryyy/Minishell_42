/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:11:48 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/28 17:37:22 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_builtin(t_args *args, t_cmd_tab *cmd, int flag)
{
    if (!cmd || !cmd->cmd)
		return (NOT_BUITIN);
    if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
        return (echo(args, cmd, flag));
    else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
        return (cd(cmd, args->env, flag));
    else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
        return (pwd(cmd, cmd->cmd, flag));
    else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
        export_variable(args, cmd, flag);
    else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
        return (exec_exit(args, cmd, flag));
    else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
        return (exec_env(cmd, args->env, flag));
    else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
        return (ft_unset(args, cmd->cmd, flag));
	return (NOT_BUITIN);
}
