#include "shell.h"

extern t_simul	g_shell;

/*------------- proto ---------------*/
void		write_prompt(char *prompt);
void		rd_files_manager(void);
t_readline	readline_init(void);
char		extract_char(void);
void		do_backspace(t_readline *rdl);
void		move_cursor(t_readline *rdl);
void		treat_char(char c, t_readline *rdl);

/* ================================= */
void	write_prompt(char *prompt)
{
	if (!g_shell.ret)
		putstr_fd("\x1B[1m\x1B[32m➜  \x1B[36m", FDOUT);
	else
		putstr_fd("\x1B[1m\x1B[31m➜  \x1B[36m", FDOUT);
	putstr_fd(prompt, FDOUT);
	putstr_fd("\x1B[0m ", FDOUT);
}

void	rd_files_manager(void)
{
	int			fd;
	struct stat	st = {0};

	if (stat(".42sh", &st) == -1)
		mkdir(".42sh", 0755);
	if (access(".42sh/.history", F_OK) == -1)
	{
		fd = open(".42sh/.history", O_RDWR | O_CREAT | O_APPEND, 0644);
		close(fd);
	}
}

void	add_history(char *line)
{
	int	fd;

	fd = open(".42sh/.history", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	putstr_fd("\n", fd);
	putstr_fd(line, fd);
	close(fd);
}

void	clear_history(void)
{
	int	fd;

	fd = open(".42sh/.history", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	close(fd);
}

t_readline	readline_init(void)
{
	t_readline	ret;

	ret.begin_pos = LEN_NAME + 3;
	ret.cursor = 0;
	ret.line = NULL;
	ret.flx = 0;
	ret.flux = NULL;
	return (ret);
}

char	extract_char(void)
{
	char	c;
	struct termios	oldt;
	struct termios	newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	c = getchar();
	if (c == '\033')
	{
		getchar(); // skip the '['
		switch (getchar())
		{
			case 'A':
				c = -1;
				break;
			case 'B':
				c = -2;
				break;
			case 'C':
				c = -3;
				break;
			case 'D':
				c = -4;
				break;
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (c);
}

void	do_backspace(t_readline *rdl)
{
	rdl->line = remove_one(rdl->line, rdl->cursor);
	if (rdl->cursor > 0)
		rdl->cursor--;
	close_flux(rdl);
}

void	move_cursor(t_readline *rdl)
{
	int	move;

	move = ft_strlen(rdl->line) - rdl->cursor;
	for (int i = 0; i < move; i++)
		printf("\033[1D");
	fflush(stdout);
}

void	close_flux(t_readline *rdl)
{
		if (rdl->flx)
			fclose(rdl->flux);
		rdl->flux = NULL;
		rdl->flx = 0;
}

void	treat_char(char c, t_readline *rdl)
{
	if (c == -1) // up
		find_in_index(rdl, 1);
	else if (c == -2) // down
		find_in_index(rdl, 0);
	else if (c == -3 && (rdl->cursor < ft_strlen(rdl->line))) // right
		rdl->cursor++;
	else if (c == -4 && rdl->cursor > 0) // left
		rdl->cursor--;
	else if (c == 127)
		do_backspace(rdl);
	else if (c > 0)
	{
		rdl->line = cat_line(rdl->line, rdl->cursor++, c);
		close_flux(rdl);
	}
	write(1, "\0338", 2);
	write(1, "\033[K", 3);
	putstr_fd(rdl->line, FDIN);
	move_cursor(rdl);
}

char	*readline(char *prompt)
{
	char		c;
	t_readline	rdl;

	rdl = readline_init();
	rd_files_manager();
	write_prompt(prompt);
	write(1, "\0337", 2);
	while ((c = extract_char()) && c != '\n')
		treat_char(c, &rdl);
	rd_files_manager();
	close_flux(&rdl);
	write(1, "\n", 1);
	return (rdl.line);
}
