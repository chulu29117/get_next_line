/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:02 by clu               #+#    #+#             */
/*   Updated: 2024/11/19 11:42:01 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char	*get_next_line(int fd)
{
	static char *word;
	char		*line;
	char		*temp;

	// Check file descriptor, buffer size, and line pointer.
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	word = fill_line_buffer(fd, word);
	if (word == NULL)
		return (NULL);
	line = set_line(word);
	temp = ft_strdup(word + ft_strlen(line));
	free(word);
	word = temp;
	if (word && word[0] == '\0')
	{
		free(word);
		word = NULL;
	}
	return (line);
}

char	*fill_line_buffer(int fd, char *prev)
{
	char 	*buffer;
	char 	*temp;
	ssize_t	bytes_read;

	// Allocate memory for a buffer to read data from the file descriptor.
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
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
		{
			free(buffer && prev);	// Free the buffer and previous buffer to avoid leaks.
			return (NULL);
		}
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
		len = newline_pos - line_buffer;		// Calculate the length of the line.
		line = ft_substr(line_buffer, 0, len);	// Extract the line from the line buffer.
	}
	else
		line = ft_strdup(line_buffer);	// Copy the line buffer to the line.
	return (line);				// Return the line.
}

// Test the get_next_line function //
#include <stdio.h>

int	main(void)
{
	int 	fd;
	char	buffer[1024];
	ssize_t	bytes_read;
	
	fd = open("text.txt", O_CREAT);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	bytes_read = read(fd, buffer, sizeof(buffer));
	if (bytes_read == -1)
	{
		perror("Error reading file");
		close(fd);
		return (1);
	}
	buffer[bytes_read] = '\0';
	printf("Read %zd bytes: %s\n", bytes_read, buffer);
	close(fd);
	return (0);
}
