
#ifndef ENGINE_H
#define ENGINE_H

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "keys.h"

#define PAGE_SIZE 20000

extern char	buff[PAGE_SIZE];
extern int	cursor_pos;

void	textyLoop();
// void	read_input();
void	save_and_exit(int sig);
void	save_file(const char *filename);
void	load_file(const char *filename);



#endif