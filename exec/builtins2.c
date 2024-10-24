/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:04:49 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/24 12:30:06 by kaafkhar         ###   ########.fr       */
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

void add_env_node(t_list **env, char *cmd)
{
    t_list *new_node;
    
    new_node = ft_lstnew(ft_strdup(cmd));
    if (!new_node)
        return;
        
    ft_lstadd_back(env, new_node);
}

void update_env_value(t_list *env_node, char *cmd)
{
    int i = 0;
    char *env_var = env_node->content;
    char *equal_sign = ft_strchr(env_var, '=');

    while(cmd[i] != '=' && cmd[i])
        i++;
    
    if (cmd[i] == '=')
        i++;

    if (equal_sign != NULL)
    {
        char *name_vari = ft_substr(env_var, 0, equal_sign - env_var);
        if (!name_vari)
            return;
            
        char *new_var = ft_strjoin(name_vari, "=");
        if (!new_var)
        {
            free(name_vari);
            return;
        }
        
        char *temp = ft_strjoin(new_var, cmd + i);
        if (!temp)
        {
            free(name_vari);
            free(new_var);
            return;
        }
        
        env_node->content = temp;
        free(temp);
        
        free(name_vari);
        free(new_var);
        //malayqin l ta qalwa
    }
}


t_list	*find_env_node(t_list *env, char *cmd)
{
    int i;
    
    i = 0;
	t_list	*current;
	char	*env_var;

    while(cmd[i] != '=' && cmd[i])
        i++;
	current = env;
	while (current)
	{
		env_var = (char *)current->content;
		if ((ft_strncmp(env_var, cmd, i)) == 0 && env_var[i] == '=')
			return (current);
		current = current->next;
	}
	return (NULL);
}

int export_variable(t_args *args, t_cmd_tab *cmd)
{
    if (cmd->cmd[1] == NULL)
    {
        t_list *current = args->env;
        while(current)
        {
            printf("declare -x %s\n", (char *)current->content);
            current = current->next;
        }
        return 0;
    }

    if (ft_strchr(cmd->cmd[1], '=') == NULL)
    {
        printf("export: invalid argument: %s\n", cmd->cmd[1]);
        return (1);
    }

    t_list *env_node = find_env_node(args->env, cmd->cmd[1]);
    if (env_node)
    {
        char *new_content = ft_strdup(cmd->cmd[1]);
        if (!new_content)
            return 1;
        env_node->content = new_content;
        free(env_node->content);
    }
    else
    {
        char *new_content = ft_strdup(cmd->cmd[1]);
        if (!new_content)
            return 1;
        t_list *new_node = ft_lstnew(new_content);
        if (!new_node)
        {
            free(new_content);
            return (1);
        }
        ft_lstadd_back(&(args->env), new_node);
    }
    return (0);
}