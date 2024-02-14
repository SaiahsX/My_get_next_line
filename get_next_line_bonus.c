/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadewumi <oadewumi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:58:07 by oadewumi          #+#    #+#             */
/*   Updated: 2024/02/14 11:45:51 by oadewumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Error handling controls; File descriptors (fd) are never in the negtive, 
only positives - they must have a content. Buffers must be greater than 0.
The read function is greater than 0 if the file can be opened and returns
-1 if the file cannot be opened. So, checking if the file can be opened 	*/

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
			return (NULL);
		buffer[bytes_read] = '\0';
		lines[fd] = ft_strjoin(lines[fd], buffer);
	}
	return (final_lines(&lines[fd]));
}

//remember to remove this block
/*
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*str;
	

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("failed to open the file\n");
		return (1);
	}

	str = get_next_line(fd);


	while (str)
	{
		printf("GNL:%s\n", str);
		free(str);
		str = get_next_line(fd);
	}
	return (0);
}
*/

/* #include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char	*line;
	int		fd;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s file1 file2 ...\n", argv[0]);
		return (1);
	}
	for (int i = 1; i < argc; i++)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening file");
			continue ; // Skip to the next file
		}
		printf("FILE: %s\n", argv[i]);
		while (1)
		{
			line = get_next_line(fd);
			if (line)
				printf("%s", line);
			else
			{
				printf("\nEOL: %s\n", argv[i]);
				break ;
			}
			free(line);
		}
		close(fd);
	}
	if (system("leaks a.out > /dev/null"))
		system("leaks a.out");
	return (0);
} */
