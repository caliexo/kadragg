#pragma once
#include<iostream>
#include<SDL.h>

class Ball
{
private:


public:

	int x, y;
	int width, height;

	std::string skin_path;

	void _Reset_Ball(Ball& ball, bool check);
	void _Goal_Check(Ball& ball);
	void _ball_Border(Ball& ball, int SCREEN_WIDTH, int SCREEN_HEIGHT);
};
	
