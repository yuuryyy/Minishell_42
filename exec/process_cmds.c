/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:10:03 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/26 19:54:35 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// int	single_command()

int	execute_cmds(t_args *args)
{
	t_cmd_tab	*table;

	table = args->table;
	if (table->next == NULL)
	{
		if (single_cmd(table))
			return (1);
	}
	return (0);
}