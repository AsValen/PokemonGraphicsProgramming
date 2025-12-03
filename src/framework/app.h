#pragma once
#include "../angle_util/vector.h"

class App
{
public:
	// Don't want to allow anyone else to be able to create instances.
	// App* app = new App();	// error
	// App app;					// error
	App() = delete;

	// All functions are static because we are using this class
	// as a namespace, effectively.
	// Keeping as class instead of converting in case need to use
	// friend keyword.

	static void processTime(float currentTime);
	static void updateScreenSize(int width, int height);
	static void updateCursor(float x, float y);

	static float getTime();
	static float getDeltaTime();
	static Vector2 getMousePosition();
	static Vector2 getScreenSize();

	static void init(void* windowHandle);
	static void processInput();

	static bool isMouseButtonDown(int mouseCode);
	static bool isMouseButtonUp(int mouseCode);
	static bool isMouseButtonPressing(int mouseCode);

	static bool isKeyDown(int keyCode);
	static bool isKeyUp(int keyCode);
	static bool isKeyPressing(int keyCode);
};
