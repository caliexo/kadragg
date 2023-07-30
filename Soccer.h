#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<chrono>

#include"Ball.hpp"
#include"Player.hpp"

class Soccer
{
	 const char* ball_Skin = "SoccerBall.png";
	 const char* player_Skin = "player.png";

	const int ball_WH = 40;

	const float MOVE_NORMAL_PLAYER = 1.f;
	const float MOVE_RUN_PLAYER = 2.f;

	const int PLAYER_WH = 70.f;

	const int SCREEN_WIDTH = 1330;
	const int SCREEN_HEIGHT = 590;

	const int TARGET_FPS = 60;

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool _init(SDL_Window** window, SDL_Renderer** renderer);
	SDL_Texture* _init_Background(SDL_Renderer** renderer);
	SDL_Texture* _init_Object(const char* skin_path, SDL_Renderer** renderer);
	void _Shutdown(SDL_Window** window, SDL_Renderer** renderer);

public:

	bool Start(int argc, char* argv[]);

};

