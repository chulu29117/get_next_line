/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:02 by clu               #+#    #+#             */
/*   Updated: 2024/12/02 17:40:01 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*line_buffer;	// Static variable to store the previous buffer between function calls.
	char		*line;			// Variable to store the line extracted from the line buffer.
	char		*temp;			// Temporary variable to store the updated line buffer.

	// Check if the file descriptor is valid and the buffer size is greater than zero.
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// Fill the line buffer with data from the file descriptor.
	line_buffer = fill_line_buffer(fd, line_buffer);
	// Check if the line buffer is empty.
	if (line_buffer == NULL || line_buffer[0] == '\0')
		return (free(line_buffer), line_buffer = NULL, NULL);
	// Extract the line from the line buffer.
	line = set_line(line_buffer);
	if (line == NULL)	// Check if the line was successfully extracted.
		return (free(line_buffer), line_buffer = NULL, NULL);
	// Update the line buffer with the remaining data.
	temp = ft_strdup(line_buffer + ft_strlen(line));
	if (temp == NULL)	// Check if the update was successful.
		return (free(line_buffer), line_buffer = NULL, NULL);
	free(line_buffer);
	line_buffer = temp;
	return (line);
}

static char	*allocate_buffer(char **prev_buffer)
{
	char	*temp_buffer;

	// Allocate a temporary buffer to store the data read from the file descriptor.
	temp_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (temp_buffer == NULL)
		return (NULL);
	if (*prev_buffer == NULL)
	{
		*prev_buffer = ft_strdup("");	// Initialize the buffer with an empty string.
		if (*prev_buffer == NULL)		// Check if the buffer was successfully allocated.
		{
			free(temp_buffer);
			return (NULL);
		}
	}
	return (temp_buffer);
}

char	*fill_line_buffer(int fd, char *prev_buffer)
{
	char	*temp_buffer;
	char	*temp;
	ssize_t	bytes_read;

	// Allocate a temporary buffer to store the data read from the file descriptor.
	temp_buffer = allocate_buffer(&prev_buffer);
	if (temp_buffer == NULL)
		return (NULL);
	bytes_read = 1;
	// Read data from the file descriptor until a newline character is found or the end of file is reached.
	while (!ft_strchr(prev_buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);	// Read data from the file descriptor.
		if (bytes_read == -1)
			return (free(temp_buffer), free(prev_buffer), NULL);
		temp_buffer[bytes_read] = '\0';
		temp = ft_strjoin(prev_buffer, temp_buffer);		// Join the previous buffer with the temporary buffer.
		if (temp == NULL)
			return (free(temp_buffer), free(prev_buffer), NULL);
		free(prev_buffer);
		prev_buffer = temp;
	}
	free(temp_buffer);
	return (prev_buffer);
}
char	*set_line(char *prev_buffer)
{
	int		i;
	char	*line;

	if (prev_buffer == NULL)
		return (NULL);
	i = 0;
	// Find the index of the newline character.
	while (prev_buffer[i] && prev_buffer[i] != '\n')
		i++;
	if (prev_buffer[i] == '\n')
		i++;
	line = ft_substr(prev_buffer, 0, i); // Extract the line from the buffer.
	if (line == NULL) // Check if the line was successfully extracted.
		return (NULL);
	return (line);
}

// // Test the get_next_line function //
// #include <stdio.h>
// #include <fcntl.h>

// void	test_get_next_line(const char *file_name, int loops)
// {
// 	int		fd;
// 	char	*line;
// 	int		i = 0;

// 	fd = open(file_name, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return;
// 	}
// 	while (i < loops && (line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	printf("\n--------------------------------------------------------------------\n\n");
// 	close(fd);
// }

// void	test_1_story(int loops)
// {
// 	printf("File 1: This file contains a short story\n\n");
// 	test_get_next_line("./text_files/story.txt", loops);
// }

// void	test_2_empty(int loops)
// {
// 	printf("File 2: This file is empty\n\n");
// 	test_get_next_line("./text_files/empty.txt", loops);
// }

// void	test_3_single_line(int loops)
// {
// 	printf("File 3: This file contains a single line\n\n");
// 	test_get_next_line("./text_files/single_line.txt", loops);
// }

// void	test_4_multiple_lines(int loops)
// {
// 	printf("File 4: This file contains multiple lines\n\n");
// 	test_get_next_line("./text_files/multi_lines.txt", loops);
// }

// void	test_5_mixed_lines(int loops)
// {
// 	printf("File 5: This file contains mixed lines\n\n");
// 	test_get_next_line("./text_files/mixed_lines.txt", loops);
// }

// void	test_6_short_lines(int loops)
// {
// 	printf("File 6: This file contains short lines\n\n");
// 	test_get_next_line("./text_files/short_lines.txt", loops);
// }

// void	test_7_only_new_lines(int loops)
// {
// 	printf("File 7: This file contains only new lines\n\n");
// 	test_get_next_line("./text_files/only_newlines.txt", loops);
// }

// int main(int argc, char **argv)
// {
// 	int loops;

// 	printf("BUFFER_SIZE is: %d\n", BUFFER_SIZE);
// 	if (argc > 1)
// 	{
// 		loops = atoi(argv[1]);
// 		if (loops <= 0)
// 		{
// 			fprintf(stderr, "Invalid number of loops: %s\n", argv[1]);
// 			return 1;
// 		}
// 		test_1_story(loops);
// 		// test_2_empty(loops);
// 		// test_3_single_line(loops);
// 		// test_4_multiple_lines(loops);
// 		// test_5_mixed_lines(loops);
// 		// test_6_short_lines(loops);
// 		// test_7_only_new_lines(loops);
// 	}
// 	else
// 	{
// 		fprintf(stderr, "Usage: %s <number_of_loops>\n", argv[0]);
// 		return 1;
// 	}
// 	return 0;
// }
