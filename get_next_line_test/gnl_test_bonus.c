/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:40:43 by clu               #+#    #+#             */
/*   Updated: 2024/12/17 14:09:02 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Test the get_next_line function /////////////////////////////////////////////
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

void test_multiple_fds(int loops)
{
	int		fd1;
	int		fd2;
	char	*line1 = NULL;
	char	*line2 = NULL;
	int 	i = 0;
	int 	count1 = 1;
	int 	count2 = 1;
	
	fd1 = open("./text_files/story.txt", O_RDONLY);
	fd2 = open("./text_files/multi_lines.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Error opening files");
		return;
	}
	printf("Reading from multiple file descriptors:\n");
	// printf("BUFFER_SIZE is: %d\n\n", BUFFER_SIZE);
    while (i < loops)
    {
        line1 = get_next_line(fd1);
        line2 = get_next_line(fd2);
        if (line1 == NULL && line2 == NULL)
            break;
        if (line1)
        {
            printf("fd1: [%d] %s\n", count1, line1);
			count1++;
            free(line1);
            line1 = NULL;
        }
        else
            printf("fd1: NULL\n\n");
        if (line2)
        {
            printf("fd2: [%d] %s\n", count2, line2);
			count2++;
            free(line2);
            line2 = NULL;
        }
        else
            printf("fd2: NULL\n\n");
        i++;
    }
	while ((line1 = get_next_line(fd1)) != NULL || (line2 = get_next_line(fd2)) != NULL)
    {
        if (line1)
        {
            free(line1);
            line1 = NULL;
        }
        if (line2)
        {
            free(line2);
            line2 = NULL;
        }
    }
	close(fd1);
	close(fd2);
}

int main(int argc, char **argv)
{
	int loops = 10;

	if (argc == 2)
	{
		loops = atoi(argv[1]);
		if (loops < 1)
		{
			fprintf(stderr, "Invalid number of loops: %s\n", argv[1]);
			return 1;
		}
		test_multiple_fds(loops);
	}
	else
	{
		fprintf(stderr, "Usage: %s <number of loops>\n", argv[0]);
		return 1;
	}
	return 0;
}
