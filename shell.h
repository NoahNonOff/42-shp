#ifndef __READLINE__H__
# define __READLINE__H__

/* ========== includes ========== */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdarg.h>

/* ========== define ========== */
# ifndef FDIN
#  define FDIN 0
# endif

# ifndef FDOUT
#  define FDOUT 1
# endif

# ifndef FDERR
#  define FDERR 2
# endif

/* ========== struct ========== */

typedef struct
{
	int	ret;
}	t_simul;

/* ========== protos ========== */

/*---------- readline -------------*/
char	*readline(char *prompt);

/*------------ utils -------------*/
int		ft_strlen(char *str);
void	putstr_fd(char *str, int fd);
void	*free_tab(char **tab);
int		comp(const char *s1, const char *s2);
char	*read_line(int fd);
char	**ft_split(char const *s, char c);

#endif
