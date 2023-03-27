#pragma once

#include "Vec2D.h"
#include <vector>

enum PacmanMovement
{
	PACMAN_MOVEMENT_NONE = 0,
	PACMAN_MOVEMENT_UP,
	PACMAN_MOVEMENT_LEFT,
	PACMAN_MOVEMENT_DOWN,
	PACMAN_MOVEMENT_RIGHT
};

inline Vec2D GetMovementVector(PacmanMovement direction)
{
	if (direction == PACMAN_MOVEMENT_LEFT)
	{
		return Vec2D(-1, 0);
	}
	else if (direction == PACMAN_MOVEMENT_DOWN)
	{
		return Vec2D(0, 1);
	}
	else if (direction == PACMAN_MOVEMENT_RIGHT)
	{
		return Vec2D(1, 0);
	}
	else if (direction == PACMAN_MOVEMENT_UP)
	{
		return Vec2D(0, -1);
	}

	return Vec2D::Zero;
}

inline PacmanMovement GetOppositeDirection(PacmanMovement direction)
{
	if (direction == PACMAN_MOVEMENT_LEFT)
	{
		return PACMAN_MOVEMENT_RIGHT;
	}
	else if (direction == PACMAN_MOVEMENT_DOWN)
	{
		return PACMAN_MOVEMENT_UP;
	}
	else if (direction == PACMAN_MOVEMENT_RIGHT)
	{
		return PACMAN_MOVEMENT_LEFT;
	}
	else if (direction == PACMAN_MOVEMENT_UP)
	{
		return PACMAN_MOVEMENT_DOWN;
	}

	return PACMAN_MOVEMENT_NONE;
}

inline std::vector<PacmanMovement> GetPerpendicularMovements(PacmanMovement direction)
{
	std::vector<PacmanMovement> perpDirections;

	if (direction == PACMAN_MOVEMENT_DOWN || direction == PACMAN_MOVEMENT_UP)
	{
		perpDirections.push_back(PACMAN_MOVEMENT_LEFT);
		perpDirections.push_back(PACMAN_MOVEMENT_RIGHT);
	}
	else if (direction == PACMAN_MOVEMENT_RIGHT || direction == PACMAN_MOVEMENT_LEFT)
	{
		perpDirections.push_back(PACMAN_MOVEMENT_UP);
		perpDirections.push_back(PACMAN_MOVEMENT_DOWN);
	}
	else if (direction == PACMAN_MOVEMENT_NONE)
	{
		perpDirections.push_back(PACMAN_MOVEMENT_UP);
		perpDirections.push_back(PACMAN_MOVEMENT_LEFT);
		perpDirections.push_back(PACMAN_MOVEMENT_DOWN);
		perpDirections.push_back(PACMAN_MOVEMENT_RIGHT);
	}

	return perpDirections;
}