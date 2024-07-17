/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:02:23 by youssra           #+#    #+#             */
/*   Updated: 2024/07/17 00:24:44 by youssra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**path(char **envp)
{
	int		i;
	char	*str;
	char	**pathh;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=",envp[i], 5) == 0)
		{
			str = ft_strdup(envp[i] + 5);
			break ;
		}
		i++;
	}
	pathh = ft_split(str);
	return (pathh);
}

t_list	*env(char **envp)
{
	
}