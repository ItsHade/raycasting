#include "../include/raycasting.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void    ft_putchar(char c)
{
    write (1, &c, 1);
}

void    ft_putstr(char *str)
{
	write (1, str, ft_strlen(str));
}

void	ft_putstr_fd(char *str, int fd)
{

	write (fd, str, ft_strlen(str));
}
