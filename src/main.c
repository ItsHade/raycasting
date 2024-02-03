#include "../include/raycasting.h"

void	init(GameState *game)
{
	int	x = 0;
	int	y;
	int	i = 0;
	char *map[9] =
	{
		"11111111",
		"10000001",
		"10000001",
		"10000001",
		"10000001",
		"10000001",
		"10000001",
		"11111111",
		NULL
	};
	game->map.map = malloc(sizeof(int) * game->map.maps);
	if (!game->map.map)
		exit(-1);
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			game->map.map[i] = map[x][y] - 48;
			ft_putchar(game->map.map[i] + 48);
			i++;
			y++;
		}
		ft_putchar('\n');
		x++;
	}
	game->player.x = 4.5;
	game->player.y = 4.5;
	game->player.angle = 0;
	game->player.deltax = cos(game->player.angle) * 5;
	game->player.deltay = sin(game->player.angle) * 5;
	game->player.size = 80;

	game->map.mapx = 8;
	game->map.mapy = 8;
	game->map.maps = 64;
}

int inputs(GameState *game)
{
	SDL_Event event;
	int done = 0;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_WINDOWEVENT_CLOSE:
			{
				if (game->window.window)
				{
					SDL_DestroyWindow(game->window.window);
					game->window.window = NULL;
					done = 1;
				}
			}
			break;
			case SDL_KEYDOWN:
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						done = 1;
					break;
				}
			}
			break;
			case SDL_QUIT:
				//quit out of the game
				done = 1;
			break;
		}
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT])
	{
		game->player.angle -= 0.1;
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		game->player.deltax = cos(game->player.angle) * 5;
		game->player.deltay = sin(game->player.angle) * 5;

	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		game->player.angle += 0.1;
		if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
		game->player.deltax = cos(game->player.angle) * 5;
		game->player.deltay = sin(game->player.angle) * 5;

	}
	if (state[SDL_SCANCODE_UP])
	{
		game->player.x += game->player.deltax;
		game->player.y += game->player.deltay;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		game->player.x -= game->player.deltax;
		game->player.y -= game->player.deltay;
	}
	return (done);
}

void	render(GameState *game)
{
	//Render display

	//set the drawing color to blue
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);

	//Clear the screen (to blue)
	SDL_RenderClear(game->renderer);

	//set the drawing color to while
	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

	SDL_Rect rect = {game->player.x, game->player.y, 80, 80};
	SDL_RenderFillRect(game->renderer, &rect);

	//We are done drawing, "present" or show to the screen what we've drawn
	SDL_RenderPresent(game->renderer);

}

int	draw_minimap(SDL_Renderer *map_renderer, GameState *game)
{
	int	x;
	int	y;
	int cell = 720 / 8; // 8 being max map_len
	fprintf(stderr, "player x %f, y %f, angle %f, deltax %f, deltay %f\n", game->player.x, game->player.y, game->player.angle, game->player.deltax, game->player.deltay);
	SDL_SetRenderDrawColor(map_renderer, 100, 100, 100, 255);

	//Clear the screen (to blue)
	SDL_RenderClear(map_renderer);
	y = 0;
	while (y < game->map.mapy)
	{
		x = 0;
		while (x < game->map.mapx)
		{
	
			if (game->map.map[y * game->map.mapy + x] == 1)
				SDL_SetRenderDrawColor(map_renderer, 0, 0, 0, 255);
			else
				SDL_SetRenderDrawColor(map_renderer, 255, 255, 255, 255);
			SDL_Rect rect = {y * cell + 1, x * cell + 1, cell - 1, cell - 1};
			SDL_RenderFillRect(map_renderer, &rect);
			x++;
		}
		y++;
	}
	//render player
	SDL_SetRenderDrawColor(map_renderer, 255, 0, 0, 255);
	SDL_Rect player = {game->player.x * cell - 3, game->player.y * cell - 3, 7, 7};
	SDL_RenderFillRect(map_renderer, &player);

	SDL_RenderDrawLine(map_renderer, game->player.x * cell, game->player.y * cell, game->player.deltax * cell * 5, game->player.deltay * cell * 5);

	SDL_RenderPresent(map_renderer);
	return (0);
}

int	main(void)
{
	GameState game;
	SDL_Window *window; //Declare a window
	SDL_Window *minimap;
	SDL_Renderer *renderer; //Declare a renderer
	SDL_Renderer *map_renderer;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) //Initialize SDL2
	{
		fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return (1);
	}
	game.window.width = 1280;
	game.window.height = 720;
	game.window.name = "Raycasting";

	srandom((int)time(NULL));

	//Create an application window with the following settings:
	window = SDL_CreateWindow(game.window.name,		// window title
				1920 / 2,	// initial x position
				0,	// initial y position
				game.window.width,				// width, in pixels
				game.window.height,				// height, in pixels
				0				// flags
				);
	 if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
	minimap = SDL_CreateWindow("Minimap",		// window title
				0,	// initial x position
				0,	// initial y position
				game.window.width,				// width, in pixels
				game.window.height,				// height, in pixels
				0				// flags
				);
	 if (minimap == NULL) {
        printf("Minimap could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	 if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
	map_renderer = SDL_CreateRenderer(minimap, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	 if (map_renderer == NULL) {
        printf("Map_Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
	game.renderer = renderer;
	game.window.window = window;

	init(&game);

	// The window is open: enter program loop (see SDL_PollEvent)
	int done = 0;

	//Event loop
	while (!done)
	{
		//Gravity
		// game.player.y += 5;
		// if (game.player.y + game.player.size > game.window.height)
		// 	game.player.y = game.window.height - game.player.size;
		//Check for events
		done = inputs(&game);

		render(&game);
		draw_minimap(map_renderer, &game);

		//don't burn up the CPU
		// SDL_Delay(10);
	}

	//Shutdown game and unload all memory
	SDL_DestroyTexture(game.star);

	//Close and destroy the window
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(minimap);
	SDL_DestroyRenderer(map_renderer);

	//Clean up
	SDL_Quit();
	free(game.map.map);
	return (0);
}
