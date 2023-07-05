#include "shell.h"

extern t_simul	g_shell;

/*------------- proto ---------------*/
void	write_prompt(char *prompt);
void	rd_files_manager(void);

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

char	*readline(char *prompt)
{
	char	*ret;

	ret = NULL;
	write_prompt(prompt);
	ret = read_one_line(FDIN);
	rd_files_manager();
	return (ret);
}
