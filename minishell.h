/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssra <youssra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:09:51 by youssra           #+#    #+#             */
/*   Updated: 2024/07/17 01:29:32 by youssra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "lib/Libft/libft.h"

typedef struct s_cmd
{
	char	**cmd;
	int		in;
	int		out;
	int		err;
}	t_cmd;

typedef struct s_args
{
	t_list	*cmds;
	int		cmd_num;
	char	**path;
	char	**env;
}	t_args;

#endif