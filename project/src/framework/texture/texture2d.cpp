#include "texture2d.h"
#include <iostream>

Texture2D::Texture2D(int width, int height, TextureConfig cfg) : width(width), height(height), cfg(cfg) {}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &handle);
}

unsigned int Texture2D::getNativeHandle()
{
	return handle;
}

Texture2D* Texture2D::createColourTexture(int width, int height, TextureConfig cfg, GLenum dataFormat, unsigned char* data)
{
	// Create the container
	Texture2D* tex = new Texture2D(width, height, cfg);

	// Generate texture and bind
	glGenTextures(1, &(tex->handle));
	glBindTexture(GL_TEXTURE_2D, (tex->handle));

	// Set Wrap Mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, cfg.hWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, cfg.vWrap);

	// Set Mipmap Generation
	// This step depends on OpenGL version
	// Legacy Pipeline (OpenGL <=2.1)
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, cfg.mipmap ? GL_TRUE : GL_FALSE);
	// Modern Pipeline (OpenGL >=3.0)
	// glGenerateMipmap(GL_TEXTURE_2D);

	// Minification Filter depends on mipmap setting.
	// If enabled, need to use the equivalent mipmap minification filter.
	int minFilter;
	switch (cfg.textureFilter)
	{
	default:
	case GL_NEAREST: minFilter = cfg.mipmap ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST; break;
	case GL_LINEAR: minFilter = cfg.mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR; break;
	}

	// Set Minification and Magnification filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, cfg.textureFilter);

	// Upload the data
	glTexImage2D(GL_TEXTURE_2D, 0, cfg.internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Return the container
	return tex;
}

/***************************************************
* Not needed in XBGT2064
***************************************************/
/*
bool Texture2D::hasMipMap()
{
	return cfg.mipmap;
}

GLint Texture2D::getWrapModeHorizontal()
{
	return cfg.hWrap;
}

GLint Texture2D::getWrapModeVertical()
{
	return cfg.vWrap;
}

GLint Texture2D::getTextureFilter()
{
	return cfg.textureFilter;
}

void Texture2D::getSize(int* w, int* h)
{
	*w = width;
	*h = height;
}

GLint Texture2D::getInternalFormat()
{
	return cfg.internalFormat;
}
*/