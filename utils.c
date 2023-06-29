#include "shell.h"

/*------------- proto ---------------*/
char	*add_char(char *str, char c);

/* ================================= */

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

char	*add_char(char *str, char c)
{
	int		len;
	char	*ret;

	len = ft_strlen(str) + 2;
	ret = malloc(sizeof(char) * len);
	if (!ret)
	{
		free(str);
		return (NULL);
	}
	for (int i = 0; str && str[i]; i++)
		ret[i] = str[i];
	ret[len - 2] = c;
	ret[len - 1] = 0;
	free(str);
	return (ret);
}

char	*read_one_line(int fd)
{
	char	*ret;
	int		rd_bytes;
	char	buff[2] = {0};

	ret = NULL;
	rd_bytes = 0;
	rd_bytes = read(fd, buff, 1);
	while (rd_bytes > 0 && buff[0])
	{
		if (buff[0] == '\n')
			break ;
		ret = add_char(ret, buff[0]);
		if (!ret)
			break ;
		rd_bytes = read(fd, buff, 1);
	}
	return (ret);
}

/* ------------- ft_split ------------- */

static int	len_sep_string(const char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
		{
			counter++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (counter + 1);
}

static char	*get_next_word(int *index, const char *str, char c)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = 0;
	while (str[*index] == c)
		(*index)++;
	while (str[*index + len] != c && str[*index + len])
		len++;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
		ret[i++] = str[(*index)++];
	ret[i] = 0;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		ac;
	char	**ret;

	i = 0;
	j = 0;
	ac = len_sep_string(s, c);
	ret = malloc(ac * sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < ac - 1)
	{
		ret[i++] = get_next_word(&j, s, c);
		if (!ret[i])
			return (free_tab(ret));
	}
	ret[i] = NULL;
	return (ret);
}

/* ------------------------------------ */
