#include "shell.h"

char	*try_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	*path;
	char	**all_path;

	i = -1;
	path = p_getenv("PATH", env);
	if (!path)
		return (putstr_fd(cmd, 2), putstr_fd(": command not found\n", 2));
	all_path = ft_split(path, ';');
	free(path);
	if (!all_path)
		return (perror("malloc"));
	while (all_path[++i])
	{
		path = path_join(all_path[i], "/");
		if (!path)
			return (free_tab(all_path));
		exec = path_join(path, cmd);
		free(path);
		if (!exec)
			return (free_tab(all_path));
		if (!access(exec, F_OK | X_OK))
			return (exec);
		free(exec);
	}
	free_tab(all_path);
	return (cmd);
}

char	*get_path(char *cmd, char **env)
{
	char	*new_path;

	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	new_path = try_path(cmd, env);
	if (!new_path)
		return (NULL);
	else if (!(new_path == cmd))
		free(cmd);
	return (new_path);
}
