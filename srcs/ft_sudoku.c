/*delete*/
#include <stdio.h>

typedef struct s_list	t_list;

struct			s_list
{
	t_list	*before;
	t_list	*next;
	char	res;
	int	i;
	int	j;
};

#include "header.h"

int			 ft_duplicate_simb(char **argv, char ****map, int i, int j)
{
	if ((j == 8 && argv[i+1][j+1] != '\0') ||
	((argv[i+1][j] < '0' || argv[i+1][j] > '9') && argv[i+1][j] != '.'))
	{
		return (0);
	}
	(**map)[i][j] = argv[i+1][j];
	if (j == 8)
		(**map)[i][j+1] = '\0';
	return (1);
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
		if (res == map[i][j])
			return (0);
		j++;
	}
	return (1);
}

char		ft_vert(char **map, char res, int i, int j)
{
	i = 0;
	while(i < 9)
	{
		if (res == map[i][j])
			return (0);
		i++;
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
			if (res == map[a * 3 - 3 + z][b * 3 - 3 + x])
				return (0);
			x++;
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

void			ft_remove_i_j(int *i, int *j, t_list **pp_back_up, char *res)
{
	t_list *pp_list;

	pp_list = *pp_back_up;
	while ((pp_list->i != *i || pp_list->j != *j) && pp_list->next != NULL)
	{
		pp_list = pp_list->next;
	}
	*i = pp_list->before->i;
	*j = pp_list->before->j;
	*res = pp_list->before->res + 1;
	pp_list->before->res = '.';
}

void			ft_guess_to_list(char guess, t_list **pp_back_up, int i, int j)
{
	t_list *pp_list;

	pp_list = *pp_back_up;
	while ((pp_list->i != i || pp_list->j != j) && pp_list->next != NULL)
	{
		pp_list = pp_list->next;
	}
	pp_list->res = guess;

}

char			**ft_solve_sudoku(char **map, int blank, t_list **pp_list, t_list *p_last_elem)
{
	char	guess;
	char	res;
	int	i;
	int	j;

	res = '1';
	i = 0;
	j = 0;
	while (p_last_elem->res == '.')
	{
		guess = ft_check(map, &i, &j, res);
		if (guess == '0')
		{
			ft_remove_i_j(&i, &j, pp_list, &res);
			map[i][j] = '.';
			continue;
		}
		map[i][j] = guess;
		ft_guess_to_list(guess, pp_list, i, j);
		res = '1';
		blank--;
	}
	return (map);
}

t_list		*ft_create_elem(char res, int i, int j)
{
	t_list *tmp;

	if ((tmp = malloc(sizeof(t_list))))
	{
		tmp->res = res;
		tmp->next = NULL;
		tmp->before = NULL;
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
	tmp->before = (**ppp_list);
	(**ppp_list) = tmp;
}

int			ft_map(char **argv, char ***map, int *blank, t_list **pp_list, t_list **pp_last_elem)
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
			if (!ft_duplicate_simb(argv, &map, i, j))
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
	(*pp_last_elem) = (*pp_list);
	while ((*pp_list)->before != NULL)
			(*pp_list) = (*pp_list)->before;
	(*back_up) = (*pp_list);
	return (1);
}

void			ft_sudoku(char **argv)
{
	t_list	*p_list;
	t_list	*p_last_elem;
	char	**map;
	int	blank;

	p_list = NULL;
	if ((map = ft_create_map()))
	{
		if (ft_map(argv, &map, &blank, &p_list, &p_last_elem))
		{
			map = ft_solve_sudoku(map, blank, &p_list, p_last_elem);
			ft_print_sudoku(map);
		}
	}
	free(map);
}
