/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporttools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 00:35:55 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/03 00:52:39 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_env_value(t_list *env_node, const char *new_part)
{
	char	*old_value_start;
	char	*old_value;
	char	*new_value;
	char	*final;
	size_t	key_len;

	old_value_start = ft_strchr((char *)env_node->content, '=');
	if (!old_value_start)
		return (exit_code(1, EDIT));
	old_value_start++;
	old_value = ft_strdup(old_value_start);
	new_value = ft_strjoin(old_value, new_part);
	if (!new_value)
		return (free(old_value), exit_code(1, EDIT));
	key_len = old_value_start - (char *)env_node->content;
	final = malloc(key_len + ft_strlen(new_value) + 1);
	if (!final)
		return (free(old_value), free(new_value), exit_code(1, EDIT));
	ft_strncpy(final, (char *)env_node->content, key_len);
	final[key_len] = '\0';
	ft_strcat(final, new_value);
	free(new_value);
	free(env_node->content);
	env_node->content = final;
	return (free(old_value), 0);
}

char	*extract_variable(const char *cmd, int append)
{
	char	*separator_pos;
	size_t	var_length;

	if (append)
		separator_pos = ft_strnstr(cmd, "+=", ft_strlen(cmd));
	else
		separator_pos = ft_strchr(cmd, '=');
	if (!separator_pos)
		return (ft_strdup2(cmd));
	var_length = separator_pos - cmd;
	return (ft_substr(cmd, 0, var_length));
}

int	update_env_value(t_list *env_node, char *cmd, int append)
{
	char	*equal_sign;
	char	*variable;
	int		result;

	variable = extract_variable(cmd, append);
	equal_sign = ft_strchr(cmd, '=');
	if (!equal_sign)
		return (free(variable), exit_code(1, EDIT));
	equal_sign++;
	result = 0;
	if (append)
		result = replace_env_value(env_node, equal_sign);
	else
	{
		free(env_node->content);
		env_node->content = ft_strdup(cmd);
		if (env_node->content == NULL)
		{
			free(variable);
			return (exit_code(1, EDIT));
		}
	}
	free(variable);
	return (result);
}

char	*prepare_new_content(const char *cmd, int append)
{
	const char			*valueur;
	char				*new_content;
	char				*equal_pos;
	size_t				variable_len;

	if (!append)
		return (ft_strdup2(cmd));
	equal_pos = ft_strnstr(cmd, "+=", ft_strlen(cmd));
	if (!equal_pos)
		return (NULL);
	variable_len = equal_pos - cmd;
	valueur = equal_pos + 2;
	new_content = malloc(variable_len + ft_strlen(valueur) + 2);
	if (!new_content)
		return (NULL);
	ft_strncpy(new_content, cmd, variable_len);
	new_content[variable_len] = '=';
	ft_strcpy(new_content + variable_len + 1, valueur);
	return (new_content);
}

int	is_valid(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
