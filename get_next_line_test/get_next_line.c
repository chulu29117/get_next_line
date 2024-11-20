/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:02 by clu               #+#    #+#             */
/*   Updated: 2024/11/20 16:00:18 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*line_buffer;	// Static variable to store the previous buffer between function calls.
	char		*line;		// Variable to store the line extracted from the line buffer.
	char		*temp;		// Temporary variable to store the updated line buffer.

	// Check if the file descriptor is valid and the buffer size is greater than zero.
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// Fill the line buffer with data from the file descriptor.
	line_buffer = fill_line_buffer(fd, line_buffer);
	// Check if the line buffer is empty.
	if (line_buffer == NULL || line_buffer[0] == '\0')
	{
		free(line_buffer);
		line_buffer = NULL;
		return (NULL);
	}
	// Extract the line from the line buffer.
	line = set_line(line_buffer);
	// Update the line buffer with the remaining data.
	temp = ft_strdup(line_buffer + ft_strlen(line));
	free(line_buffer);
	line_buffer = temp;
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
		printf("bytes_read: %ld\n", bytes_read);
		if (bytes_read == -1)	// Check read error
			return (free(temp_buffer), free(prev_buffer), NULL);	// Free the buffer and previous buffer to avoid leaks.
		temp_buffer[bytes_read] = '\0';
		temp = ft_strjoin(prev_buffer, temp_buffer);	// Join the previous buffer with the current buffer.
		free(prev_buffer);
		prev_buffer = temp;
		// printf("prev_buffer: %s\n", prev_buffer);
	}
	free(temp_buffer);	// Free the temp buffer to avoid leaks.
	return (prev_buffer);	// Return the updated buffer.
}
char	*set_line(char *prev_buffer)
{
	int	i;

	i = 0;
	while (prev_buffer[i] && prev_buffer[i] != '\n')
		i++;
	if (prev_buffer[i] == '\n')
		i++;
	return (ft_substr(prev_buffer, 0, i));
}

// Test the get_next_line function //
#include <stdio.h>

void	test_get_next_line(const char *file_path, int loops)
{
	int		fd;
	char	*line;
	int		i = 0;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	while (i < loops && (line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
		i++;
	}
	printf("\n--------------------------------------------------------------------\n\n");
	close(fd);
}

void	test_1_all(int loops)
{
	test_get_next_line("./text_files/all.txt", loops);
}

void	test_2_empty(int loops)
{
	test_get_next_line("./text_files/empty.txt", loops);
}

void	test_3_single_line(int loops)
{
	test_get_next_line("./text_files/single_line.txt", loops);
}

void	test_4_multiple_lines(int loops)
{
	test_get_next_line("./text_files/multi_lines.txt", loops);
}

void	test_5_mixed_lines(int loops)
{
	test_get_next_line("./text_files/mixed_lines.txt", loops);
}

void	test_6_short_lines(int loops)
{
	test_get_next_line("./text_files/short_lines.txt", loops);
}

void	test_7_only_new_lines(int loops)
{
	test_get_next_line("./text_files/only_newlines.txt", loops);
}

int main(int argc, char **argv)
{
	int loops;

	if (argc > 1)
	{
		loops = atoi(argv[1]);
		if (loops <= 0)
		{
			fprintf(stderr, "Invalid number of loops: %s\n", argv[1]);
			return 1;
		}
		test_1_all(loops);
		// test_2_empty(loops);
		// test_3_single_line(loops);
		// test_4_multiple_lines(loops);
		// test_5_mixed_lines(loops);
		// test_6_short_lines(loops);
		// test_7_only_new_lines(loops);
	}
	else
	{
		fprintf(stderr, "Usage: %s <number_of_loops>\n", argv[0]);
		return 1;
	}
	return 0;
}
