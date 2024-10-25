/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsbuilts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:29:58 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/25 12:58:51 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_list *find_env_node(t_list *env, char *cmd)
{
    int     i;
    t_list  *current;
    char    *env_var;
    char    *append_pos;

    i = 0;
    append_pos = ft_strnstr(cmd, "+=", ft_strlen(cmd));
    if (append_pos)
        i = append_pos - cmd;
    else
    {
        while (cmd[i] != '=' && cmd[i])
            i++;
    }
    
    current = env;
    while (current)
    {
        env_var = (char *)current->content;
        char *env_equal = ft_strchr(env_var, '=');
        if (env_equal && (ft_strncmp(env_var, cmd, i) == 0) && 
            ((size_t)(env_equal - env_var) == (size_t)i))
            return (current);
        current = current->next;
    }
    return (NULL);
}

t_list	*find_env_node2(t_list *env, char *cmd)
{
	int			i;
	t_list	*current;
	char		*env_var;

	i = 0;
	while (cmd[i] != '=' && cmd[i])
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