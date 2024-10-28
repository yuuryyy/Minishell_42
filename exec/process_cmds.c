/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:10:03 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/28 01:07:26 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_cmds(t_args *args)
{
    t_cmd_tab	*table;

    table = args->table;
    if (!table)
        return (0);
    if (table && table->next == NULL)
		return(single_cmd(table));
    else if (exec_pipes(table))
        return (1);
    return (0);
}
