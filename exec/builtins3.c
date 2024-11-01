/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:19:43 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/01 01:47:31 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echo(t_args *args, t_cmd_tab *table,int flag)
{
    bool newline;
    int i;

    // (void)args;
    // (void)flag;
	if (flag == SINGLE)
		if (infile_opn(table) || outfile_opn(table))
			return (g_errno = 1, 1);
	newline = true;
	i = 1;
    while (table->cmd[i] && ft_strncmp(table->cmd[i], "-n", 3) == 0)
    {
        newline = false;
        i++;
    }
    while (table->cmd[i])
    {
       write(STDOUT_FILENO, table->cmd[i], ft_strlen(table->cmd[i]));
        if (table->cmd[i + 1])
           write(STDOUT_FILENO, " ", 1);
		i++;
    }
    if (newline)
       write(STDOUT_FILENO, "\n", 1);
	g_errno = 0;
	return (0);
}

int pwd(t_cmd_tab *table, char **cmd, int flag)
{
	char	*cwd;

    (void)cmd;
    (void)flag;
    (void)table;
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
    g_errno= 0;
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

int exec_exit(t_args *args, t_cmd_tab *cmd, int flag)
{
    int len;

    (void)args;
    (void)flag;
    len = array_len(cmd->cmd);
    if (len > 1)
    {
        if (!is_num(cmd->cmd[1]))
        {
            printf("SHELL: exit: %s: numeric argument required\n", cmd->cmd[1]);
            g_errno = 255;
            exit(g_errno);
        }
        if (len > 2)
        {
            printf("SHELL: exit: too many arguments\n");
            g_errno = 1;
            return g_errno;
        }
    }
    if (len == 1)
    {
        exit(0);
    }
    // fprintf(stderr, "str = <<<<%s>>>\n", cmd->cmd[1]);
    g_errno = ft_atoi(cmd->cmd[1]);
    // fprintf(stderr, "errno  = <<<<%d>>>\n", g_errno);
    exit(g_errno);
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

void	remove_env_var(t_args *args, char *cmd)
{
	char		*env_var;
	t_list		*prev;
	t_list		*current;

	prev = NULL;
	current = args->env;
	while (current)
	{
		env_var = (char *)current->content;
		if (ft_strncmp(env_var, cmd, ft_strlen(cmd)) == 0
			&& env_var[ft_strlen(cmd)] == '=')
		{
			if (prev)
				prev->next = current->next;
			else
				args->env = current->next;
			free(current->content);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_args *args, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (!is_valid_identifier(cmd[i]))
		{
			printf("unset: %s': not a valid identifier\n", cmd[i]);
			g_errno = 1;
		}
		else
		{
			remove_env_var(args, cmd[i]);
		}
		i++;
	}
	if (g_errno != 1)
		g_errno = 0;
	return (0);
}
