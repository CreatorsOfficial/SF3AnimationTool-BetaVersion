#pragma once
#include "Position.h"
#include "Quaternion.h"

class AnimatedTransform
{
public:
	Quaternion rotation;
	Position position;
public:
	AnimatedTransform(Position position, Quaternion quaternion);
	AnimatedTransform() = default;
};