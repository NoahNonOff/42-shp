# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdint.h>

char	next_char(FILE *flux, int mode);

FILE	*new_flux(char *name, char *mode)
{
	FILE	*flux;
	char	c;

	flux = fopen(name, mode);
	if (!flux)
		return (NULL);
	fseek(flux, 0, SEEK_END);
	c = next_char(flux, 0);
	while (c == '\n')
	{
		next_char(flux, 1);
		c = next_char(flux, 0);
	}
	return (flux);
}

char	next_char(FILE *flux, int mode)
{
	char	buff[2] = {0};

	if (!ftell(flux))
		return (0);
	if (fseek(flux, -1, SEEK_CUR))
		return (-1);
	fread(buff, sizeof(char), 1, flux);
	if (mode == 1)
	{
		if (fseek(flux, -1, SEEK_CUR))
			return (-1);
	}
	return (buff[0]);
}

int	main(int ac, char **av)
{
	FILE	*flux;
	char	c;

	if (ac != 2)
		return (0);

	flux = new_flux(av[1], "a+");
	if (!flux)
		return (-1);

	while ((c = next_char(flux, 1)))
		printf("next char = |%c|\n", c);
	fclose(flux);
	return (0);
}
