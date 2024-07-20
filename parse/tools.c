/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:02:23 by youssra           #+#    #+#             */
/*   Updated: 2024/07/20 06:23:55 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	environment(char **envp, t_args *cmd_line)
{
	t_list	*node;
	t_list	*prev;
	int		i;
	char	*str;
	char	**pathh;

	str = getenv("PATH");
	pathh = ft_split(str, ':');
	prev = NULL;
	cmd_line->path = pathh;
	i  = 0;
	while (envp[i])
	{
		node = ft_lstnew(envp[i]);
		node->previous = prev;
		prev = node;
		ft_lstadd_back(&cmd_line->env, node);
		i++;
	}
}
