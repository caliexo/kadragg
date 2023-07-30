#include"Soccer.h"


bool Soccer::Start(int argc, char* argv[])
{
	window = nullptr;
	renderer = nullptr;

	SDL_Texture* background_Texture = nullptr;
	SDL_Texture* ball_Texture = nullptr;
	SDL_Texture* player_Texture = nullptr;

	if (!_init(&window, &renderer))
		return false;
	else
		std::cout << "Window and Renderer loaded successfully!" << std::endl;

	background_Texture = _init_Background(&renderer);

	if (background_Texture == nullptr)
		return false;
	else
		std::cout << "Background texture loaded successfully!" << std::endl;


	

	Ball* ball = new Ball{650, 280, ball_WH, ball_WH, ball_Skin};
	SDL_Rect ball_Rect;

	ball_Texture = _init_Object(ball_Skin, &renderer);

	if (ball_Texture == nullptr)
		return false;
	else
		std::cout << "Obj Ball loaded successfully!" << std::endl;

	Player* player = new Player{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f,MOVE_NORMAL_PLAYER,MOVE_RUN_PLAYER, 1000.f, 150,PLAYER_WH, PLAYER_WH, "TEAM1", "LABRON NIGGA" };
	SDL_Rect player_Rect;

	player_Texture = _init_Object(player_Skin, &renderer);

	if (player_Texture == nullptr)
		return false;
	else
		std::cout << "Obj Player loaded successfully!" << std::endl;

	bool quit = false;
	SDL_Event event;

	std::chrono::high_resolution_clock::time_point prevTime;
	float deltaTime = 0.0f;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - prevTime).count();

		prevTime = currentTime;

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, background_Texture, NULL, NULL);//background

		//std::cout << "X: " << player->x << " Y: " << player->y << std::endl;
		ball->_Goal_Check(*ball);

		ball_Rect = { ball->x, ball->y, ball->width, ball->height };
		ball->_ball_Border(*ball, SCREEN_WIDTH, SCREEN_HEIGHT);
		ball->_Reset_Ball(*ball, false);
		
		SDL_RenderCopy(renderer, ball_Texture, NULL, &ball_Rect);//ball

		player->_Update_Pos(static_cast<float>(deltaTime), *player);
		player->_player_Border(*player, SCREEN_WIDTH, SCREEN_HEIGHT);
		player->_Touch_Ball(*player, *ball, deltaTime);

		player_Rect = { static_cast<int>(player->x), static_cast<int>(player->y), player->width, player->height };

		SDL_RenderCopy(renderer, player_Texture, NULL, &player_Rect);//player

		SDL_RenderPresent(renderer);
	}

	delete player;
	delete ball;
	_Shutdown(&window, &renderer);
	return true;
}

/*
left

left- x: 0 y: 380

rigth- x:0 y: 142
*/

/*
right

left - x: 1260 y: 380
right - x: 1260 y: 142
*/


SDL_Texture* Soccer::_init_Object(const char* skin_path, SDL_Renderer** renderer)
{
	SDL_Surface* Obj_Surface = nullptr;
	SDL_Texture* Obj_Texture = nullptr;

	Obj_Surface = IMG_Load(skin_path);
	if (!Obj_Surface)
	{
		std::cerr << "Failed to load  object surface." << SDL_GetError<<std::endl;
		return nullptr;
	}

	Obj_Texture = SDL_CreateTextureFromSurface(*renderer, Obj_Surface);

	SDL_FreeSurface(Obj_Surface);

	if (!Obj_Texture)
	{
		std::cerr << "Failed to load object texture." << SDL_GetError << std::endl;
		return nullptr;
	}
	
	return Obj_Texture;
}
SDL_Texture* Soccer::_init_Background(SDL_Renderer** renderer)
{
	SDL_Texture* background_Texture = nullptr;
	SDL_Surface* background_Surface = SDL_LoadBMP("background.bmp");

	if (!background_Surface)
	{
		std::cerr << "Failed to load bmp surface." << SDL_GetError << std::endl;
		return nullptr;
	}
	std::cout << "bmp surface loaded successfully!" << std::endl;

	background_Texture = SDL_CreateTextureFromSurface(*renderer, background_Surface);

	SDL_FreeSurface(background_Surface);

	if (!background_Texture)
	{
		std::cerr << "Failed to  load surface to texture." << SDL_GetError << std::endl;
		return nullptr;
	}
	std::cout << "Texture loaded successfully!" << std::endl;

	return background_Texture;
}

bool Soccer::_init(SDL_Window** window, SDL_Renderer** renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
		return false;
	}

	//init window
	*window = SDL_CreateWindow("SOCCER",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL);


	//checks if window has been created
	if (*window == NULL) {
		std::cerr << "Failed to load screen." << SDL_GetError() << std::endl;
		return false;
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!*renderer)
	{
		std::cerr << "Failed to load renderer."<< SDL_GetError() << std::endl;
		return false;
		SDL_Quit();
	}

	return true;
}

void  Soccer::_Shutdown(SDL_Window** window, SDL_Renderer** renderer)
{
	SDL_DestroyRenderer(*renderer);
	SDL_DestroyWindow(*window);
}


