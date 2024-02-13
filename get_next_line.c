/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadewumi <oadewumi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:58:07 by oadewumi          #+#    #+#             */
/*   Updated: 2024/02/14 00:08:17 by oadewumi         ###   ########.fr       */
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
/*
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *line;
	int fd;
	
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
			continue; // Skip to the next file
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
				break;
				}
			free(line);
		}
		close(fd);
	}
	if (system("leaks a.out > /dev/null"))
		system("leaks a.out");
	return (0);
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h" // Assuming you have a header file for get_next_line

#define MAX_FD 10 // Maximum number of file descriptors to handle

typedef struct {
    int fd;
    char *buffer;
} FileState;

int main(void) {
    FileState fds[MAX_FD]; // Array to hold file descriptors and their buffers

    // Open file descriptors
    fds[0].fd = open("test.txt", O_RDONLY);
    fds[1].fd = open("test2.txt", O_RDONLY);
    // You can add more file descriptors as needed

    if (fds[0].fd == -1 || fds[1].fd == -1 /* Add more conditions for additional file descriptors */) {
        printf("Failed to open one or more files\n");
        return 1;
    }

    // Initialize buffers for each file descriptor
    for (int i = 0; i < MAX_FD; i++) {
        fds[i].buffer = NULL;
    }

    // Read from each file descriptor in a round-robin fashion
    int current_fd = 0;
    while (1) {
        char *str = get_next_line(fds[current_fd].fd);
        if (str) {
            printf("GNL from fd %d: %s\n", fds[current_fd].fd, str);
            free(str);
        } else {
            // If end of file reached or error occurred, close the file descriptor
            close(fds[current_fd].fd);
            fds[current_fd].fd = -1;
        }

        // Move to the next file descriptor in a round-robin fashion
        current_fd = (current_fd + 1) % MAX_FD;

        // Check if all file descriptors are closed
        int all_closed = 1;
        for (int i = 0; i < MAX_FD; i++) {
            if (fds[i].fd != -1) {
                all_closed = 0;
                break;
            }
        }
        if (all_closed) break;
    }

    return 0;
}


