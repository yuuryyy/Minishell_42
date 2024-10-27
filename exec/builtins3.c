/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:19:43 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/27 01:17:03 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echo(t_args *args, t_cmd_tab *cmd)
{
    (void)args;

    int newline = 1;
    int i = 0;

    if (cmd && !cmd->cmd[1])
    {
        printf("\n");
        return (0);
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

int	array_len(char **str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int exec_exit(t_args *cmdline, t_cmd_tab *cmd_table, int flag)
{
	int	len;

	(void)cmdline;
	len = array_len(cmd_table->cmd);
	if (flag == SINGLE)
	{
		if (len == 1)
			return (printf("exit\n"), free_struct(cmd_table->data), exit (0), 1);
		else if (len >= 2 && !is_num(cmd_table->cmd[1]))
			return (printf("exit\n"), put_built_err("exit: ",cmd_table->cmd[1], NUMERICARG),
					free_struct(cmd_table->data), exit(255), 1);
		else if (len == 2 && is_num(cmd_table->cmd[1]))
			return (printf("exit\n"), free_struct(cmd_table->data), exit (ft_atoi(cmd_table->cmd[1])), 0);
		else
			return (printf("exit\n"), put_built_err("exit: ",NULL, TOOMANYARG), 1);
		}
	else
	{
		if (len == 1 || (len == 2 && is_num(cmd_table->cmd[1])))
		{
			if (len == 2)
				g_errno = ft_atoi(cmd_table->cmd[1]);
			return (0);
		}
		else if (len >= 2 && !is_num(cmd_table->cmd[1]))
			return (put_built_err("exit: ",cmd_table->cmd[1], NUMERICARG),1);
		else
			return (put_built_err("exit: ",NULL, TOOMANYARG), 1);
	}
	return (0);
}


int exec_env(t_cmd_tab *cmd, t_list *env)
{
    if (cmd->arg && ft_strcmp(cmd->arg, "|") != 0)
    {
        printf("env: %s: No such file or directory\n", cmd->arg);
        g_errno = 127;
        return (0);
    }

    t_list *tmp = env;
    while (tmp)
    {
        printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
    g_errno = 0;
	return (0);
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
