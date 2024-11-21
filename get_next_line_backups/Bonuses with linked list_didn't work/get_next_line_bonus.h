/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:58:23 by clu               #+#    #+#             */
/*   Updated: 2024/11/21 12:41:29 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>	// read()
# include <stdlib.h>	// malloc(), free()

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_fd_list
{
	int					fd;
	char				*line_buffer;
	struct s_fd_list	*next;
}	t_fd_list;

char	*get_next_line(int fd);
char	*fill_line_buffer(int fd, char *prev);
char	*set_line(char *line_buffer);
void	free_fd_list(t_fd_list **list, int fd);
t_fd_list	*find_fd(t_fd_list **list, int fd);

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

#endif