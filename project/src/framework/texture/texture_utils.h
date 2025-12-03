#pragma once
#include <vector>
#include <string>
#include "texture2d.h"

class TextureUtils
{
public:
	static Texture2D* loadFromFile(const std::string& path, TextureConfig cfg);
};