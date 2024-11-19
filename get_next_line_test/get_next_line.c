/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:02 by clu               #+#    #+#             */
/*   Updated: 2024/11/19 14:53:14 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*word;	// Static variable to store the previous buffer.
	char		*line;	// Variable to store the line extracted from the line buffer.
	char		*temp;	// Temporary variable to store the updated line buffer.

	// Check if the file descriptor is valid and the buffer size is greater than zero.
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// Fill the line buffer with data from the file descriptor.
	word = fill_line_buffer(fd, word);
	// Check if the line buffer is empty.
	if (word == NULL || word[0] == '\0')
		return (free(word), word = NULL, NULL);
	// Extract the line from the line buffer.
	line = set_line(word);
	// Update the line buffer with the remaining data.
	temp = ft_strdup(word + ft_strlen(line));
	free(word);
	word = temp;
	// Check if the line buffer is empty.
	if (word == NULL)
		return (free(word), NULL);
	return (line);
}

char	*fill_line_buffer(int fd, char *prev)
{
	char 	*buffer;
	char 	*temp;
	ssize_t	bytes_read;

	// Allocate memory for a buffer to read data from the file descriptor.
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	if (prev == NULL)			// Check if the previous buffer is empty.
		prev = ft_strdup("");	// Initialize the buffer with an empty string.
	bytes_read = 1;
	// Read data from the file descriptor until a newline character is found.
	while (!ft_strchr(prev, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);	// Read data from the file descriptor.
		if (bytes_read == -1)	// Check read error
			return (free(buffer), free(prev), NULL);	// Free the buffer and previous buffer to avoid leaks.
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(prev, buffer);	// Join the previous buffer with the current buffer.
		free(prev);
		prev = temp;
	}
	free(buffer);	// Free the temp buffer to avoid leaks.
	return (prev);	// Return the updated buffer.
}

char	*set_line(char *line_buffer)
{
	char	*newline_pos;
	char	*line;
	size_t	len;

	// Find the newline character in the line buffer.
	newline_pos = ft_strchr(line_buffer, '\n');	// Find the newline character in the line buffer.
	if (newline_pos)
	{
		len = newline_pos - line_buffer + 1;		// Calculate the length of the line.
		line = ft_substr(line_buffer, 0, len);	// Extract the line from the line buffer.
	}
	else
		line = ft_strdup(line_buffer);	// Copy the line buffer to the line.
	return (line);				// Return the line.
}

// Test the get_next_line function //
#include <stdio.h>

// Read all lines from a file //
void	test_1_all(void)
{
	int 	fd;
	char	*line;
	
	fd = open("all.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("\n--------------------------------------------------------------------\n\n");
	close(fd);
}

// Read from an empty file //
void	test_2_empty(void)
{
	int 	fd;
	char	*line;
	
	fd = open("empty.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("\n--------------------------------------------------------------------\n\n");
	close(fd);
}

// Read from a file with one line //
void	test_3_single_line(void)
{
	int 	fd;
	char	*line;
	
	fd = open("single_line.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("\n--------------------------------------------------------------------\n\n");
	close(fd);
}

// Read from a file with multiple lines //
void	test_4_multiple_lines(void)
{
	int 	fd;
	char	*line;
	
	fd = open("multi_lines.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("\n--------------------------------------------------------------------\n\n");
	close(fd);
}

// Read from a file with mixed lines //
void	test_5_mixed_lines(void)
{
	int 	fd;
	char	*line;
	
	fd = open("mixed_lines.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("\n--------------------------------------------------------------------\n\n");
	close(fd);
}

// Read from a file with short lines //
void	test_6_short_lines(void)
{
	int 	fd;
	char	*line;
	
	fd = open("short_lines.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("\n--------------------------------------------------------------------\n\n");
	close(fd);
}

// Read from only new lines //
void	test_7_only_new_lines(void)
{
	int 	fd;
	char	*line;
	
	fd = open("only_newlines.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("\n--------------------------------------------------------------------\n\n");
	close(fd);
}

int	main(void)
{
	test_1_all();
	test_2_empty();
	test_3_single_line();
	test_4_multiple_lines();
	test_5_mixed_lines();
	test_6_short_lines();
	test_7_only_new_lines();
	return (0);
}
