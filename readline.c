#include "shell.h"

extern t_simul	g_shell;

/*------------- proto ---------------*/
void	write_prompt(char *prompt);

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

char	*readline(char *prompt)
{
	char	*ret;

	ret = NULL;
	write_prompt(prompt);
	ret = read_line(FDIN);
	return (ret);
}
