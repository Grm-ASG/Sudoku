#include "header.h"
int             ft_duplicate_simb(char **argv, char ****map, int i, int j)
{
    if (j == 8 && argv[i][j+1] != '\0' ||
    ((argv[i][j] < '0' && argv[i][j] != '.') ||
    (argv[i][j] > '9' && argv[i][j] != '.')))
        return (0);
    **map[i][j] = argv[i][j];
    if (j == 8)
        **map[i][j+1] = '\0';
}

int             ft_map(char **argv, char ***map)
{
    int i, j;

    i = 1;
    while(i <= 9)
    {
        j = 0;
        while(j < 9)
        {
            if (!(ft_duplicate_simb(argv, &map, i, j)))
            {
                ft_putstr(ERR);
                return (0);
            }
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

void			ft_sudoku(char **argv)
{
    char    **map;
    int     i;

    i = 0;
    map = (char **)malloc(sizeof(char *) * 10);
    while(i < 10)
    {
        map[i] = (char *)malloc(sizeof(char) * 10);
        if (map[i] == NULL)
        {
            free(map);
            return ;
        }
        i++;
    }
    if (map == NULL)
        return ;
    if (ft_map(argv, &map))
    {
        ft_solve_sudoku(&map);
        ft_print_sudoku(map);
    }
    free(map);
}
