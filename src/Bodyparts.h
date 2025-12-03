#pragma once
#include "Shapes.h" 
#include <glad/glad.h> 
#include "angle_util/matrix.h"

class Bodyparts
{
public :
	void CreateUpperTorso(const Matrix4& viewProjectionMatrix);

	void CreateLowerTorso(const Matrix4& viewProjectionMatrix);

	void CreateHead(const Matrix4& viewProjectionMatrix);

	void CreateLeftArm(const Matrix4& viewProjectionMatrix);

	void CreateRightArm(const Matrix4& viewProjectionMatrix);

	void CreateLeftLeg(const Matrix4& viewProjectionMatrix);

	void CreateRightLeg(const Matrix4& viewProjectionMatrix);

	void CreateTail(const Matrix4& viewProjectionMatrix);
};