/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:03:41 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 01:19:12 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_files(char *filename, int flag)
{
	int	err;

	err = 0;
	if (ft_strchr(filename, '/') && access(filename, F_OK) != 0)
		err = 2;
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, R_OK) == -1)
			err = 1;
	}
	if (flag == INPUT && access(filename, F_OK) != 0)
		err = 2;
	if (err == 2)
		return (put_error(INTROUVABLE_FILE, filename), 1);
	else if (err == 1)
		return (put_error(PERMISSION, filename), 1);
	return (0);
}

char	**lst_to_array(t_list *lst)
{
	int		i;
	int		len;
	char	**arr;
	t_list	*tmp;

	tmp = lst;
	i = 0;
	len = ft_lstsize(tmp);
	arr = malloc((len + 1) * sizeof(char *));
	while (tmp)
	{
		arr[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else if ((str[i] == '-' || str[i] == '+') && i == 0)
			i++;
		else
			return (0);
	}
	return (1);
}

char	*path(t_list *env, const char *var_name)
{
	t_list	*current;
	size_t	var_len;
	char	*env_var;

	var_len = ft_strlen(var_name);
	current = env;
	while (current)
	{
		env_var = (char *)current->content;
		if (ft_strncmp(env_var, var_name, var_len) == 0
			&& env_var[var_len] == '=')
		{
			return (env_var + var_len + 1);
		}
		current = current->next;
	}
	return (NULL);
}
