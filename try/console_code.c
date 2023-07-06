#include <curses.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int	main(void)
{
	printf("-> shell ");
	printf("\033[s"); // save cursor current state
	printf("\ntest");
	printf("\033[u"); // restore cursor state
	fflush(stdout);
	while (1)
		;
	return (0);
}
