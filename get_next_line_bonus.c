/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadewumi <oadewumi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:58:07 by oadewumi          #+#    #+#             */
/*   Updated: 2024/02/16 12:45:34 by oadewumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	
This is the bonus for the get_next_line function. This function has been 
modified to read from multiple  file descriptors as dynamically as possible.

The main changes to this function are evident from the header file name, the
buffer size from header file set to 42 instead of 10 and the changing of 
the static variable to a 2 dimensional array upto 1024 possible numbers of
file descriptors.
*/

#include "get_next_line_bonus.h"

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
	static char	*lines[1024];
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(lines[fd]);
		lines[fd] = NULL;
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0 && nl_found(lines[fd]) < 1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			if (lines)
				free(lines);
			lines[fd] = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		lines[fd] = ft_strjoin(lines[fd], buffer);
	}
	return (final_lines(&lines[fd]));
}
