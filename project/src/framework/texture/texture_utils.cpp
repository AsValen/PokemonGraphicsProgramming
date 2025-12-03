#include "texture_utils.h"
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <iostream>

Texture2D* TextureUtils::loadFromFile(const std::string& path, TextureConfig cfg)
{
	// By default, point to null (null equals 0 in C++)
	Texture2D* tex = 0;

	// Tell stb_image.h to flip loaded texture's on the Y-axis.
	// This is because image coordinates has Y-axis pointing downwards,
	// while OpenGL has it pointing upwards.
	stbi_set_flip_vertically_on_load(true);

	// local static variables for reusability
	// curious what it means? go find reading materials!
	static int width, height, nrChannels;

	// Use stb_image to load the file, it returns the data and also changes
	// width, height and numberChannels
	// The type is unsigned char because unsigned char byte-size is 1 byte
	// and data is actually an array, which is why it is a pointer to unsigned char.
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);

	// If data is not null, then the image is successfully loaded.
	if (data)
	{
		// For XBGT2064/2094 frameworks, colour images use RGBA internal format
		// This is for consistency purposes.
		// cfg is used in Texture2D::createColourTexture(...)
		cfg.internalFormat = GL_RGBA;

		// Actually create the texture. You thought you read enough huh?
		// More things to read inside Texture2D::createColourTexture(...)
		tex = Texture2D::createColourTexture(width, height, cfg, GL_RGBA, data);
		std::cout << "Loaded texture: " << path << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture: " << path << std::endl;
	}

	// Free memory after we upload the data.
	stbi_image_free(data);

	return tex;
}