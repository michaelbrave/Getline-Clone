//do not turn this in

#include "get_next_line.h"

int main (void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	//fd = 9999999999999;
	if (fd < 0)
		write(1, "failed to open/n", 15);

	while(get_next_line(fd, &line) == 1)
		write(1, line, ft_strlen(line));
	close(fd);
	return(0);
}
