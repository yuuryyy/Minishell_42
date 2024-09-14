/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builttins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:01:15 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/09/13 22:20:11 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(t_args *args, char **cmd)
{
    int i = 1;
    while (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
        i++;
    while (cmd[i])
    {
        ft_putstr_fd(cmd[i], 1);
        if (cmd[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (i == 1)
        ft_putchar_fd('\n', 1);
    return (1);
}


int ft_cd(t_args *args, char **cmd)
{
    char *path = NULL;

    if (cmd[1] == NULL)
        path = ft_strdup(getenv("HOME"));
    else
        path = ft_strdup(cmd[1]);

    if (chdir(path) == -1)
    {
        perror("cd");
        free(path);
        return (0);
    }

    free(path);
    return (1);
}


int ft_pwd(t_args *args, char **cmd)
{
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


int ft_export(t_args *args, char **cmd)
{
    int i = 1;
    while (cmd[i])
    {
        if (ft_strchr(cmd[i], '=') == NULL)
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(cmd[i], 2);
            ft_putendl_fd("': not a valid identifier", 2);
            return (0);
        }
        if (setenv(cmd[i], "", 1) == -1)
        {
            perror("setenv");
            return (0); 
        }
        i++;
    }
    return (1);
}
