/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:40:43 by clu               #+#    #+#             */
/*   Updated: 2024/11/22 13:54:36 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Test the get_next_line function /////////////////////////////////////////////
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

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

void test_multiple_fds(int loops)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;

	int i = 0;
	fd1 = open("./text_files/story.txt", O_RDONLY);
	fd2 = open("./text_files/multi_lines.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Error opening files");
		if (fd1 != -1) close(fd1);
		if (fd2 != -1) close(fd2);
		return;
	}
	printf("Reading from multiple file descriptors:\n");
	printf("BUFFER_SIZE is: %d\n\n", BUFFER_SIZE);
	while (i < loops)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		if (line1)
		{
			printf("fd1: %s", line1);
			free(line1);
		}
		else
			printf("fd1: NULL\n");
		if (line2)
		{
			printf("fd2: %s", line2);
			free(line2);
		}
		else
			printf("fd2: NULL\n");
		i++;
	}
	close(fd1);
	close(fd2);
}

int main(int argc, char **argv)
{
	int loops = 10;

	if (argc > 1)
	{
		loops = atoi(argv[1]);
		if (loops <= 0)
		{
			fprintf(stderr, "Invalid number of loops: %s\n", argv[1]);
			return 1;
		}
	}
	test_multiple_fds(loops);
	return 0;
}
