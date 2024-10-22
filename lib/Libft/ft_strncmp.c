/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:47:17 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/20 12:18:04 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] == (unsigned char)s2[i] && i < n - 1)
			i++;
		else
			break ;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
