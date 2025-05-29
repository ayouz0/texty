#include "../header.h"

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (prep_file(av[1]) == -1)
		return (1);
	textyLoop();
}
