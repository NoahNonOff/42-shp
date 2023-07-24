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

	rd_putstr_fd("\033[s", FDIN); // save pos
	rd_putstr_fd("\033[J", FDIN); // efface tous apres le curseur

	if (len == 1) {
		free(rdl->line);
		rdl->line = ret[0];
		rdl->cursor = rd_strlen(rdl->line);
	}
	else {
		for (int i = 0; ret && ret[i]; i++) { // mult posibilities don't work
			if (!(i % 6))
				rd_putstr_fd("\n", FDIN);
			rd_putstr_fd(ret[i], FDIN);
			rd_putstr_fd("\t", FDIN);
		}
		rd_free_tab(ret);
	}
	rd_putstr_fd("\033[u", FDIN); // restore pos
}



/*

int	main(int ac, char **av)
{
	char	**ret;
	t_readline	rdl = rd_readline_init("test");

	rdl.line = "az";
	rdl.cursor = 1;
	rd_putstr_fd("->", 1);
	write(1, "\0337", 2); // alrd
	rd_putstr_fd("\033[s", 1); // save pos
	rd_putstr_fd("\n", 1);
	ret = rd_list_files(".", &rdl);
	for (int i = 0; ret && ret[i]; i++)
		printf("%s\t",ret[i]);
	fflush(stdout);
	rd_free_tab(ret);
	rd_putstr_fd("\033[u", 1); // return to his pos
	write(1, "\0338", 2); // alrd
	write(1, "\033[K", 3); // alrd
	sleep(2);
	rd_putstr_fd("\033[J", 1); // efface tous apres le curseur

	return (0);
}*/
