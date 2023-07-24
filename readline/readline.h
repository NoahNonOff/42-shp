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

/* ========== struct ========== */

typedef struct
{
	int		begin_pos;
	int		cursor;
	char	*line;
	int		flx;
	FILE	*flux;
}	t_readline;

/* ========== protos ========== */

/*---------- readline -------------*/
char	*readline(char *prompt, int ret);
void	add_history(char *line);
void	clear_history(void);
void	rd_close_flux(t_readline *rdl);

/*--------- read_history ----------*/
FILE	*rd_new_flux(char *name, char *mode);
char	*rd_line_from_stream(FILE *flux, int mode);
char	*rd_read_first_line(FILE *flux);
void	rd_find_in_index(t_readline *rdl, int mode);
int		rd_is_past_command(char *cmd);

/*------------ funct -------------*/
char	*rd_cat_line(char *line, int pos, char c);
char	*rd_remove_one(char *line, int pos);

/*------------ utils -------------*/
int		rd_strlen(char *str);
void	rd_putstr_fd(char *str, int fd);
void	*rd_free_tab(char **tab);
int		rd_comp(const char *s1, const char *s2);
char	*rd_strdup(char *str);
char	*rd_substring(char *str, int start, int end);
char	*rd_read_one_line(int fd);

#endif
