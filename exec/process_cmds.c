/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:10:03 by ychagri           #+#    #+#             */
/*   Updated: 2024/11/03 01:13:40 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmds(t_args *args)
{
	t_cmd_tab		*table;
	int				err;

	table = args->table;
	if (!table)
		return (0);
	if (table && table->next == NULL)
	{
		err = exec_builtin(args, table, SINGLE);
		if (err == NOT_BUITIN)
			return (single_cmd(table));
	}
	else if (exec_pipes(table))
		return (1);
	return (0);
}
