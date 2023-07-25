#include "readline.h"

t_readline	rd_readline_init(char *prompt);

/*------------- proto ---------------*/

/* ================================= */

char	**rd_list_files(char *curr_dir, t_readline *rdl)
{
	DIR				*dirp;
	char			**ret;
	struct dirent	*entity;

	ret = NULL;
	dirp = opendir(curr_dir);
	while (1)
	{
		entity = readdir(dirp);
		if (!entity)
			break ;
		else if (rdl->cursor && rd_compn(rdl->line, entity->d_name, rdl->cursor - 1))
			continue ;
		ret = rd_tabPush(ret, entity->d_name);
		if (!ret)
			break ;
	}
	closedir(dirp);
	return (ret);
}

void	rd_auto_compl(t_readline *rdl)
{
	int		len = 0;
	char	**ret;

	ret = rd_list_files(".", rdl);
	while (ret && ret[len])
		len++;

	if (!len)
		return ;

	rd_putstr_fd("\033[s", FDIN); // Save cursor location
	rd_putstr_fd("\033[J", FDIN); // Erase display (cursor -> END)

	if (len == 1) {
		free(rdl->line);
		rdl->line = ret[0];
		rdl->cursor = rd_strlen(rdl->line);
	}
	else {
		for (int i = 0; ret && ret[i]; i++) {
			if (!(i % 6))
				rd_putstr_fd("\n", FDIN);
			rd_putstr_fd(ret[i], FDIN);
			rd_putstr_fd("\t", FDIN);
		}
		rd_free_tab(ret);
	}
	rd_putstr_fd("\033[u", FDIN); // Restore cursor location
}

char	*rd_extract_word(t_readline *rdl, int *n)
{
	int		i;
	char	*ret;

	i = rdl->cursor;
	while (rdl->line && i > -1)
}
