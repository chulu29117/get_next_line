/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:40:06 by clu               #+#    #+#             */
/*   Updated: 2024/12/18 13:35:32 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Test the get_next_line function //
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

// Test the get_next_line function with a single file descriptor //////////////////////////
void	test_get_next_line(const char *file_name, int loops)
{
	int		fd;
	char	*line;
	int		i = 0;
	int 	count = 1;
	
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	while (i < loops)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		if (line)
		{
			printf("[%d] %s", count, line);
			count++;
			free (line);
			line = NULL;
		}
		else
			printf("fd: NULL\n");
		i++;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	printf("\n--------------------------------------------------------------------\n\n");
	close(fd);
}

void	test_1_story(int loops)
{
	printf("File 1: This file contains a short story about 0\n\n");
	test_get_next_line("./text_files/story.txt", loops);
}

void	test_2_empty(int loops)
{
	printf("File 2: This file is empty\n\n");
	test_get_next_line("./text_files/empty.txt", loops);
}

void	test_3_single_line(int loops)
{
	printf("File 3: This file contains a single line\n\n");
	test_get_next_line("./text_files/single_line.txt", loops);
}

void	test_4_multiple_lines(int loops)
{
	printf("File 4: This file contains multiple lines\n\n");
	test_get_next_line("./text_files/multi_lines.txt", loops);
}

void	test_5_mixed_lines(int loops)
{
	printf("File 5: This file contains mixed lines\n\n");
	test_get_next_line("./text_files/mixed_lines.txt", loops);
}

void	test_6_short_lines(int loops)
{
	printf("File 6: This file contains short lines\n\n");
	test_get_next_line("./text_files/short_lines.txt", loops);
}

void	test_7_only_new_lines(int loops)
{
	printf("File 7: This file contains only new lines\n\n");
	test_get_next_line("./text_files/only_newlines.txt", loops);
}

int main(int argc, char **argv)
{
	int loops;

	printf("Reading from a single file:\n");
	// printf("BUFFER_SIZE is: %d\n", BUFFER_SIZE);
	printf("--------------------------------------------------------------------\n");

	if (argc == 2)
	{
		loops = atoi(argv[1]);
		if (loops < 1)
		{
			fprintf(stderr, "Invalid number of loops: %s\n", argv[1]);
			return 1;
		}
		test_1_story(loops);
		// test_2_empty(loops);
		// test_3_single_line(loops);
		test_4_multiple_lines(loops);
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
