/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:45:51 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/27 03:50:06 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	syntax_error(t_args *cmd_line)
{
	ft_putstr_fd("bash: syntax error\n", 2);
	free(cmd_line->line);
	free_tokens(cmd_line->tokens);
	free_table(&cmd_line->table);
	errno = EXIT_FAILURE;
}
