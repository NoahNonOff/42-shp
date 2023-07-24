#ifndef __SHELL__H__
# define __SHELL__H__

/* ========== includes ========== */
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

typedef struct
{
	int		begin_pos; // LEN_NAME + 3
	int		cursor;
	char	*line;
	int		flx;
	FILE	*flux;
}	t_readline;

/* ========== protos ========== */

/*----------- shell ------------*/
void	free_glob(void);

/*---------- readline -------------*/
char	*readline(char *prompt, int ret);
void	add_history(char *line);
void	clear_history(void);
void	close_flux(t_readline *rdl);

/*--------- read_history ----------*/
FILE	*new_flux(char *name, char *mode);
char	*line_from_stream(FILE *flux, int mode);
char	*read_first_line(FILE *flux);
void	find_in_index(t_readline *rdl, int mode);
int		is_past_command(char *cmd);

/*------------ funct -------------*/
char	*p_getenv(char *str, char **tab);
char	*cat_line(char *line, int pos, char c);
char	*remove_one(char *line, int pos);

/*------------ utils -------------*/
char	*try_path(char *cmd, char **env);
char	*get_path(char *cmd, char **env);

/*------------ utils -------------*/
int		ft_strlen(char *str);
void	putstr_fd(char *str, int fd);
void	*free_tab(char **tab);
int		comp(const char *s1, const char *s2);
char	*ft_strdup(char *str);
char	*substring(char *str, int start, int end);
char	*read_one_line(int fd);
char	**ft_split(char const *s, char c);

#endif
