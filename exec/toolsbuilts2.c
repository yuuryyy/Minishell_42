/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsbuilts2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:34:12 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/31 23:51:04 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_valid_identifier(const char *str)
{
    if (!str || !*str)
        return (0);
    if (!ft_isalpha(*str) && *str != '_')
        return (0);
    str++;
    while (*str)
    {
        if (!ft_isalnum(*str) && *str != '_')
            return (0);
        str++;
    }
    return (1);
}