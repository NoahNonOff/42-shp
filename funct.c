#include "shell.h"

/*------------- proto ---------------*/

/* ================================= */

char	*p_getenv(char *str, char **tab)
{
	int	i;
	int	idx;

	idx = 0;
	if (!str)
		return (NULL);
	while (tab && tab[idx])
	{
		i = 0;
		while (str[i] && tab[idx][i] && str[i] == tab[idx][i])
			i++;
		if (tab[idx][i] && tab[idx][i + 1] && tab[idx][i + 1] == '=')
			if (ft_strlen(tab[idx]) >= i + 2)
				return (substring(tab[idx], i + 2, -1));
		idx++;
	}
	return (NULL);
}

char	*cat_line(char *line, int pos, char c)
{
	int		i;
	int		len;
	char	*newline;

	i = 0;
	len = ft_strlen(line);
	if (pos > len)
		pos = len;
	newline = malloc(sizeof(char) * (len + 2));
	if (!newline)
		return (NULL);
	for (; line && i < pos; i++)
		newline[i] = line[i];
	newline[i++] = c;
	for (; line && line[i - 1]; i++)
		newline[i] = line[i - 1];
	newline[i] = 0;
	free(line);
	return (newline);
}

char	*remove_one(char *line, int pos)
{
	int		i;
	int		len;
	char	*newline;

	i = 0;
	if (pos == 0)
		return (line);
	len = ft_strlen(line);
	if (pos > len)
		pos = len;
	newline = malloc(sizeof(char) * (len));
	if (!newline)
		return (NULL);
	for (; line && i < pos - 1; i++)
		newline[i] = line[i];
	for (; line && line[i + 1]; i++)
		newline[i] = line[i + 1];
	newline[i] = 0;
	free(line);
	return (newline);
}

char	*path_join(char const *s1, char const *s2)
{
	int		i, len1, len2;
	char	*ret;

	i = -1;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ret = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ret)
		return (NULL);
	while (++i < len1)
		ret[i] = s1[i];
	i = -1;
	while (++i < len2)
		ret[len1 + i] = s2[i];
	ret[len1 + len2] = 0;
	return (ret);
}
