/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:02 by clu               #+#    #+#             */
/*   Updated: 2024/11/20 12:40:27 by clu              ###   ########.fr       */
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

// char	*set_line(char *buffer)
// {
// 	char	*newline_pos;
// 	char	*line;
// 	size_t	len;

// 	newline_pos = ft_strchr(buffer, '\n');
// 	if (newline_pos)
// 	{
// 		len = newline_pos - buffer + 1;
// 		line = ft_substr(buffer, 0, len);
// 	}
// 	else
// 		line = ft_strdup(buffer);
// 	return (line);
// }
char *set_line(char *buffer)
{
    int i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (buffer[i] == '\n')
        i++;
    return ft_substr(buffer, 0, i);
}