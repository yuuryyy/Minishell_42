/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:34:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/25 10:33:51 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_seperator(char c)
{
	return (c == '|' || c == '<' || c == '>' );
}

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

