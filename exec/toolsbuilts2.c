/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsbuilts2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:34:12 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/11/03 04:12:43 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *s1, const char *s2)
{
	char	*orig;

	orig = s1;
	while (*s2)
	{
		*s1++ = *s2++;
	}
	*s1 = '\0';
	return (orig);
}

char	*ft_strdup2(const char *str)
{
	char		*dup;
	size_t		len;

	len = ft_strlen(str);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strcpy(dup, str);
	return (dup);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	get_equal_position(char *cmd)
{
	char	*append_pos;
	int		i;

	i = 0;
	append_pos = ft_strnstr(cmd, "+=", ft_strlen(cmd));
	if (append_pos)
		return (append_pos - cmd);
	while (cmd[i] != '=' && cmd[i])
		i++;
	return (i);
}
