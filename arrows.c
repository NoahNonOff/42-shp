#include <curses.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

// link "https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar-for-reading-a-single-character-only"

int	main(void)
{
	int	c;
	static struct termios	oldt;
	static struct termios	newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	while ((c = getchar()) != 'e')
	{
		if (c == '\033')
		{
			getchar(); // skip the '['
			switch (getchar())
			{
				case 'A':
					printf("-> up\n");
					break;
				case 'B':
					printf("-> down\n");
					break;
				case 'C':
					printf("-> right\n");
					break;
				case 'D':
					printf("-> left\n");
					break;
			}
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (0);
}
