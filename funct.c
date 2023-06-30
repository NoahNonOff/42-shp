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
