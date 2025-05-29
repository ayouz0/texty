#include "engine.h"



char	buff[PAGE_SIZE];
int		cursor_pos;


void	load_file_to_buffer(int fd)
{
	int bytes_read;

	bytes_read = read(fd, buff, PAGE_SIZE - 1);
	if (bytes_read < 0)
	{
		write(2, "Error reading file\n", 19);
		return;
	}
	buff[bytes_read] = '\0';
	cursor_pos = 0;
	write(1, buff, bytes_read);
	lseek(fd, 0, SEEK_SET);
}

void	clear_screen(void)
{
	// sleep(1); 
	const char *clear_sequence = "\033[H\033[J";
	write(1, clear_sequence, 7);
}

void	write_buffer_to_stdout(int cursor)
{
	int i = 0;
	while (buff[i] != '\0')
	{
		if (i == cursor)
			write(1, "\033[7m", 4); // Invert colors for cursor
		write(1, &buff[i], 1);
		if (i == cursor)
			write(1, "\033[0m", 4); // Reset colors
		i++;
	}
}

void	remove_terminal_cusor(void)
{
	const char *hide_cursor = "\033[?25l";
	write(1, hide_cursor, 6);
}

void	read_input_and_update_buffer(int fd)
{
	char input;
	int bytes_read;
	(void)fd; // Unused parameter, can be removed if not needed

	bytes_read = read(0, &input, 1);
	if (bytes_read <= 0)
		return ;
	if (input == CTRL_C)
	{
		// save_and_exit(0);
		return ;
	}
	if (input == BACKSPACE)
	{
		if (cursor_pos > 0)
		{
			cursor_pos--;
			memmove(&buff[cursor_pos], &buff[cursor_pos + 1], strlen(&buff[cursor_pos + 1]) + 1);
		}
	}
	else if (input == ENTER || input == CTRL_M)
	{
		buff[cursor_pos] = '\n';
		cursor_pos++;
	}
	else if (input >= 32 && input <= 126) // Printable characters
	{
		memmove(&buff[cursor_pos + 1], &buff[cursor_pos], strlen(&buff[cursor_pos]) + 1);
		buff[cursor_pos] = input;
		cursor_pos++;
	}
}

void	textyLoop(int fd)
{
	remove_terminal_cusor();
	load_file_to_buffer(fd);
	while (1)
	{
		clear_screen();
		write_buffer_to_stdout(cursor_pos);
		read_input_and_update_buffer(fd);
	}
	close(fd);
}