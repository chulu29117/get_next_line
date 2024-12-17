/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:48:49 by clu               #+#    #+#             */
/*   Updated: 2024/12/17 14:08:05 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

// Allocate a buffer to store the data read from the file descriptor.
static char	*allocate_buffer(char **prev_buffer)
{
	char	*temp_buffer;

	// Allocate memory for the buffer.
	temp_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (temp_buffer == NULL)
		return (NULL);
	if (*prev_buffer == NULL)			// Check if the previous buffer is empty.
	{
		*prev_buffer = ft_strdup("");	// Initialize the buffer with empty string.
		if (*prev_buffer == NULL)		// Check if the allocation was successful.
		{
			free(temp_buffer);			// Free the buffer to avoid leaks.
			return (NULL);
		}
	}
	return (temp_buffer);
}

// Fill the line buffer with data read from the file descriptor.
static char	*read_file_fill_buffer(int fd, char *prev_buffer)
{
	char	*temp_buffer;
	char	*temp;
	ssize_t	bytes_read;

	// Allocate a buffer to store the data read from the file descriptor.
	temp_buffer = allocate_buffer(&prev_buffer);
	if (temp_buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(prev_buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(temp_buffer), free(prev_buffer), NULL);
		temp_buffer[bytes_read] = '\0';
		temp = ft_strjoin(prev_buffer, temp_buffer);
		if (temp == NULL)
			return (free(temp_buffer), free(prev_buffer), NULL);
		free(prev_buffer);
		prev_buffer = temp;
	}
	free(temp_buffer);
	return (prev_buffer);
}

static char	*set_line(char *prev_buffer)
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

char	*get_next_line(int fd)
{
	static char	*line_buffer[MAX_FD];	// Static array to store the previous buffer between function calls.
	char		*line;
	char		*temp;

	// Check if the file descriptor is valid, the buffer size is greater than zero, and the file descriptor is within the maximum limit.
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	// Fill the line buffer with data from the file descriptor.
	line_buffer[fd] = read_file_fill_buffer(fd, line_buffer[fd]);
	// Check if the line buffer is empty.
	if (line_buffer[fd] == NULL || line_buffer[fd][0] == '\0') // Check if the line buffer is empty.
		return (free(line_buffer[fd]), line_buffer[fd] = NULL, NULL);	// Free the buffer and set it to NULL to avoid leaks.
	// Extract the line from the line buffer.
	line = set_line(line_buffer[fd]);
	if (line == NULL)	// Check if the line was successfully extracted.
		return (free(line_buffer[fd]), line_buffer[fd] = NULL, NULL);
	// Update the line buffer with the remaining data.
	temp = ft_strdup(line_buffer[fd] + ft_strlen(line));
	if (temp == NULL)	// Check if the update was successful.
		return (free(line_buffer[fd]), line_buffer[fd] = NULL, NULL);
	free(line_buffer[fd]);	// Free the previous buffer to avoid leaks.
	line_buffer[fd] = temp; // Update the line buffer with the remaining data.
	return (line);
}
