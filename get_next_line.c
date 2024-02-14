/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadewumi <oadewumi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:58:07 by oadewumi          #+#    #+#             */
/*   Updated: 2024/02/14 21:32:56 by oadewumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	
The get_next_line function is a function designed to read and return lines via
repeated calls to read the text file pointed to by the file descriptor (fd), ONE
LINE AT A TIME including the terminating '\n' character except at the end of 
the file which does not end with '\n' character. If theres nothing to be read,
it should return NULL.

"if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)"
The conditions above are Error handling controls; File descriptors (fd) are 
never in the negtive, only positives - they must have a content. Buffers must 
be greater than 0. The read function is greater than 0 if the file can be 
opened and returns -1 if the file cannot be opened. So, checking if the file 
can be opened.

How it works: 
The function parameter receives the file descriptor (fd) passed as
an argument. In a typical manner, we need a char pointer to a Static 
variable called 'lines'. This is where we dump the output result.

Likewise we need a char pointer variable called buffer with a predetermined 
size - 10 bytes of char (This value can be modified or desired) of BUFFER 
defined in the header file. The purpose of this variable is to receive the 
text read from the fd for further processing. 

In addition, an INT variable, 'bytes_read' is declared to keep track of the 
amount of bytes read from the fd. This bytes_read is an index of sort that 
we use for the char, buffer.

Already, in order to fulfil the condition necessary for reading the fd, 
bytes_read is initialised to 1, meaning if there are no bytes_read, then the
program moves on to the next execution. 
 
Also, a  function, "nl_found" (new line found) is called in this condition. 
This function i needed to search through the static variable - lines for the
'\n' character. If '\n' is found, the loop is broken. Then the program moves
to the next executable. However, it should be noted that the whole string of
characters read which may include the '\n' character is contained and 
null terminated within the 'buffer' variable. The condition fails if '\n' is
found among the string.

However, while the condition above holds true, the loop performs a helping 
function "ft_strjoin" from the Utils file. This aims to join accordingly
the content of buffer to the static variable, lines. In the first call, the 
static variable 'lines' is empty. Next, within "ft_strjoin", a checking condition
for this is inserted to duplicate (ft_strdup) the 'buffer' into the 
static variable, 'lines'. The return result is the static variable, 'lines' 
whose address is passed as an argument to another helper function "final_lines".

The purpose of the helper function, "final_lines" is to serch through the string
and refine the output by returning the string read from the fd + '\n' and
the left over is stored back inside the static variable, 'lines' for the next
run of the function.

Memory management:
BUFFER_SIZE was defined for the variable, 'buffer' is such that this is managed
dynamically. No memory needs to be freed.

Checks are made in the parent function as marked at the start of this document.
This ensures that the static variable memory is freed and set to NULL if it 
fails.

When the helper function "ft_strjoin" is called, memory is allocated to
dynamically allocate sufficent memory for the function and freed if it fails.
Likewise, within "ft_strjoin" is another helper function "ft_strdup" that 
activates when the static variable passed as an argument is empty or at first 
run of the function. The function "ft_strdup" duplicates the string passed as
an argument while dynamically allocating sufficient memory. Subsequently, 
the static variable passed as and argument (s1) for the function, "ft_strjoin" 
is freed of memory after a succesful operation.

Utility functions:
For the get_next_line function (GNL), 5 helper functions are used to ensure the
GNL functions as expected. The functions are listed as thus;

ft_strjoin - This function performs a concactenation of two character variables 
passed as an argument. It dynamically allocates memory to hold the result. 
Finally, it frees the memory of all the parameters to avoid leaks. It received 
the arguments, lines (static variable) and buffer from the mother function
"get_next_line".

ft_strdup - This function is called within "ft_strjoin" when a condtion of if
the source parameter (lines or s1) os empty. This function duplicates the 
second parameter (buffer or s2) while dynamically allocating memory to the
to the result that is returned. No freeing of memory occours here because no
other allocation was done to the source but only the result.

ft_strlen - Our trusty function ;) is used at length in the utility file to
determine the length of the string characters in bytes passed as an argument.
it returns an Int variable, 'count'.

ft_strlcpy - This function is used within "ft_strjoin" as a means to copy 
the destination parameter from "ft_strjoin" into the result passed as an 
argument from same.

ft_strlcat - This function is used as a final step in "ft_strjoin" to 
concatenate the source the content of the result from "ft_strlcpy".
*/

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

// #include "get_next_line.h"
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main(int argc, char *argv[])
// {
// 	char	*line;
// 	int		fd;

// 	if (argc < 2)
// 	{
// 		fprintf(stderr, "Usage: %s file1 file2 ...\n", argv[0]);
// 		return (1);
// 	}
// 	for (int i = 1; i < argc; i++)
// 	{
// 		fd = open(argv[i], O_RDONLY);
// 		if (fd == -1)
// 		{
// 			perror("Error opening file");
// 			continue ; // Skip to the next file
// 		}
// 		printf("FILE: %s\n", argv[i]);
// 		while (1)
// 		{
// 			line = get_next_line(fd);
// 			if (line)
// 				printf("%s", line);
// 			else
// 			{
// 				printf("\nEOL: %s\n", argv[i]);
// 				break ;
// 			}
// 			free(line);
// 		}
// 		close(fd);
// 	}
// 	if (system("leaks a.out > /dev/null"))
// 		system("leaks a.out");
// 	return (0);
// }
