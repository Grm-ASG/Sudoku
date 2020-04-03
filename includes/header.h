#ifndef HEADER_H
# define HEADER_H

# define ERR "Error\n"

# include <stdlib.h>

typedef	struct		s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	char		res;
	int		i;
	int		j;
}			t_list;

void			ft_sudoku(char **argv);
void			ft_putstr(char *str);
void			ft_putchar(char c);

#endif
