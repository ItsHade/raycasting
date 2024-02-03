//https://www.youtube.com/watch?v=JPAyj85tJ5E&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=1

#ifndef SLASH_H
# define SLASH_H

#include <SDL.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

# define PI 3.14159265359

typedef struct
{
	int	mapx;
	int	mapy;
	int	maps;
	int	*map;
}	t_minimap;

typedef struct
{
	int width, height;
	char *name;
	SDL_Window *window;
} t_window;


typedef struct
{
	double	x;
	double	y;
	double	deltax;
	double	deltay;
	double	angle;
	int size; // 
} t_player;

typedef struct
{
	//Players
	t_player player;
	t_window window;
	t_minimap map;

	//Images
	SDL_Texture *star;
	SDL_Renderer *renderer;
} GameState;

/* PUT FUNCTIONS */

int		ft_strlen(char *str);

void	ft_putchar(char c);

void	ft_putstr(char *s);

void	ft_putstr_fd(char *s, int fd);


#endif
