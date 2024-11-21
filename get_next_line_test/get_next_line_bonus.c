/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:48:49 by clu               #+#    #+#             */
/*   Updated: 2024/11/21 16:38:04 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*line_buffer[MAX_FD];	// Static array to store the previous buffer between function calls.
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_buffer[fd] = fill_line_buffer(fd, line_buffer[fd]);
	if (line_buffer[fd] == NULL || line_buffer[fd][0] == '\0')
	{
		free(line_buffer[fd]);
		line_buffer[fd] = NULL;
		return (NULL);
	}
	line = set_line(line_buffer[fd]);
	temp = ft_strdup(line_buffer[fd] + ft_strlen(line));
	free(line_buffer[fd]);
	line_buffer[fd] = temp;
	return (line);
}

char	*fill_line_buffer(int fd, char *prev_buffer)
{
	char	*temp_buffer;
	char	*temp;
	ssize_t	bytes_read;

	temp_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (temp_buffer == NULL)
		return (NULL);
	if (prev_buffer == NULL)
		prev_buffer = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(prev_buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(temp_buffer), free(prev_buffer), NULL);
		temp_buffer[bytes_read] = '\0';
		temp = ft_strjoin(prev_buffer, temp_buffer);
		free(prev_buffer);
		prev_buffer = temp;
	}
	free(temp_buffer);
	return (prev_buffer);
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

// Test the get_next_line function /////////////////////////////////////////////
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
	while (i < loops && (line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
		i++;
	}
	printf("\n--------------------------------------------------------------------\n");
	printf("--------------------------------------------------------------------\n\n");

	close(fd);
}

void	test_1_story(int loops)
{
	printf("File 1: This file contains a short story\n\n");
	test_get_next_line("./text_files/story.txt", loops);
}

void	test_2_single_line(int loops)
{
	printf("File 2: This file contains a single line\n\n");
	test_get_next_line("./text_files/single_line.txt", loops);
}

void	test_3_multiple_lines(int loops)
{
	printf("File 3: This file contains multiple lines\n\n");
	test_get_next_line("./text_files/multi_lines.txt", loops);
}

void	test_4_mixed_lines(int loops)
{
	printf("File 4: This file contains mixed short and long lines\n\n");
	test_get_next_line("./text_files/mixed_lines.txt", loops);
}

int main(int argc, char **argv)
{
	int loops;

	printf("Hello, BUFFER_SIZE is: %d\n", BUFFER_SIZE);
	printf("--------------------------------------------------------------------\n");

	if (argc > 1)
	{
		loops = atoi(argv[1]);
		if (loops <= 0)
		{
			fprintf(stderr, "Invalid number of loops: %s\n", argv[1]);
			return 1;
		}
		test_1_story(loops);
		test_2_single_line(loops);
		test_3_multiple_lines(loops);
		test_4_mixed_lines(loops);
		printf("/// Repeat the tests to check multiple file handling ///\n\n");
		test_1_story(loops);
		test_2_single_line(loops);
		test_3_multiple_lines(loops);
		test_4_mixed_lines(loops);
	}
	else
	{
		fprintf(stderr, "Usage: %s <number_of_loops>\n", argv[0]);
		return 1;
	}
	return 0;
}
