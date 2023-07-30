#include "Ball.hpp"

void Ball::_Reset_Ball(Ball& ball, bool check)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_BACKSPACE] || check)
	{
		ball.x = 650;
		ball.y = 280;
	}
}

void Ball::_Goal_Check(Ball& ball)
{
	if ((ball.x <= 5 || ball.x >= 1255) && (ball.y > 142 && ball.y < 380))
	{
		std::cout << "Goal" << "Ball x: "<<ball.x<<"y: "<<ball.y << std::endl;
		_Reset_Ball(ball, true);
	}
}

void Ball::_ball_Border(Ball& ball, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	if (ball.x < 0) { ball.x = 0; }

	if (ball.x + ball.width > SCREEN_WIDTH) { ball.x = SCREEN_WIDTH - ball.width; }

	if (ball.y < 0) { ball.y = 0; }

	if (ball.y + ball.height > SCREEN_HEIGHT) { ball.y = SCREEN_HEIGHT - ball.height; }
}