/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:04:49 by kaafkhar          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/20 19:42:39 by kaafkhar         ###   ########.fr       */
=======
/*   Updated: 2024/10/20 18:22:32 by ychagri          ###   ########.fr       */
>>>>>>> 23903e7e0f077d7ceae8cffaff4844aba731697f
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void add_env_node(t_list **env, char *name_vari, char *var_value)
{
    char *new_var;
    t_list *new_node;

    new_var = ft_strjoin(name_vari, "=");
    char *temp = new_var;
    new_var = ft_strjoin(new_var, var_value);
    free(temp);
    new_node = ft_lstnew(new_var);
    ft_lstadd_back(env, new_node);
}

void update_env_value(t_list *env_node, char *new_value)
{
    char *env_var = (char *)env_node->content;
    char *equal_sign = ft_strchr(env_var, '=');

    if (equal_sign != NULL) {
        char *name_vari = ft_substr(env_var, 0, equal_sign - env_var);
        char *new_var = ft_strjoin(name_vari, "=");
        char *temp = new_var;
        new_var = ft_strjoin(new_var, new_value);
        free(temp);
        free(env_node->content);
        env_node->content = new_var;
        free(name_vari);
    }
}

t_list	*find_env_node(t_list *env, char *name_vari)
{
	t_list	*current;
	char	*env_var;

	current = env;
	while (current)
	{
		env_var = (char *)current->content;
		if (ft_strncmp(env_var, name_vari, ft_strlen(name_vari)) == 0 && env_var[ft_strlen(name_vari)] == '=')
			return (current);
		current = current->next;
	}
	return (NULL);
}

void ordre_alpha(t_list **env)
{
    t_list *i;
    t_list *j;
    char *temp;

    if (!env || !(*env))
        return;

    i = *env;
    while (i)
    {
        j = i->next;
        while (j)
        {
            if (ft_strcmp((char *)i->content, (char *)j->content) > 0)
            {
                temp = i->content;
                i->content = j->content;
                j->content = temp;
            }
            j = j->next;
        }
        i = i->next;
    }
}

int export_variable(t_args *args, t_cmd_tab *cmd)
{
    char *name_vari;
    char *var_value;
    char *equal_sign;
    t_list *env_node;

    if (cmd->cmd[1] == NULL)
    {
        ordre_alpha(&(args->env));

        t_list *current = args->env;
        while (current)
        {
            printf("declare -x %s\n", (char *)current->content);
            current = current->next;
        }
        return 0;
    }

    equal_sign = ft_strchr(cmd->cmd[1], '=');
    if (equal_sign == NULL)
    {
        printf("export: invalid argument: %s\n", cmd->cmd[1]);
        return 1;
    }
    name_vari = ft_substr(cmd->cmd[1], 0, equal_sign - cmd->cmd[1]);
    var_value = ft_strdup(equal_sign + 1);

    env_node = find_env_node(args->env, name_vari);
    if (env_node)
    {
        update_env_value(env_node, var_value);
    }
    else
    {
        add_env_node(&args->env, name_vari, var_value);
    }

    free(name_vari);
    free(var_value);

    return 0;
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
    return (0);
}
