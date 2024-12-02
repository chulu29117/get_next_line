/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:48:49 by clu               #+#    #+#             */
/*   Updated: 2024/12/02 11:20:23 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*line_buffer[MAX_FD];	// Static array to store the previous buffer between function calls.
	char		*line;
	char		*temp;

	// Check if the file descriptor is valid, the buffer size is greater than zero, and the file descriptor is within the maximum limit.
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	// Fill the line buffer with data from the file descriptor.
	line_buffer[fd] = fill_line_buffer(fd, line_buffer[fd]);
	// Check if the line buffer is empty.
	if (line_buffer[fd] == NULL || line_buffer[fd][0] == '\0') // Check if the line buffer is empty.
		return (free(line_buffer[fd]), line_buffer[fd] = NULL);	// Free the buffer and set it to NULL to avoid leaks.
	// Extract the line from the line buffer.
	line = set_line(line_buffer[fd]);
	// Update the line buffer with the remaining data.
	temp = ft_strdup(line_buffer[fd] + ft_strlen(line));
	free(line_buffer[fd]);	// Free the previous buffer to avoid leaks.
	line_buffer[fd] = temp; // Update the line buffer with the remaining data.
	return (line);
}

char	*fill_line_buffer(int fd, char *prev_buffer)
{
	char 	*temp_buffer;
	char 	*temp;
	ssize_t	bytes_read;

	// Allocate memory for a buffer to read data from the file descriptor.
	temp_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (temp_buffer == NULL)
		return (NULL);
	if (prev_buffer == NULL)			// Check if the previous buffer is empty.
		prev_buffer = ft_strdup("");	// Initialize the buffer with an empty string.
	bytes_read = 1;
	// Read data from the file descriptor until a newline character is found.
	while (!ft_strchr(prev_buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);	// Read file and output # of bytes read.
		if (bytes_read == -1)	// Check read error
			return (free(temp_buffer), free(prev_buffer), NULL);	// Free the buffer and previous buffer to avoid leaks.
		temp_buffer[bytes_read] = '\0';
		temp = ft_strjoin(prev_buffer, temp_buffer);	// Join the previous buffer with the current buffer.
		if (temp == NULL)	// Check if the join was successful.
			return (free(temp_buffer), free(prev_buffer), NULL);	// Free the buffer and previous buffer to avoid leaks.
		free(prev_buffer);
		prev_buffer = temp;
		// printf("Read %zd bytes: %s\n", bytes_read, temp_buffer);
	}
	free(temp_buffer);	// Free the temp buffer to avoid leaks.
	return (prev_buffer);	// Return the updated buffer.
}

char	*set_line(char *prev_buffer)
{
	int		i;
	char	*line;

	if (prev_buffer == NULL)
		return (NULL);
	i = 0;
	while (prev_buffer[i] && prev_buffer[i] != '\n')
		i++;
	if (prev_buffer[i] == '\n')
		i++;
	line = ft_substr(prev_buffer, 0, i);
	if (line == NULL)
		return (NULL);
	return (line);
}

// // Test the get_next_line function /////////////////////////////////////////////
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
// 	printf("\n--------------------------------------------------------------------\n");
// 	printf("--------------------------------------------------------------------\n\n");

// 	close(fd);
// }

// void	test_1_story(int loops)
// {
// 	printf("File 1: This file contains a short story\n\n");
// 	test_get_next_line("./text_files/story.txt", loops);
// }

// void	test_2_single_line(int loops)
// {
// 	printf("File 2: This file contains a single line\n\n");
// 	test_get_next_line("./text_files/single_line.txt", loops);
// }

// void	test_3_multiple_lines(int loops)
// {
// 	printf("File 3: This file contains multiple lines\n\n");
// 	test_get_next_line("./text_files/multi_lines.txt", loops);
// }

// void	test_4_mixed_lines(int loops)
// {
// 	printf("File 4: This file contains mixed short and long lines\n\n");
// 	test_get_next_line("./text_files/mixed_lines.txt", loops);
// }

// int main(int argc, char **argv)
// {
// 	int loops;

// 	printf("BUFFER_SIZE is: %d\n", BUFFER_SIZE);
// 	printf("--------------------------------------------------------------------\n");

// 	if (argc > 1)
// 	{
// 		loops = atoi(argv[1]);
// 		if (loops <= 0)
// 		{
// 			fprintf(stderr, "Invalid number of loops: %s\n", argv[1]);
// 			return 1;
// 		}
// 		test_1_story(loops);
// 		test_2_single_line(loops);
// 		test_3_multiple_lines(loops);
// 		test_4_mixed_lines(loops);
// 		printf("/// Repeat the tests to check multiple file handling ///\n\n");
// 		test_1_story(loops);
// 		test_2_single_line(loops);
// 		test_3_multiple_lines(loops);
// 		test_4_mixed_lines(loops);
// 	}
// 	else
// 	{
// 		fprintf(stderr, "Usage: %s <number_of_loops>\n", argv[0]);
// 		return 1;
// 	}
// 	return 0;
// }
