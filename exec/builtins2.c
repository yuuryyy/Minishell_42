/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:04:49 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/09/30 02:23:47 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int own_strchr(char *str, char c)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return i;
        i++;
    }
    return -1;
}

t_env *create_env_node(char *var, char *value)
{
    t_env *new = malloc(sizeof(t_env));
    if (!new)
        return NULL;

    new->var = strdup(var);
    new->value = strdup(value);
    new->next = NULL;

    return new;
}

void ft_export(t_args *args, char **cmd)
{
    (void)args;
    int i = 1;

    if (cmd[1] == NULL) 
    {
        extern char **environ; 
        for (int j = 0; environ[j] != NULL; j++)
        {
            ft_putstr_fd(environ[j], 1); 
            ft_putstr_fd("\n", 1);
        }
        return;
    }

    while (cmd[i])
    {
        if (ft_strchr(cmd[i], '=') == NULL)
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(cmd[i], 2);
            ft_putendl_fd("': not a valid identifier", 2);
            return;
        }
        if (setenv(cmd[i], "", 1) == -1)
        {
            perror("setenv");
            return; 
        }
        i++;
    }
}

int ft_unset(t_args *args, char **cmd)
{
    int i = 1;
    while (cmd[i])
    {
        t_list *prev = NULL;
        t_list *current = args->env;

        while (current)
        {
            t_env *var = (t_env *)current->content;
            if (strcmp(var->var, cmd[i]) == 0) // Comparaison avec strcmp
            {
                if (prev)
                    prev->next = current->next;
                else
                    args->env = current->next;

                free(var->var);
                free(var->value);
                free(var);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
    return 0;
}

int check_is_env(char *var, t_list *env)
{
    t_list *tmp = env;
    while (tmp)
    {
        t_env *env_var = (t_env *)tmp->content;
        if (ft_strcmp(env_var->var, var) == 0)
            return 1;
        tmp = tmp->next;
    }
    return 0;
}
