/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:19:43 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/27 18:08:06 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echo(t_args *args, t_cmd_tab *table)
{
    bool newline;
    int i;

    (void)args;
	newline = true;
	i = 0;
    if (table && !table->cmd[1])
        write(STDOUT_FILENO,"\n", 1);
    else if (table->cmd[1] && ft_strncmp(table->cmd[1], "-n", 3) == 0)
    {
        newline = false;
        i++;
    }
    while (table->cmd[++i])
    {
       write(STDOUT_FILENO, table->cmd[i], ft_strlen(table->cmd[i]));
        if (table->cmd[i + 1])
           write(STDOUT_FILENO, " ", 1);
    }
    if (newline)
       write(STDOUT_FILENO, "\n", 1);
	g_errno = 0;
	return (0);
}

int pwd(char **cmd)
{
	char	*cwd;

    (void)cmd;
	if (cmd[1] && *cmd[1] == '-')
		return (put_built_err("pwd: ", NULL, "extra options!!"), 1);
    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        perror("pwd");
        g_errno = 1;
        return (g_errno);
    }
    ft_putendl_fd(cwd, STDOUT_FILENO);
    free(cwd);
    g_errno = 0;
    return (g_errno); 
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
			return (printf("exit\n"), free_struct(cmd_table->data), exit (0), 0);
		else if (len >= 2 && !is_num(cmd_table->cmd[1]))
			return (printf("exit\n"), put_built_err("exit: ",cmd_table->cmd[1], NUMERICARG),
					free_struct(cmd_table->data), exit(255), 255);
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
			return (g_errno);
		}
		else if (len >= 2 && !is_num(cmd_table->cmd[1]))
			return (put_built_err("exit: ",cmd_table->cmd[1], NUMERICARG),1);
		else
			return (put_built_err("exit: ",NULL, TOOMANYARG), 1);
	}
	return (0);
}


int exec_env(t_cmd_tab *table, t_list *env)
{
	t_list *tmp;

    if (table->cmd[1])
    {
		ft_putstr_fd("env: "RED, 2);
		ft_putstr_fd(table->cmd[1], 2);
		ft_putstr_fd(RESET, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
        g_errno = 127;
        return (127);
    }
    tmp = env;
    while (tmp)
    {
        write(STDOUT_FILENO, (char *)tmp->content, ft_strlen(tmp->content));
		write(STDOUT_FILENO, "\n", 1);
        tmp = tmp->next;
    }
    g_errno = 0;
	return (0);
}

int ft_unset(t_args *args, char **cmd)
{
    int		i;
	t_list	*prev;
	t_list	*current;

    i = 1;
	g_errno = 0;
    while (cmd[i])
    {
		if (ft_isdigit(*cmd[i]))
			put_built_err("unset: ", cmd[i], NOTVALID);
       prev = NULL;
       current = args->env;
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
    return (g_errno);
}
