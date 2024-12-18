#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;
//	int		i = 0;
	int	count;

	fd = open("get_next_line.c", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		printf("[%d] %s", count, line);
		count++;
		if (line == NULL)
			break;
		free (line);
		line = NULL;
	}
	close(fd);
	return (0);
}
