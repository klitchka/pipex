/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaparici <aaparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:32:48 by aaparici          #+#    #+#             */
/*   Updated: 2021/08/10 18:28:26 by aaparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	const char	*sc;

	sc = s;
	while (*sc)
		++sc;
	return ((unsigned int)(sc - s));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	if (!dst || !src)
		return (0);
	if (dstsize)
	{
		i = -1;
		while (dstsize-- && src[++i])
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

void	if_e(bool is_error, int val, char *msg)
{
	if (is_error)
	{
		errno = val;
		perror(msg);
		exit(EXIT_FAILURE);
	}
}
