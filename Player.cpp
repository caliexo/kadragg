#include "Player.hpp"


void Player::_Touch_Ball(Player& player, Ball& ball, float deltaTime)
{
	float distance = pow(pow(player.x - ball.x, 2) + pow(player.y - ball.y, 2), 0.5);

	if (distance < 43)
	{
        if (player.x > ball.x) { ball.x -= _Move(deltaTime, player); }
        else { ball.x += _Move(deltaTime, player); }

        if (player.y > ball.y) { ball.y -= _Move(deltaTime, player); }
        else { ball.y += _Move(deltaTime, player); }
	}
}

float Player::_Velocity_Calc(float deltaTime, Player& player)
{
	float Volacity = player.velocity + player.acceleration * deltaTime;

	return Volacity;
}

float Player::_Move(float deltaTime, Player& player)
{
	return _Velocity_Calc(deltaTime, player) * deltaTime;
}

void Player::_Update_Pos(float deltaTime, Player& player)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	// Walking w/s/a/d
	if (currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_LEFT])
	{
		player.x -= _Move(deltaTime, player);
	}
	if (currentKeyStates[SDL_SCANCODE_D] || currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		player.x += _Move(deltaTime, player);
	}
	if (currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_UP])
	{
		player.y -= _Move(deltaTime, player);
	}
	if (currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_DOWN])
	{
		player.y += _Move(deltaTime, player);
	}

	// Running shift + w/s/a/d
	if (currentKeyStates[SDL_SCANCODE_LSHIFT] && (currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_LEFT]))
	{
		player.x += _Move(deltaTime, player) - 6;
	}
	if (currentKeyStates[SDL_SCANCODE_LSHIFT] && (currentKeyStates[SDL_SCANCODE_D] || currentKeyStates[SDL_SCANCODE_RIGHT]))
	{
		player.x -= _Move(deltaTime, player) - 6;
	}
	if (currentKeyStates[SDL_SCANCODE_LSHIFT] && (currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_UP]))
	{
		player.y += _Move(deltaTime, player)-6;
	}
	if (currentKeyStates[SDL_SCANCODE_LSHIFT] && (currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_DOWN]))
	{
		player.y -= _Move(deltaTime, player)-6;
	}
}

void Player::_player_Border(Player& player, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	if (player.x < 0) { player.x = 0; }

	if (player.x + player.width > SCREEN_WIDTH) { player.x = SCREEN_WIDTH - player.width; }

	if (player.y < 0) { player.y = 0; }

	if (player.y + player.height > SCREEN_HEIGHT) { player.y = SCREEN_HEIGHT - player.height; }
}