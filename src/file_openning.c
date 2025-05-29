#include "../header.h"

int	prep_file(char const *filename)
{
	int fd;

	fd = open(filename, O_RDWR | O_CREAT, 0644);

	if (fd == -1) {

		write (2, "texty couldn't open the file", 29);
		write (2, filename, strlen(filename));
		return (-1);
	}
	textyLoop();
	return (fd);
}
