#pragma once

struct colorValues
{
	float r;
	float g;
	float b;
	float a;
	colorValues(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
	{
	}
};

struct circleValues
{
	int slices;
	float outerRadius;
	float innerRadius;
	float height;
	float squash;

	circleValues(int slices, float outerRadius, float innerRadius, float height, float squash) : slices(slices), outerRadius(outerRadius), innerRadius(innerRadius), height(height), squash(squash)
	{
	}
};

struct cylinderValues
{
	int slices;
	float topRadius;
	float bottomRadius;
	float height;
	float squash;

	cylinderValues(int slices, float topRadius, float bottomRadius, float height, float squash) : slices(slices), topRadius(topRadius), bottomRadius(bottomRadius), height(height), squash(squash)
	{
	}
};