/*delete*/
#include <stdio.h>

#include "header.h"
int             ft_duplicate_simb(char **argv, char ****map, int i, int j)
{
    if ((j == 8 && argv[i][j+1] != '\0') ||
    (argv[i][j] < '0' && argv[i][j] > '9' && argv[i][j] != '.'))
    {
        return (0);
    }
    (**map)[i-1][j] = argv[i][j];
    if (j == 8)
        (**map)[i-1][j+1] = '\0';
    return (1);
}

int             ft_map(char **argv, char ***map, int *blank)
{
    int i, j;

    *blank = 0;
    i = 1;
    while(i <= 9)
    {
        j = 0;
        while(j < 9)
        {
            if (!ft_duplicate_simb(argv, &map, i, j))
            {
                ft_putstr(ERR);
                return (0);
            }
            if (argv[i][j] == '.')
                (*blank)++;
	    j++;
        }
        i++;
    }
    return (1);
}

void            ft_print_sudoku(char **map)
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

char            **ft_create_map(void)
{
    char    **map;
    int     i;

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

	a = (i - 1) / 3 + 1;
	b = (j - 1) / 3 + 1;

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

char		ft_check_all(char **map, int i, int j)
{
	char res;

	res = '1';
	while (res <= '9')
	{
		if (ft_horiz(map, res, i, j) &&
		ft_vert(map, res, i, j) &&
		ft_cube(map, res, i, j))
			return (res);
		res += 1;
	}
	return ('0');
}


char		ft_check(char **map, int *i, int *j)
{
	while (*i < 9)
	{
		while (*j < 9)
		{
			if (map[*i][*j] == '.')
			{
				return(ft_check_all(map, *i, *j));
			}
			(*j)++;
		}
		*j = 0;
		(*i)++;
	}
	return ('0');
}

char            **ft_solve_sudoku(char **map, int blank)
{
	char	guess;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (blank)
	{
		guess = ft_check(map, &i, &j);
		/*delete*/
		ft_print_sudoku(map);
		printf("\nguess = %c | i = %d | j = %d\n-----------------\n", guess, i, j);
		/*delete*/
		map[i][j] = guess;
	}
	return (map);
}

void			ft_sudoku(char **argv)
{
	char    **map;
	int     blank;

	if ((map = ft_create_map()))
	{
		if (ft_map(argv, &map, &blank))
		{
		    map = ft_solve_sudoku(map, blank);
		    ft_print_sudoku(map);
		}
	}
	free(map);
}
