#include "readline.h"

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
		if (rd_compn(rdl->line, entity->d_name, rdl->cursor))
			continue ;
		ret = rd_tabPush(ret, entity->d_name);
		if (!ret)
			break ;
	}
	return (ret);
}

void	print_match_lst(t_readline *rdl) {
	char	**ret;

	ret = rd_list_files(".", rdl);
	for (int i = 0; ret && ret[i]; i++)
		printf("ret[%d] -> \"%s\"\n", i, ret[i]);
	rd_free_tab(ret);
	fflush(stdout);
}
