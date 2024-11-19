/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:02 by clu               #+#    #+#             */
/*   Updated: 2024/11/19 10:37:54 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char *word;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	word = fill_line_buffer(fd, word);
	if (word == NULL)
		return (NULL);
	line = set_line(word);
	word = ft_strdup(word + ft_strlen(line) + 1);
	if (word[0] == '\0')
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

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(prev, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(prev, buffer);
		free(prev);
		prev = temp;
	}
	free(buffer);
	return (prev);
}

char	*set_line(char *line_buffer)
{
	char	*line;
	char	*temp;
	char	*newline;

	newline = ft_strchr(line_buffer, '\n');
	if (newline == NULL)
	{
		line = ft_strdup(line_buffer);
		free(line_buffer);
		return (line);
	}
	*newline = '\0';
	line = ft_strdup(line_buffer);
	temp = ft_strdup(newline + 1);
	free(line_buffer);
	line_buffer = temp;
	return (line);
}
