/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:34:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 04:46:09 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_seperator(char c)
{
	return (c == '|' || c == '<' || c == '>' );
}

char	*envgetter(const char *key, t_list *env)
{
	char	*value;
	char	*lookup;
	t_list	*tmp;

	if (!key || !env)
		return (NULL);
	value = NULL;
	lookup = ft_strjoin(key, "=");
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(lookup, tmp->content, ft_strlen(lookup)) == 0)
		{
			value = ft_strdup(tmp->content + ft_strlen(lookup));
			break ;
		}
		tmp = tmp->next;
	}
	free(lookup);
	return (value);
}

void	environment(char **envp, t_args *cmd_line)
{
	t_list	*node;
	t_list	*prev;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			i++;
			continue ;
		}
		node = ft_lstnew(ft_strdup(envp[i]));
		node->previous = prev;
		prev = node;
		ft_lstadd_back(&cmd_line->env, node);
		i++;
	}
}
