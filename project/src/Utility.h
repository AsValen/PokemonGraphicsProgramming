#pragma once
#include "Framework/app.h"

float Clamp(float baseValue, float min, float max)
{
	return (baseValue < min) ? min : (baseValue > max) ? max : baseValue;
}

float Oscillation(float baseValue, float speed, float maxAngle)
{
	float oscillation = sin(App::getTime() * speed) * maxAngle;

	float rot = baseValue + oscillation;

	float maxValue = baseValue + maxAngle;
	float minValue = baseValue - maxAngle;

	if (rot > baseValue)
	{
		//// If your range is upward (45 → 55)
		return Clamp(rot, baseValue, maxValue);
	}
	else {
		//// If your range is downward (45 → 34)
		return Clamp(rot, minValue, baseValue);
	}
}