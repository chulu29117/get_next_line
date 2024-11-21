/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:57:55 by clu               #+#    #+#             */
/*   Updated: 2024/11/21 13:33:29 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list;
	t_fd_list			*current_fd;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current_fd = find_fd(&fd_list, fd);
	if (current_fd == NULL)
		return (NULL);
	current_fd->line_buffer = fill_line_buffer(fd, current_fd->line_buffer);
	if (current_fd->line_buffer == NULL)
		return (NULL);
	{
		free_fd_list(&fd_list, fd);
		return (NULL);
	}
	line = set_line(current_fd->line_buffer);
	if (line == NULL)
		free_fd_list(&fd_list, fd);
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
// *find_fd function to find the file descriptor in the list //
t_fd_list *find_fd(t_fd_list **list, int fd)
{
	t_fd_list	*current;	// Create a pointer to the current list.

	current = *list;				// Set the current list to the list.
	// Loop through the list to find the file descriptor.
	while (current)
	{
		if (current->fd == fd)		// Check if the file descriptor is found.
			return (current);		// Return the current list.
		current = current->next;	// Move to the next node.
	}
	// If the file descriptor is not found, create a new node in the list.
	current = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (current == NULL)
		return (NULL);
	current->fd = fd;				// Set the file descriptor.
	current->line_buffer = NULL;	// Set the line buffer to NULL.
	current->next = *list;			// Set the next node to the list.
	*list = current;				// Set the list to the current node.
	return (current);
}

// *free_fd_list function to free the list //
void	free_fd_list(t_fd_list **list, int fd)
{
	t_fd_list	*current;
	t_fd_list	*temp;

	current = *list;		// Set the current list to the list.
	temp = NULL;			// Set the temp node to NULL.
	while (current)			// Loop through the list.
	{
		if (current->fd == fd)	// Check if the file descriptor is found.
		{
			if (temp)			// Check if the temp node is not NULL.
				temp->next = current->next;	// Set the temp node to the next node.
			else
				*list = current->next;		// Set the list to the next node.
			free(current->line_buffer);		// Free the line buffer.
			free(current);					// Free the current node.
			return ;
		}
		temp = current;				// Set the temp node to the current node.
		current = current->next;	// Move to the next node.
	}
}

// Test the get_next_line function //
#include <stdio.h>
#include <fcntl.h>

void	test_get_next_line(const char *file_name, int loops)
{
	int		fd;
	char	*line;
	int		i = 0;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	printf("Reading from file: %s\n", file_name);
	while (i < loops && (line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", i + 1, line);
		free(line);
		i++;
	}
	printf("\n--------------------------------------------------------------------\n\n");
	close(fd);
}

void test_multiple_fd(void)
{
	int 	fd1;
	int 	fd2;
	char 	*line;

	fd1 = open("./text_files/mixed_lines.txt", O_RDONLY);
	fd2 = open("./text_files/all.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Error opening file");
		if (fd1 != -1) close(fd1);
		if (fd2 != -1) close(fd2);
		return;
	}
	printf("Reading from multiple file descriptors:\n");
	// Read from fd1
	line = get_next_line(fd1);
	if (line)
	{
		printf("fd1: %s", line);
		free(line);
	}
	else
		printf("fd1: NULL\n");

	// Read from fd2
	line = get_next_line(fd2);
	if (line)
	{
		printf("fd2: %s", line);
		free(line);
	}
	else
		printf("fd2: NULL\n");

	// Read again from fd1
	line = get_next_line(fd1);
	if (line)
	{
		printf("fd1: %s", line);
		free(line);
	}
	else
		printf("fd1: NULL\n");

	// Read again from fd2
	line = get_next_line(fd2);
	if (line)
	{
		printf("fd2: %s", line);
		free(line);
	}
	else
		printf("fd2: NULL\n");

	close(fd1);
	close(fd2);
}

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		int loops = atoi(argv[2]);
		test_get_next_line(argv[1], loops);
	}
	else
		test_multiple_fd();
	return 0;
}
