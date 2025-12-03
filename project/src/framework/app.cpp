#include "app.h"
#include <map>
#include <GLFW/glfw3.h>

static GLFWwindow* win;
static float ct = 0, dt = 0;
static Vector2 mp_v2, ss_v2;
static std::map<char, bool>::iterator i;

static struct iset {
	std::map<char, bool> p, c;
	int (*fun)(GLFWwindow*, int) = 0;
} itype[2];

void App::processTime(float a)
{
	dt = a - ct;
	ct = a;
}

void App::updateScreenSize(int w, int h)
{
	auto& v = ss_v2;
	v.x = w;
	v.y = h;
}

void App::updateCursor(float x, float y)
{
	auto& ss = ss_v2;
	auto& v = mp_v2;
	v.x = x;
	v.y = ss.y - y;
}

float App::getTime()
{
	return ct;
}

float App::getDeltaTime()
{
	return dt;
}

Vector2 App::getMousePosition()
{
	return mp_v2;
}

Vector2 App::getScreenSize()
{
	return ss_v2;
}

void App::init(void* windowHandle)
{
	win = static_cast<GLFWwindow*>(windowHandle);

	itype[0].fun = glfwGetKey;
	itype[1].fun = glfwGetMouseButton;
	itype[1].c = itype[1].p = { { 0, false }, { 1, false }, { 2, false } };
}

void App::processInput()
{
	for (auto& a : itype)
	{
		for (auto& i : a.p) i.second = a.c[i.first];
		for (auto& i : a.c) i.second = a.fun(win, i.first);
	}
}

bool App::isMouseButtonDown(int mouseCode)
{
	i = itype[1].c.find(mouseCode);

	if (i != itype[1].c.end())
	{
		return i->second && !itype[1].p[mouseCode];
	}
	else return false;
}

bool App::isMouseButtonUp(int mouseCode)
{
	i = itype[1].c.find(mouseCode);

	if (i != itype[1].c.end())
	{
		return !(i->second) && itype[1].p[mouseCode];
	}
	else return false;
}

bool App::isMouseButtonPressing(int mouseCode)
{
	i = itype[1].c.find(mouseCode);
	if (i != itype[1].c.end())
	{
		return i->second;
	}
	else return false;
}

bool App::isKeyDown(int keyCode)
{
	i = itype[0].c.find(keyCode);

	if (i == itype[0].c.end())
	{
		itype[0].c.emplace(keyCode, false);
		itype[0].p.emplace(keyCode, false);
		return false;
	}
	else
	{
		return i->second && !itype[0].p[keyCode];
	}
}

bool App::isKeyUp(int keyCode)
{
	i = itype[0].c.find(keyCode);

	if (i == itype[0].c.end())
	{
		itype[0].c.emplace(keyCode, false);
		itype[0].p.emplace(keyCode, false);
		return false;
	}
	else
	{
		return !(i->second) && itype[0].p[keyCode];
	}
}

bool App::isKeyPressing(int keyCode)
{
	i = itype[0].c.find(keyCode);

	if (i == itype[0].c.end())
	{
		itype[0].c.emplace(keyCode, false);
		itype[0].p.emplace(keyCode, false);
		return false;
	}
	else
	{
		return i->second;
	}
}