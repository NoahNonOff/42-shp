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

// len of shell name + 2 (ex: sh (len = 2) + 2) --> LEN_NAME = 4
# ifndef LEN_NAME
#  define LEN_NAME 4
# endif

/* ========== struct ========== */

typedef struct
{
	int		ret;
	char	**env;
	char	*dir_pos;
}	t_simul;

/* ========== protos ========== */			//	(informations about files)

/*----------- shell ------------*/			//	(main shell code)
void	free_glob(void);

/*---------- readline -------------*/		//	(readline functions)
char	*readline(char *prompt);
void	add_history(char *line);
void	clear_history(void);

/*------------ funct -------------*/		//	(specified functions)
char	*p_getenv(char *str, char **tab);

/*------------ utils -------------*/		//	(generic functions)
int		ft_strlen(char *str);
void	putstr_fd(char *str, int fd);
void	*free_tab(char **tab);
int		comp(const char *s1, const char *s2);
char	*ft_strdup(char *str);
char	*substring(char *str, int start, int end);
char	*read_one_line(int fd);
char	**ft_split(char const *s, char c);

#endif
