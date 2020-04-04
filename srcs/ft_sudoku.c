#include "header.h"
#include <stdio.h>

int			 ft_duplicate_simb(char **argv, char **map, int i, int j)
{
	if ((j == 8 && argv[i+1][j+1] != '\0') ||
	((argv[i+1][j] < '0' || argv[i+1][j] > '9') && argv[i+1][j] != '.'))
	{
		return (1);
	}
	map[i][j] = argv[i+1][j];
	if (j == 8)
		map[i][j+1] = '\0';
	return (0);
}

void			ft_print_sudoku(char **map)
{
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			ft_putchar(map[i][j]);
			if (map[i][j+1] != '\0')
				ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

char			**ft_create_map(void)
{
	char	**map;
	int	 i;

	i = 0;
	map = (char **)malloc(sizeof(char *) * 10);
	if (!(map == NULL))
	{
		while (i < 9) {
			map[i] = (char *)malloc(sizeof(char) * 10);
			if (map[i] == NULL)
			{
				free(map);
				return (NULL);
			}
			i++;
		}
		map[9] = '\0';
	}
	return (map);
}

char		ft_horiz(char **map, char res, int i, int j)
{
	j = 0;

	while (map[i][j])
	{
		if (res == map[i][j++])
			return (0);
	}
	return (1);
}

char		ft_vert(char **map, char res, int i, int j)
{
	i = 0;

	while(i < 9)
	{
		if (res == map[i++][j])
			return (0);
	}
	return (1);
}

char		ft_cube(char **map, char res, int i, int j)
{
	int a;
	int b;
	int z;
	int x;

	a = i  / 3 + 1;
	b = j  / 3 + 1;
	z = 0;
	while (a * 3 - 3 + z <= a * 3 - 1)
	{
		x = 0;
		while (b * 3 - 3 + x <= b * 3 - 1)
		{
			if (res == map[a * 3 - 3 + z][b * 3 - 3 + x++])
				return (0);
		}
		z++;

	}
	return (1);
}

char		ft_check_all(char **map, int i, int j, char *res)
{
	while (*res <= '9')
	{
		if (ft_horiz(map, *res, i, j) &&
		ft_vert(map, *res, i, j) &&
		ft_cube(map, *res, i, j))
			return (*res);
		(*res) += 1;
	}
	return ('0');
}

char		ft_check(char **map, int *i, int *j, char res)
{
	while (*i < 9)
	{
		while (*j < 9)
		{
			if (map[*i][*j] == '.')
			{
				return(ft_check_all(map, *i, *j, &res));
			}
			(*j)++;
		}
		*j = 0;
		(*i)++;
	}
	return ('0');
}

void			ft_remove_i_j(int *i, int *j, t_list **pp_back_up, char *res, int *flag)
{
	t_list *pp_list;

	pp_list = *pp_back_up;
	while ((pp_list->i != *i || pp_list->j != *j) && pp_list->next != NULL)
		pp_list = pp_list->next;
	*i = pp_list->prev->i;
	*j = pp_list->prev->j;
	*res = pp_list->prev->res + 1;
	pp_list->prev->res = '.';
	if (pp_list->prev->prev == NULL)
		*flag = 1;
}

void			ft_guess_to_list(char guess, t_list **pp_back_up, int i, int j)
{
	t_list *pp_list;

	pp_list = *pp_back_up;
	while ((pp_list->i != i || pp_list->j != j) && pp_list->next != NULL)
		pp_list = pp_list->next;
	pp_list->res = guess;

}

void			ft_list_clear(t_list **begin_list)
{
	t_list *tmp;

	if (!*begin_list || !begin_list)
		return ;
	while (*begin_list)
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp);
	}
}

char			**ft_solve_sudoku(char **map, int blank, t_list **pp_list)
{
	char	guess;
	char	res;
	int	flag;
	int	fs_fl;
	int	i;
	int	j;

	res = '1';
	i = 0;
	j = 0;
	fs_fl = 1;
	flag = 0;
	while (blank)
	{
		guess = ft_check(map, &i, &j, res);
		if (flag || (guess == '0' && fs_fl))
		{
			flag = 1;
			break;
		}
		else
			fs_fl = 0;
		if (guess == '0')
		{
			ft_remove_i_j(&i, &j, pp_list, &res, &flag);
			map[i][j] = '.';
			blank++;
			continue;
		}
		map[i][j] = guess;
		ft_guess_to_list(guess, pp_list, i, j);
		res = '1';
		blank--;
	}
	if (flag)
		return (0);
	ft_list_clear(pp_list);
	return (map);
}

t_list		*ft_create_elem(char res, int i, int j)
{
	t_list *tmp;

	if ((tmp = malloc(sizeof(t_list))))
	{
		tmp->res = res;
		tmp->next = NULL;
		tmp->prev = NULL;
		tmp->i = i;
		tmp->j = j;
	}
	return (tmp);
}

void			ft_list_push_back(t_list ***ppp_list, int i, int j)
{
	t_list	*tmp;

	tmp = ft_create_elem('.', i, j);
	(**ppp_list)->next = tmp;
	tmp->prev = (**ppp_list);
	(**ppp_list) = tmp;
}

int			ft_map(char **argv, char **map, int *blank, t_list **pp_list)
{
	int		i;
	int		j;
	t_list		**back_up;

	back_up = pp_list;
	*blank = 0;
	i = 0;
	while(i < 9)
	{
		j = 0;
		while(j < 9)
		{
			if (ft_duplicate_simb(argv, map, i, j))
			{
				ft_putstr(ERR);
				return (0);
			}
			if (argv[i+1][j] == '.')
			{
				if ((*blank) == 0)
				{
					(*pp_list) = ft_create_elem('.', i, j);
					if (pp_list == NULL)
					{
						ft_putstr(ERR);
						return (0);
					}
				}
				else
				{
					ft_list_push_back(&pp_list, i, j);
				}
				(*blank)++;
			}
			j++;
		}
		i++;
	}
	if (*blank == 0 || *blank >= 65)
	{
		ft_putstr(ERR);
		return (0);
	}
	while ((*pp_list)->prev != NULL)
			(*pp_list) = (*pp_list)->prev;
	(*back_up) = (*pp_list);
	return (1);
}

void			ft_sudoku(char **argv)
{
	t_list	*p_list;
	char	**map;
	int	blank;

	if ((map = ft_create_map()))
		if (ft_map(argv, map, &blank, &p_list))
		{
			if ((map = ft_solve_sudoku(map, blank, &p_list)))
				ft_print_sudoku(map);
			else
				ft_putstr(ERR);
		}
	free(map);
}
