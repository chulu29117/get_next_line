/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:02 by clu               #+#    #+#             */
/*   Updated: 2024/11/19 11:41:34 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char	*get_next_line(int fd)
{
	static char	*word;
	char		*line;
	char		*temp;

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
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	if (prev == NULL)
		prev = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(prev, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer && prev);
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
	char	*newline_pos;
	char	*line;
	size_t	len;

	newline_pos = ft_strchr(line_buffer, '\n');
	if (newline_pos)
	{
		len = newline_pos - line_buffer;
		line = ft_substr(line_buffer, 0, len);
	}
	else
		line = ft_strdup(line_buffer);
	return (line);
}
