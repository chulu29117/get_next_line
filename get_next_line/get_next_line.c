/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:02 by clu               #+#    #+#             */
/*   Updated: 2024/11/20 14:04:52 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line_buffer;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_buffer = fill_line_buffer(fd, line_buffer);
	if (line_buffer == NULL || line_buffer[0] == '\0')
	{
		free(line_buffer);
		line_buffer = NULL;
		return (NULL);
	}
	line = set_line(line_buffer);
	temp = ft_strdup(line_buffer + ft_strlen(line));
	free(line_buffer);
	line_buffer = temp;
	return (line);
}

char	*fill_line_buffer(int fd, char *line_buffer)
{
	char	*temp_buffer;
	char	*temp;
	ssize_t	bytes_read;

	temp_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (temp_buffer == NULL)
		return (NULL);
	if (line_buffer == NULL)
		line_buffer = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(line_buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(temp_buffer), free(line_buffer), NULL);
		temp_buffer[bytes_read] = '\0';
		temp = ft_strjoin(line_buffer, temp_buffer);
		free(line_buffer);
		line_buffer = temp;
	}
	free(temp_buffer);
	return (line_buffer);
}

char	*set_line(char *line_buffer)
{
	int	i;

	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\n')
		i++;
	return (ft_substr(line_buffer, 0, i));
}
