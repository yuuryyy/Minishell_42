/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:04:49 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/04 03:51:47 by ychagri          ###   ########.fr       */
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

int	updates(t_cmd_tab *cmd, char *variable, char *find_sign, int i)
{
	t_list	*env_node;

	env_node = find_env_node(cmd->data->env, variable);
	if (env_node)
	{
		if (find_sign)
		{
			if (update_env_value(env_node, cmd->cmd[i], 1) != 0)
				return (exit_code(1, EDIT));
		}
		else if (ft_strchr(cmd->cmd[i], '='))
		{
			if (update_env_value(env_node, cmd->cmd[i], 0) != 0)
				return (exit_code(1, EDIT));
		}
	}
	else
	{
		if (add_new_env_var(cmd->data, cmd->cmd[i], find_sign != NULL) != 0)
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

int	export_variable(t_args *args, t_cmd_tab *cmd, int flag)
{
	char	*find_sign;
	char	*variable;
	int		result;
	int		i;

	i = 1;
	if (flag == SINGLE && (infile_opn(cmd) || outfile_opn(cmd)))
		return (1);
	exit_code(EXIT_SUCCESS, EDIT);
	if (!cmd->cmd[1])
		return (display_env_vars(args->env), exit_code(EXIT_SUCCESS, EDIT));
	while (cmd->cmd[i])
	{
		find_sign = ft_strnstr(cmd->cmd[i], "+=", ft_strlen(cmd->cmd[i]));
		variable = extract_variable(cmd->cmd[i], find_sign != NULL);
		if (ft_strncmp(variable, "PATH", 5) == 0)
			args->env_i = false;
		if (!variable || !is_valid(variable))
			put_built_err("export: ", variable, NOTVALID);
		else
			result = updates(cmd, variable, find_sign, i);
		free(variable);
		i++;
	}
	return (exit_code(0, RETRIEVE));
}
