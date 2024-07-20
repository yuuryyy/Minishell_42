/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:23:18 by ychagri           #+#    #+#             */
/*   Updated: 2024/07/20 06:38:41 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

//int main()
//{
//	char h[] = "youssra";
//	t_list	*node;

//	node = ft_lstnew(h);
//	printf("%s",(char *)node->next);
//}