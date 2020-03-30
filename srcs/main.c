#include "header.h"

int			main(int argc, char **argv)
{
	if (argc != 10)
	{
		ft_putstr(ERR);
	}
	else
	{
		ft_sudoku(argv);
	}
	return (0);
}
