#include "shell.h"

t_simul	g_shell;

/*------------- proto ---------------*/

/* ================================= */

int	shell_init(int ac, char **av, char **env)
{
	(void)av;
	(void)env;
	if (ac != 1)
		putstr_fd("error: args: too many arguments\n", FDERR);
	g_shell.ret = 0;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*str;

	if (shell_init(ac, av, env) == -1)
		return (2);
	while (1)
	{
		str = readline("shell");
		if (!str)
			return (-1);
		putstr_fd(str, FDIN);
		putstr_fd("\n", FDIN);
		if (!comp(str, "0"))
			g_shell.ret = 0;
		else if (!comp(str, "1"))
			g_shell.ret = 1;
		else if (!comp(str, "exit"))
			break ;
		free(str);
	}
	free(str);
	return (0);
}
