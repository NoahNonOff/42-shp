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
			printf("ESC\n");
			getchar(); // skip the '['
			switch (c = getchar())
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
				case '3':
					if (getchar() == '~')
						printf("-> del\n");
					break ;
				default:
					printf(".%c.", c);
			}
		}
		if (c == '\t')
			printf("-> tab\n");
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (0);
}
