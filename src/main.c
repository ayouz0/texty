#include "../header.h"

int main(int ac, char **av)
{
	if (ac < 1 || ac > 2)
	{
		write(2, "Usage: texty [filename]\n", 24);
		return (1);
	}
	int fd;
	if (ac != 2)
		return (1);
	if (prep_file(av[1], &fd) == -1)
		return (1);
	textyLoop(fd);
}
