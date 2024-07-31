/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:45:51 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/29 16:47:27 by youssra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



void	syntax_error(t_args *cmd_line)
{
	ft_putstr_fd("bash: syntax error\n", 2);
	free(cmd_line->line);
	cmd_line->line = NULL;
	if (cmd_line->tokens)
		free_tokens(&cmd_line->tokens);
	if (cmd_line->table)
		free_table(&cmd_line->table);
	errno = EXIT_FAILURE;
}
