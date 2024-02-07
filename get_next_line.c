/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadewumi <oadewumi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:58:07 by oadewumi          #+#    #+#             */
/*   Updated: 2024/02/07 20:17:48 by oadewumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Error handling controls; File descriptors (fd) are never in the negtive, 
only positives - they must have a content. Buffers must be greater than 0.
The read function is greater than 0 if the file can be opened and returns
-1 if the file cannot be opened. So, checking if the file can be opened 	*/


#include "get_next_line.h"

static int	nl_found(char *lines)
{
	if (!lines)
		return (0);
	while (*lines++)
		if (*lines == '\n')
			return (1);
	return (0);
}

static char	*final_lines(char **lines)
{
	char	*result;
	char	*temp_lines;
	int		i;

	i = 0;
	if (!*lines)
		return (NULL);
	temp_lines = *lines;
	while (temp_lines[i] && temp_lines[i] != '\n')
		i++;
	if (temp_lines[i] == '\n')
		i++;
	result = ft_strdup(temp_lines, i);
	if (!result)
	{
		free (*lines);
		*lines = NULL;
		return (result);
	}
	*lines = ft_strdup((temp_lines + i), ft_strlen(temp_lines + i));
	if (temp_lines)
		free (temp_lines);
	temp_lines = NULL;
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*lines;
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(lines);
		lines = NULL;
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0 && nl_found(lines) < 1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		lines = ft_strjoin(lines, buffer);
	}
	return (final_lines(&lines));
}

//remember to remove this block

#include <fcntl.h>

int	main(void)
{
	int	fd;
	int bytes;
	char *str;

	fd = open("test.txt", O_RDONLY);
	bytes = read(fd, str, 12);
	str[bytes + 1]= '\0';
	return (bytes);
}