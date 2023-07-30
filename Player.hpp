#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<random>

#include"Ball.hpp"

class Player
{
private:
	


public:

	float x, y;
	float move_normal, move_sprint, acceleration, velocity;
	int width, height;

	std::string team, name;

	std::string skin_path;

	bool touched_ball;
	
	float _Velocity_Calc(float deltaTime, Player& player);
	void _Touch_Ball(Player& player, Ball& ball, float deltaTime);
	void _Update_Pos(float deltaTime, Player& player);
	float _Move(float deltaTime, Player& player);
	void _player_Border(Player& player, int SCREEN_WIDTH, int SCREEN_HEIGHT);
};

