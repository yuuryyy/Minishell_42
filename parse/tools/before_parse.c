/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:34:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 19:52:12 by ychagri          ###   ########.fr       */
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

void	set_envi(t_args *cmd_line)
{
	char	cpath[PATH_MAX];

	if (getcwd(cpath, PATH_MAX) == 0)
		return (perror(cpath), free_struct(cmd_line), exit(1));
	cmd_line->env = ft_lstnew(ft_strjoin("PWD=", cpath));
	ft_lstadd_back(&cmd_line->env, ft_lstnew(ft_strdup("SHLVL=1")));
	ft_lstadd_back(&cmd_line->env, ft_lstnew(ft_strdup("_=/usr/bin/env")));
	ft_lstadd_back(&cmd_line->env, ft_lstnew(ft_strdup(DEF_PATH)));
}

void	environment(char **envp, t_args *cmd_line)
{
	t_list	*node;
	t_list	*prev;
	int		i;

	i = 0;
	cmd_line->env_i = false;
	if (!envp || !*envp)
	{
		cmd_line->env_i = true;
		set_envi(cmd_line);
	}
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
