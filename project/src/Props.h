#pragma once
#include "Shapes.h" 
#include "angle_util/matrix.h"

class Props 
{
public:
	void CreateGround(const Matrix4& viewProjectionMatrix, Shapes& shapes, Texture2D* texture = NULL);

	void CreateGrass(const Matrix4& viewProjectionMatrix, Shapes& shapes, Vector3& position, Vector2& size, Texture2D* texture = NULL);

	void CreateRock(const Matrix4& viewProjectionMatrix, Shapes& shapes, Vector3& position, Vector3& size = Vector3(1.0f, 1.0f, 1.0f), Texture2D* texture = NULL);

	void CreateCrystal(const Matrix4& viewProjectionMatrix, Shapes& shapes, Vector3& position, float height, Vector3& size = Vector3(1.0f, 1.0f, 1.0f), Vector3& rotation = Vector3(0.0f, 0.0f, 0.0f), Texture2D* texture = NULL);
};