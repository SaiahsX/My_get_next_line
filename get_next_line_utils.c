/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadewumi <oadewumi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:25:40 by oadewumi          #+#    #+#             */
/*   Updated: 2024/02/07 20:05:35 by oadewumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	dest_len;
	size_t	source_len;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	dest_len = ft_strlen(s1);
	source_len = ft_strlen(s2);
	result = (char *) malloc ((dest_len + source_len + 1) * sizeof(char));
	if (!result)
	{
		free (s1);
		return (NULL);
	}
	ft_strlcpy(result, s1, dest_len + 1);
	ft_strlcat(result, s2, (dest_len + source_len + 1));
	free (s1);
	return (result);
}

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
	{
		while (src[i] != '\0')
			i++;
		return (i);
	}
	while (i < (dstsize - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1, int str_len)
{
	int		indx;
	char	*s2;

	indx = 0;
	if (!s1 || !str_len)
		return (NULL);
	s2 = (char *) malloc ((str_len + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	while (indx++ < str_len)
		s2[indx] = s1[indx];
	s2[indx] = '\0';
	return (s2);
}