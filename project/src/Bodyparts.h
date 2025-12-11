#pragma once
#include "Shapes.h" 
#include <glad/glad.h> 
#include "angle_util/matrix.h"

class Bodyparts
{
public :
	void CreateUpperTorso(const Matrix4& viewProjectionMatrix, const Matrix4& overallMatrix, Shapes& shapes, Texture2D* torsoTexture = NULL, Texture2D* spikeTexture = NULL);

	void CreateLowerTorso(const Matrix4& viewProjectionMatrix, Shapes& shapes, Texture2D* beltTexture = NULL, Texture2D* lowerTorsoTexture = NULL);

	void CreateHead(const Matrix4& viewProjectionMatrix, Shapes& shapes, Texture2D* neckTexture = NULL, Texture2D* headTexture = NULL, Texture2D* snoutTexture = NULL, Texture2D* snoutTipTexture = NULL, Texture2D* earTexture = NULL, Texture2D* earTopBottomTexture = NULL, Texture2D* hairTexture = NULL);

	void CreateLeftArm(const Matrix4& viewProjectionMatrix, Shapes& shapes, Texture2D* bracerTexture = NULL, Texture2D* armTexture = NULL, Texture2D* fingerTexture = NULL, Texture2D* spikeTexture = NULL);

	void CreateRightArm(const Matrix4& viewProjectionMatrix, Shapes& shapes, Texture2D* bracerTexture = NULL, Texture2D* armTexture = NULL, Texture2D* fingerTexture = NULL, Texture2D* spikeTexture = NULL);
	
	void CreateLeftLeg(const Matrix4& viewProjectionMatrix, const Matrix4& overallMatrix, Shapes& shapes, Texture2D* legTexture = NULL, Texture2D* toeTexture = NULL);

	void CreateRightLeg(const Matrix4& viewProjectionMatrix, const Matrix4& overallMatrix, Shapes& shapes, Texture2D* legTexture = NULL, Texture2D* toeTexture = NULL);

	void CreateTail(const Matrix4& viewProjectionMatrix, Texture2D* tailTexture = NULL);

	void CreateHair(const Matrix4& viewProjectionMatrix, Texture2D* hairTexture = NULL);
};