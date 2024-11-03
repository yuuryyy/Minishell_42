/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:04:49 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/03 00:46:09 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_new_env_var(t_args *args, const char *cmd, int append)
{
	t_list	*new_node;
	char	*new_content;

	new_content = prepare_new_content(cmd, append);
	if (!new_content)
		return ((exit_code(1, EDIT)));
	new_node = ft_lstnew(new_content);
	if (!new_node)
	{
		free(new_content);
		return (g_errno = 1);
	}
	ft_lstadd_back(&(args->env), new_node);
	return (0);
}

int	updates(t_args *args, t_cmd_tab *cmd, char *variable, char *find_sign)
{
	t_list	*env_node;

	env_node = find_env_node(args->env, variable);
	if (env_node)
	{
		if (find_sign)
		{
			if (update_env_value(env_node, cmd->cmd[1], 1) != 0)
				return (exit_code(1, EDIT));
		}
		else if (ft_strchr(cmd->cmd[1], '='))
		{
			if (update_env_value(env_node, cmd->cmd[1], 0) != 0)
				return (exit_code(1, EDIT));
		}
	}
	else
	{
		if (add_new_env_var(args, cmd->cmd[1], find_sign != NULL) != 0)
			return (exit_code(1, EDIT));
	}
	return (0);
}

void	ordre_env_vars(t_list **env)
{
	t_list	*i;
	t_list	*j;
	char	*temp;

	i = *env;
	while (i && i->next)
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

void	display_env_vars(t_list *env)
{
	t_list	*current;

	ordre_env_vars(&env);
	current = env;
	while (current)
	{
		printf("declare -x %s\n", (char *)current->content);
		current = current->next;
	}
}

int	export_variable(t_args *args, t_cmd_tab *cmd)
{
	char	*find_sign;
	char	*variable;
	int		result;

	if (!cmd->cmd[1])
	{
		display_env_vars(args->env);
		return (exit_code(EXIT_SUCCESS, EDIT));
	}
	find_sign = ft_strnstr(cmd->cmd[1], "+=", ft_strlen(cmd->cmd[1]));
	variable = extract_variable(cmd->cmd[1], find_sign != NULL);
	if (!variable || !is_valid(variable))
	{
		put_built_err("export: ", variable, NOTVALID);
		free(variable);
		return (exit_code(1, EDIT));
	}
	result = updates(args, cmd, variable, find_sign);
	free(variable);
	return (result);
}
