/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:02 by clu               #+#    #+#             */
/*   Updated: 2024/11/18 16:28:52 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	int		file;
	char	**line;

	file = open(fd, O_RDONLY);
	if (file == -1)
	{
		write(1, "Line Error\n", 12);
		return (NULL);
	}
	line = parse(fd)
	
	
}

char	*fill_line_beffer(int fd, char *left_c, char *buffer)
{
	
}

char	*_set_line(char *line_buffer)
{
	
}


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
