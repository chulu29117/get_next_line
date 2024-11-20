/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:02 by clu               #+#    #+#             */
/*   Updated: 2024/11/20 12:40:08 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;	// Static variable to store the previous buffer between function calls.
	char		*line;	// Variable to store the line extracted from the line buffer.
	char		*temp;	// Temporary variable to store the updated line buffer.

	// Check if the file descriptor is valid and the buffer size is greater than zero.
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// Fill the line buffer with data from the file descriptor.
	buffer = fill_line_buffer(fd, buffer);
	// Check if the line buffer is empty.
	if (buffer == NULL || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	// Extract the line from the line buffer.
	line = set_line(buffer);
	// Update the line buffer with the remaining data.
	temp = ft_strdup(buffer + ft_strlen(line));
	free(buffer);
	buffer = temp;
	return (line);
}

char	*fill_line_buffer(int fd, char *buffer)
{
	char 	*temp_buffer;
	char 	*temp;
	ssize_t	bytes_read;

	// Allocate memory for a buffer to read data from the file descriptor.
	temp_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (temp_buffer == NULL)
		return (NULL);
	if (buffer == NULL)			// Check if the previous buffer is empty.
		buffer = ft_strdup("");	// Initialize the buffer with an empty string.
	bytes_read = 1;
	// Read data from the file descriptor until a newline character is found.
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);	// Read file and output # of bytes read.
		if (bytes_read == -1)	// Check read error
			return (free(temp_buffer), free(buffer), NULL);	// Free the buffer and previous buffer to avoid leaks.
		temp_buffer[bytes_read] = '\0';
		temp = ft_strjoin(buffer, temp_buffer);	// Join the previous buffer with the current buffer.
		free(buffer);
		buffer = temp;
	}
	free(temp_buffer);	// Free the temp buffer to avoid leaks.
	return (buffer);	// Return the updated buffer.
}
char *set_line(char *buffer)
{
    int i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (buffer[i] == '\n')
        i++;
    return ft_substr(buffer, 0, i);
}
// char	*set_line(char *buffer)
// {
// 	char	*newline_pos;
// 	char	*line;
// 	size_t	len;

// 	// Find the newline character in the line buffer.
// 	newline_pos = ft_strchr(buffer, '\n');	// Newline Position: Points to the newline character
// 	if (newline_pos)
// 	{
// 		len = newline_pos - buffer + 1;	// Calculate the length of the line.
// 		line = ft_substr(buffer, 0, len);	// Extract the line from the line buffer.
// 	}
// 	else
// 		line = ft_strdup(buffer);	// Copy the line buffer to the line.
// 	return (line);					// Return the line.
// }

// Test the get_next_line function //
#include <stdio.h>

void	test_1_all(int loops)
{
	int 	fd;
	char	*line;
	int		i = 0;
	
	fd = open("./text_files/all.txt", O_RDONLY);
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

void	test_2_empty(int loops)
{
	int 	fd;
	char	*line;
	int		i = 0;
	
	fd = open("./text_files/empty.txt", O_RDONLY);
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

void	test_3_single_line(int loops)
{
	int 	fd;
	char	*line;
	int		i = 0;
	
	fd = open("./text_files/single_line.txt", O_RDONLY);
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

void	test_4_multiple_lines(int loops)
{
	int 	fd;
	char	*line;
	int		i = 0;
	
	fd = open("./text_files/multi_lines.txt", O_RDONLY);
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

void	test_5_mixed_lines(int loops)
{
	int 	fd;
	char	*line;
	int		i = 0;
	
	fd = open("./text_files/mixed_lines.txt", O_RDONLY);
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

void	test_6_short_lines(int loops)
{
	int 	fd;
	char	*line;
	int		i = 0;
	
	fd = open("./text_files/short_lines.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	while (i < loops && (line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		// printf("Line %d: %s", i + 1, line); // Add line number for debugging
		free(line);
		i++;
	}
	printf("\n--------------------------------------------------------------------\n\n");
	close(fd);
}

void	test_7_only_new_lines(int loops)
{
	int 	fd;
	char	*line;
	int		i = 0;
	
	fd = open("./text_files/only_newlines.txt", O_RDONLY);
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

int	main(int argc, char **argv)
{
	int	loops;
	// Run the test cases
	if (argc > 1)
	{
		loops = atoi(argv[1]);
		test_1_all(loops);
		test_2_empty(loops);
		test_3_single_line(loops);
		test_4_multiple_lines(loops);
		test_5_mixed_lines(loops);
		test_6_short_lines(loops);
		test_7_only_new_lines(loops);
	}
	return (0);
}
