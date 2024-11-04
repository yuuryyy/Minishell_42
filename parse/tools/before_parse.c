/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:34:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/04 06:11:37 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl_node(t_list *shlvl_node, int shlvl_value)
{
	char	*new_shlvl;
	char	*itoa_value;

	itoa_value = ft_itoa(shlvl_value);
	new_shlvl = ft_strjoin("SHLVL=", itoa_value);
	free(itoa_value);
	if (new_shlvl)
	{
		free(shlvl_node->content);
		shlvl_node->content = new_shlvl;
	}
}

void	increment_shlvl(t_list *shlvl_node)
{
	char	*content;
	int		shlvl_value;

	content = (char *)shlvl_node->content;
	if (content[6] == '-')
		shlvl_value = 0;
	else if (ft_atoi(content + 6) >= 1000)
		shlvl_value = 1;
	else if (ft_atoi(content + 6) == 999)
	{
		free(shlvl_node->content);
		shlvl_node->content = ft_strdup("SHLVL=");
		return ;
	}
	else
	{
		shlvl_value = ft_atoi(shlvl_node->content + 6);
		shlvl_value++;
	}
	update_shlvl_node(shlvl_node, shlvl_value);
}

void	init_shlvl(t_list **env)
{
	t_list	*shlvl_node;
	char	*new_shlvl;

	shlvl_node = find_env_node2(*env, "SHLVL=");
	if (shlvl_node)
	{
		increment_shlvl(shlvl_node);
	}
	else
	{
		new_shlvl = ft_strdup("SHLVL=1");
		if (new_shlvl)
			add_env_node(env, new_shlvl);
	}
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
	init_shlvl(&cmd_line->env);
}
