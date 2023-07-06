#include "shell.h"

t_simul	g_shell;

/*------------- proto ---------------*/
int		shell_init(int ac, char **av, char **env);
char	**duplicate_tab(char **tab);
int		action(char *str);

/* ================================= */

int	shell_init(int ac, char **av, char **env)
{
	char	*pos;

	(void)av;
	if (ac != 1)
	{
		putstr_fd("error: args: too many arguments\n", FDERR);
		return (-1);
	}
	g_shell.ret = 0;
	g_shell.env = duplicate_tab(env);
	if (!g_shell.env)
		return (-1);
	pos = p_getenv("PWD", env);
	if (pos)
	{
		g_shell.dir_pos = substring(pos, 0, ft_strlen(pos) - LEN_NAME);
		free(pos);
		if (!g_shell.dir_pos)
		{
			free_tab(g_shell.env);
			return (-1);
		}
	}
	else
	{
		free_tab(g_shell.env);
		return (-1);
	}
	return (0);
}

void	free_glob(void)
{
	if (g_shell.env)
		free_tab(g_shell.env);
	if (g_shell.dir_pos)
		free(g_shell.dir_pos);
}

char	**duplicate_tab(char **tab)
{
	int		len;
	char	**ret;

	len = -1;
	while (tab && tab[++len])
		;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	for (int i = 0; tab && tab[i]; i++)
	{
		ret[i] = ft_strdup(tab[i]);
		if (!ret[i])
			return (free_tab(ret));
	}
	ret[len] = NULL;
	return (ret);
}

int	action(char *str)
{
	putstr_fd(str, FDIN);
	putstr_fd("\n", FDIN);

	if (!comp(str, "0"))
		g_shell.ret = 0;
	else if (!comp(str, "1"))
		g_shell.ret = 1;
	else if (!comp(str, "exit"))
		return (0);
	else if (!comp(str, "env"))
	{
		for (int i = 0; g_shell.env[i]; i++)
			printf("%s\n", g_shell.env[i]);
	}
	else if (!comp(str, "sound"))
		write(0, "\x07", 1);
	else if (!comp(str, "clear"))
		write(1, "\033c", 2);
	return (1);
}

int	history_string(char *str)
{
	int	space;

	space = 0;
	for (int i = 0; str && str[i]; i++)
		if (!((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
			space++;
	return (space);
}

int	main(int ac, char **av, char **env)
{
	char	*str;

	if (shell_init(ac, av, env) == -1)
		return (2);
	while (1)
	{
		str = readline("sh");
		if (!str)
			continue ;
		if (comp(str, "\n"))
		{
			if (!action(str))
				break ;
			if (history_string(str))
				add_history(str);
		}
		free(str);
	}
	free(str);
	free_glob();
	return (0);
}
