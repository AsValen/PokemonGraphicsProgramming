#pragma once
#include <glad/glad.h>

enum class TextureWrapMode
{
	REPEAT,
	REPEAT_MIRRORED,
	CLAMP
};

enum class TextureFilterMode
{
	NEAREST,
	LINEAR
};

// This struct is to provide means to control texture settings when loading texture
struct TextureConfig
{
	GLint hWrap;
	GLint vWrap;
	GLint textureFilter;
	GLint internalFormat = GL_RGBA;
	bool mipmap;

	TextureConfig(TextureWrapMode wrapHorizontal, TextureWrapMode wrapVertical, TextureFilterMode filter, bool enableMipmap)
		: mipmap(enableMipmap)
	{
		switch (wrapHorizontal)
		{
		case TextureWrapMode::REPEAT: hWrap = GL_REPEAT; break;
		case TextureWrapMode::REPEAT_MIRRORED: hWrap = GL_MIRRORED_REPEAT; break;
		case TextureWrapMode::CLAMP: hWrap = GL_CLAMP_TO_EDGE; break;
		}
		switch (wrapVertical)
		{
		case TextureWrapMode::REPEAT: vWrap = GL_REPEAT; break;
		case TextureWrapMode::REPEAT_MIRRORED: vWrap = GL_MIRRORED_REPEAT; break;
		case TextureWrapMode::CLAMP: vWrap = GL_CLAMP_TO_EDGE; break;
		}
		switch (filter)
		{
		case TextureFilterMode::NEAREST: textureFilter = GL_NEAREST; break;
		case TextureFilterMode::LINEAR: textureFilter = GL_LINEAR; break;
		}
	}
};

class Texture2D
{
private:

	friend class TextureUtils;

	TextureConfig cfg;
	int width, height;
	unsigned int handle;

	Texture2D(int width, int height, TextureConfig cfg);
	static Texture2D* createColourTexture(int width, int height, TextureConfig cfg, GLenum dataFormat, unsigned char* data);

public:
	~Texture2D();

	unsigned int getNativeHandle();

	/***************************************************
	* Not needed in XBGT2064
	***************************************************/
	/*
	bool hasMipMap();
	GLint getWrapModeHorizontal();
	GLint getWrapModeVertical();
	GLint getTextureFilter();
	void getSize(int* w, int* h);
	GLint getInternalFormat();
	*/

};
