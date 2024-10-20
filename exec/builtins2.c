/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:04:49 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/20 11:08:15 by kaafkhar         ###   ########.fr       */
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

void	add_env_node(t_list **env, char *name_vari, char *var_value)
{
	char	*new_var;
	t_list	*new_node;

	new_var = ft_strjoin(name_vari, "=");
	new_var = ft_strjoin(new_var, var_value);
	new_node = ft_lstnew(new_var);
	ft_lstadd_back(env, new_node);
}

void update_env_value(t_list *env_node, char *new_value)
{
    char *env_var;
    char *equal_sign;
    char *new_var;

    env_var = (char *)env_node->content;
    equal_sign = ft_strchr(env_var, '=');

    if (equal_sign != NULL)
    {
        char *name_vari = ft_substr(env_var, 0, equal_sign - env_var);
        new_var = ft_strjoin(name_vari, "=");
        new_var = ft_strjoin(new_var, new_value);
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

int export_variable(t_args *args, t_cmd_tab *cmd)
{
    char *name_vari;
    char *var_value;
    char *equal_sign;
    t_list *env_node;

    if (cmd->cmd[1] == NULL)
    {
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



// int ft_unset(t_args *args, char **cmd)
// {
//     int i = 1;
//     while (cmd[i])
//     {
//         t_list *prev = NULL;
//         t_list *current = args->env;

//         while (current)
//         {
//             t_env *var = (t_env *)current->content;
//             if (strcmp(var->var, cmd[i]) == 0) // Comparaison avec strcmp
//             {
//                 if (prev)
//                     prev->next = current->next;
//                 else
//                     args->env = current->next;

//                 free(var->var);
//                 free(var->value);
//                 free(var);
//                 free(current);
//                 break;
//             }
//             prev = current;
//             current = current->next;
//         }
//         i++;
//     }
//     return 0;
// }

// int check_is_env(char *var, t_list *env)
// {
//     t_list *tmp = env;
//     while (tmp)
//     {
//         t_env *env_var = (t_env *)tmp->content;
//         if (ft_strcmp(env_var->var, var) == 0)
//             return 1;
//         tmp = tmp->next;
//     }
//     return 0;
// }
