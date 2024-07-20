/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:02:23 by youssra           #+#    #+#             */
/*   Updated: 2024/07/20 01:11:36 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	environment(char **envp, t_args *cmd_line)
{
	t_list	*env;
	int		i;
	char	*str;
	char	**pathh;

	env = NULL;
	str = getenv("PATH");
	pathh = ft_split(str, ':');
	cmd_line->path = pathh;
	i  = 0;
	while (envp[i])
	{
		ft_lstadd_back(&env, ft_lstnew(envp[i]));
		i++;
	}
	cmd_line->env = env;
}
