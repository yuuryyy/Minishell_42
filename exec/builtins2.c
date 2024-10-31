/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:04:49 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/31 23:53:16 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *extract_key(const char *cmd, int append)
{
    char *separator_pos;
    size_t key_length;

    if (append)
    {
        separator_pos = ft_strnstr(cmd, "+=", ft_strlen(cmd));
    }
    else
    {
        separator_pos = ft_strchr(cmd, '=');
    }
    if (!separator_pos)
        return NULL;
    key_length = separator_pos - cmd;
    return ft_substr(cmd, 0, key_length);
}


int append_value(t_list *env_node, const char *new_part)
{
    char *old_value;
    char *new_value;
    char *final;

    old_value = ft_strchr((char *)env_node->content, '=') + 1;
    new_value = ft_strjoin(old_value, new_part);
    if (!new_value)
        return (g_errno = 1);
    final = ft_strjoin(((char *)env_node->content), new_value);
    free(new_value);
    if (!final)
        return (g_errno = 1);
    free(env_node->content);
    env_node->content = final;
    return 0;
}


int update_env_value(t_list *env_node, char *cmd, int append)
{
    char *key = extract_key(cmd, append);
    char *equal_sign = ft_strchr(cmd, '=');

    if (!equal_sign)
    {
        free(key);
        return (g_errno = 1);
    }

    equal_sign++;

    int result;
    if (append)
    {
        result = append_value(env_node, equal_sign);
    }
    else
    {
        free(env_node->content);
        env_node->content = ft_strdup(cmd);
        if (env_node->content == NULL)
        {
            result = (g_errno = 1);
        }
        else
        {
            result = 0;
        }
    }

    free(key);
    return result;
}

int add_new_env_var(t_args *args, const char *cmd, int append)
{
    char *new_content;
    if (append)
    {
        new_content = ft_strjoin(cmd, "=");
    }
    else
    {
        new_content = ft_strdup((char *)cmd);
    }
    
    if (!new_content) return (g_errno = 1);

    t_list *new_node = ft_lstnew(new_content);
    if (!new_node)
    {
        free(new_content);
        return (g_errno = 1);
    }
    ft_lstadd_back(&(args->env), new_node);
    return 0;
}


void display_env_vars(t_list *env)
{
    t_list *current = env;

    while (current)
    {
        printf("declare -x %s\n", (char *)current->content);
        current = current->next;
    }
}

int export_variable(t_args *args, t_cmd_tab *cmd)
{
    char *append_sign;
    char *identifier;

    if (!cmd->cmd[1])
    {
        display_env_vars(args->env);
        return (g_errno = 0);
    }

    append_sign = ft_strnstr(cmd->cmd[1], "+=", ft_strlen(cmd->cmd[1]));
    identifier = extract_key(cmd->cmd[1], append_sign != NULL);

    if (!identifier || !is_valid_identifier(identifier))
    {
        printf("export: `%s': not a valid identifier\n", cmd->cmd[1]);
        free(identifier);
        return (g_errno = 1);
    }
    free(identifier);

    t_list *env_node = find_env_node(args->env, cmd->cmd[1]);
    if (env_node)
    {
        if (update_env_value(env_node, cmd->cmd[1], append_sign != NULL) == 0)
        {
            return (g_errno = 0);
        }
        else
        {
            return (g_errno = 1);
        }
    }
    else
    {
        if (add_new_env_var(args, cmd->cmd[1], append_sign != NULL) == 0)
        {
            return (g_errno = 0);
        }
        else
        {
            return (g_errno = 1);
        }
    }
}
