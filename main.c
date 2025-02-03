# include <fcntl.h> 
#include <stdio.h>
#include "get_next_line.h"
int main()
{
	int		fd;
	char	*line;

	fd = open("file1.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);  // Free the allocated string to avoid leaks
	}
	close(fd);
	return (0);
}