# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdint.h>

char	past_char(FILE *flux, int mode);

FILE	*new_flux(char *name, char *mode)
{
	FILE	*flux;
	char	c;

	flux = fopen(name, mode);
	if (!flux)
		return (NULL);
	fseek(flux, 0, SEEK_END);
	c = past_char(flux, 0);
	while (c == '\n')
	{
		past_char(flux, 1);
		c = past_char(flux, 0);
	}
	return (flux);
}

// mode:
// 0 -> don't move the head reader
// 1 -> move the head reader
char	past_char(FILE *flux, int mode)
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

char	next_char(FILE *flux, int mode)
{
	char	buff[2] = {0};
	int		rd_bytes;

	rd_bytes = fread(buff, sizeof(char), 1, flux);
	if (rd_bytes < 1)
		return (0);
	if (mode == 1)
	{
		if (fseek(flux, -1, SEEK_CUR))
			return (-1);
	}
	return (buff[0]);
}

int	getidx_past_line(FILE *flux)
{
	char	c;
	int		size;
	char	buff[2] = {0};
	long	pos;

	size = 0;
	while ((c = past_char(flux, 0)) != '\n' && c > 0) // on sort de la ligne actuelle
		past_char(flux, 1);
	if (c != '\n')
		return (0);
	past_char(flux, 1); // on passe apres le '\n'
	while ((c = past_char(flux, 0)) != '\n' && c > 0) // on lit la ligne (jusqu'au bout ou '\n')
	{
		size++;
		past_char(flux, 1);
	}
	return (size);
}

int	getidx_next_line(FILE *flux)
{
	char	c;
	int		size;
	char	buff[2] = {0};
	long	pos;

	size = 0;
	while ((c = next_char(flux, 0)) != '\n' && c > 0) // on sort de la ligne actuelle
		next_char(flux, 1);
	if (c != '\n')
		return (0);
	next_char(flux, 1); // on passe apres le '\n'
	pos = ftell(flux);
	while ((c = next_char(flux, 0)) != '\n' && c > 0) // on lit la ligne (jusqu'au bout ou '\n')
	{
		size++;
		next_char(flux, 1);
	}
	fseek(flux, pos, SEEK_SET);
	return (size);
}

// mode:
// 0 = next line
// 1 = past line
char	*line_from_stream(FILE *flux, int mode)
{
	int		i;
	int		size;
	char	*line;

	if (mode)
		size = getidx_past_line(flux);
	else
		size = getidx_next_line(flux);
	if (!size)
		return (NULL);
	line = malloc(sizeof(char) * (size + 1));
	if (!line)
		return (NULL);
	for (i = 0; i < size; i++)
		line[i] = next_char(flux, 0);
	line[i] = 0;
	return (line);
}

char	*read_first_line(FILE *flux)
{
	char	c;
	int		i;
	int		size;
	char	*line;

	size = 0;
	while ((c = past_char(flux, 0)) != '\n' && c > 0)
	{
		size++;
		past_char(flux, 1);
	}
	line = malloc(sizeof(char) * (size + 1));
	if (!line)
		return (NULL);
	for (i = 0; i < size; i++)
		line[i] = next_char(flux, 0);
	line[i] = 0;
	return (line);
}

int	main(int ac, char **av)
{
	FILE	*flux;
	char	*ln;
	char	c;

	if (ac != 2)
		return (0);

	flux = new_flux(av[1], "a+");
	if (!flux)
		return (-1);
	
	ln = read_first_line(flux);
	printf("first line is $%s$\n", ln);
	free(ln);

	for (int i = 0; i < 5; i++)
	{
		ln = line_from_stream(flux, 1);
		printf("ln.%d $%s$\n", i, ln);
		free(ln);
	}

	for (int i = 0; i < 5; i++)
	{
		ln = line_from_stream(flux, 0);
		printf("ln.%d $%s$\n", i, ln);
		free(ln);
	}

	fclose(flux);
	return (0);
}
