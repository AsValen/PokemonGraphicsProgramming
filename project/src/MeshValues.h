#pragma once

struct colorValues
{
	float r;
	float g;
	float b;
	float a;
	colorValues(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) : r(r), g(g), b(b), a(a)
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

	cylinderValues(int slices, float topRadius, float bottomRadius, float height, float squash = 1.0f) : slices(slices), topRadius(topRadius), bottomRadius(bottomRadius), height(height), squash(squash)
	{
	}
};

struct cubeFacesValues
{
	bool front;
	bool back;
	bool left;
	bool right;
	bool top;
	bool bottom;
	cubeFacesValues(bool front = true, bool back = true, bool left = true, bool right = true, bool top = true, bool bottom = true) : front(front), back(back), left(left), right(right), top(top), bottom(bottom)
	{
	}
};	