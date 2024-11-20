/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:02 by clu               #+#    #+#             */
/*   Updated: 2024/11/20 11:43:27 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = fill_line_buffer(fd, buffer);
	if (buffer == NULL || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = set_line(buffer);
	temp = ft_strdup(buffer + ft_strlen(line));
	free(buffer);
	buffer = temp;
	return (line);
}

char	*fill_line_buffer(int fd, char *buffer)
{
	char	*temp_buffer;
	char	*temp;
	ssize_t	bytes_read;

	temp_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (temp_buffer == NULL)
		return (NULL);
	if (buffer == NULL)
		buffer = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(temp_buffer), free(buffer), NULL);
		temp_buffer[bytes_read] = '\0';
		temp = ft_strjoin(buffer, temp_buffer);
		free(buffer);
		buffer = temp;
	}
	free(temp_buffer);
	return (buffer);
}

char	*set_line(char *line_check)
{
	char	*newline_pos;
	char	*line;
	size_t	len;

	newline_pos = ft_strchr(line_check, '\n');
	if (newline_pos)
	{
		len = newline_pos - line_check + 1;
		line = ft_substr(line_check, 0, len);
	}
	else
		line = ft_strdup(line_check);
	return (line);
}
