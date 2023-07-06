# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdarg.h>
# include <termios.h>
# include <curses.h>

# include <dirent.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	putstr_fd(char *str, int fd)
{
	if (!str || fcntl(fd, F_GETFD) == -1)
		return ;
	for (int i = 0; str[i]; i++)
		write(fd, &str[i], 1);
}

void	*free_tab(char **tab)
{
	for (int i = 0; tab && tab[i]; i++)
		free(tab[i]);
	free(tab);
	return (NULL);
}

int	comp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	while ((t1[i] && t2[i]) && (t1[i] == t2[i]))
		i++;
	return (t1[i] - t2[i]);
}

char	*ft_strdup(char *str)
{
	int		len;
	char	*ret;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (int i = 0; str && str[i]; i++)
		ret[i] = str[i];
	ret[len] = 0;
	return (ret);
}

/* ======================================== */

char	**tdtab_push(char **tab, char *to_add)
{
	int		len;
	char	**ret;

	len = 0;
	while (tab && tab[len])
		len++;
	ret = malloc(sizeof(char *) * (len + 2));
	if (!ret)
		return (NULL);
	len = 0;
	while (tab && tab[len])
	{
		ret[len] = tab[len];
		if (!ret[len++])
			return (free_tab(ret));
	}
	ret[len] = ft_strdup(to_add);
	if (!ret[len++])
		return (free_tab(ret));
	ret[len] = NULL;
	free(tab);
	return (ret);
}

int	begin_match(char *file, char *str)
{
	int	i;

	i = 0;
	if (!file || !str)
		return (0);
	while (file[i] && str[i] && file[i] == str[i])
		i++;
	if (str[i] && file[i] && file[i] != str[i] || (!file[i] && str[i]))
		return (0);
	return (1);
}

char	**curr_files(char *str)
{
	struct dirent	*entity;
	DIR 			*folder;
	char			**ret;

	ret = NULL;
    folder = opendir(".");
	while (1)
	{
		entity = readdir(folder);
		if (!entity)
			break ;
		if (begin_match(entity->d_name, str))
		{
			ret = tdtab_push(ret, entity->d_name);
			if (!ret)
				break ;
		}
	}
	closedir(folder);
	return (ret);
}

int	main(int ac, char **av)
{
	char	**tab_list;

	if (ac != 2)
		return (0);
	tab_list = curr_files(av[1]);
	if (!tab_list)
		printf("no one match\n");
	else
		for (int i = 0; tab_list && tab_list[i]; i++)
			printf("%s\n", tab_list[i]);
	free_tab(tab_list);
	return (0);
}
