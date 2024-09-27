/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:03:41 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/25 23:36:51 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_files(t_args *args, char *filename, int flag)
{
	int	err;

	err = 0;
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, R_OK) == -1)
			err = 1;
	}
	if (flag == INPUT && access(filename, F_OK) == -1)
		err = 2;
	if (err == 2)
		return (put_error(args, INTROUVABLE_FILE, filename), 1);
	else if (err == 1)
		return (put_error(args, PERMISSION, filename), 1);
	return (0);
}

char	**lst_to_array(t_list *lst)
{
	int		i;
	int		len;
	char	**arr;
	t_list	*tmp;

	tmp = lst;
	i = 0;
	len = ft_lstsize(tmp);
	arr = malloc((len + 1) * sizeof(char *));
	while (tmp)
	{
		arr[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}
