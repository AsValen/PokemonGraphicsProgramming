#pragma once

class DepthVisualizer
{
public:
	static bool RENDER_DEPTH;

	static void render(float zNear, float zFar);
};