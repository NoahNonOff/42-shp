#include "readline.h"

t_readline	rd_readline_init(char *prompt);

/*------------- proto ---------------*/

/* ================================= */

char	**rd_list_files(char *curr_dir, char *line, int cursor)
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
		else if (cursor && rd_compn(line, entity->d_name, cursor - 1))
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

	ret = rd_list_files(".", rdl->line, rdl->cursor);
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

/* ================================================ */

int	rd_is_sep(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ' || c == ';' || c == 34 || c == 39);
}

static int	rd_len_sep_string(const char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (rd_is_sep(str[i]))
			i++;
		if (!rd_is_sep(str[i]) && str[i])
		{
			counter++;
			while (!rd_is_sep(str[i]) && str[i])
				i++;
		}
	}
	return (counter + 1);
}

static char	*rd_get_next_word(int *index, const char *str, int *tmp)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = 0;
	while (str[*index] && rd_is_sep(str[*index]))
		(*index)++;
	*tmp = *index;
	while (str[*index + len] && !rd_is_sep(str[*index + len]))
		len++;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
		ret[i++] = str[(*index)++];
	ret[i] = 0;
	return (ret);
}

char	**rd_splitLine(char const *s, int cursor, t_auto_compl *cmpl)
{
	int		i;
	int		j;
	int		ac;
	int		tmp;
	char	**ret;

	i = 0;
	j = 0;
	ac = rd_len_sep_string(s);
	ret = malloc(ac * sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < ac - 1)
	{
		ret[i] = rd_get_next_word(&j, s, &tmp);
		if (cmpl->n == -1 && cursor <= j)
		{
			cmpl->n = i;
			cmpl->pos = j - (rd_strlen(ret[i]) + 1);
			if (1 == ac - 2)
				cmpl->pos++;
			cmpl->pos = cursor - cmpl->pos;
			cmpl->begin_word = tmp;
		}
		i++;
	}
	if (cmpl->pos < 0)
		cmpl->n = -1;
	ret[i] = NULL;
	return (ret);
}

t_auto_compl	*rd_extract_word(char *line, int cursor)
{
	int				i;
	t_auto_compl	*ret;

	i = 0;
	while (line[i] && rd_is_sep(line[i]))
		i++;
	if (!line[i])
		return (NULL);

	ret = malloc(sizeof(t_auto_compl));
	if (!ret)
		return (NULL);

	ret->pos = -1;
	ret->n = -1;

	ret->words = rd_splitLine(line, cursor, ret);
	if (!ret->words) {
		free(ret);
		return (NULL);
	}
	return (ret);
}

void	new_auto_compl(t_readline *rdl)
{
	int				len = 0;
	char			**ret;
	t_auto_compl	*cmpl;

	cmpl = rd_extract_word(rdl->line, rdl->cursor);
	if (cmpl)
		return ;

	if (cmpl->n == -1) {
		free(cmpl);
		return ;
	}

	ret = rd_list_files(".", cmpl->words[cmpl->n], cmpl->pos);
	while (ret && ret[len])
		len++;

	if (!len) {
		free(cmpl);
		return ;
	}

	rd_putstr_fd("\033[s", FDIN); // Save cursor location
	rd_putstr_fd("\033[J", FDIN); // Erase display (cursor -> END)

	if (len == 1) {
		// replace_word(cmpl, ret[0], rdl);
	}
	else {
		for (int i = 0; ret && ret[i]; i++) {
			if (!(i % 6))
				rd_putstr_fd("\n", FDIN);
			rd_putstr_fd(ret[i], FDIN);
			rd_putstr_fd("\t", FDIN);
		}
	}
	free(cmpl);
	rd_free_tab(ret);
	rd_putstr_fd("\033[u", FDIN); // Restore cursor location
}

/* ========================================================= */

/*
int	main(int ac, char **av)
{
	if (ac != 3)
		return (1);
	t_auto_compl	*ptr = rd_extract_word(av[1], atoi(av[2]));

	for (int i = 0; ptr->words && ptr->words[i]; i++)
		printf("%s\n", ptr->words[i]);
	printf("pos = %d\n", ptr->pos);
	printf("n = %d\n", ptr->n);
	printf("begin_word = %d\n", ptr->begin_word);

	char	**ret = rd_list_files(".", ptr->words[ptr->n], ptr->pos);
	for (int i = 0; ret && ret[i]; i++)
		printf("%s\n", ret[i]);

	rd_free_tab(ret);
	rd_free_tab(ptr->words);
	free(ptr);

	return (0);
}
*/