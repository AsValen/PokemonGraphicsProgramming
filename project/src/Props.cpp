#include "Props.h"
#include "Transform.h"


void Props::CreateGround(const Matrix4& viewProjectionMatrix, Shapes& shapes, Texture2D* texture)
{
	Transform groundTransform;

	groundTransform.rotateXBy(-90.0f);
	groundTransform.setPosition(-5.0f, 0.0f, 5.0f);

	Matrix4 groundTransformMatrix = groundTransform.getMatrix();

	Matrix4 mvp = viewProjectionMatrix * groundTransformMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateSquare(
		Vector3(10.0f, 10.0f, 0.0f),
		colorValues(0.8f, 0.8f, 0.0f, 1.0f),
		texture
	);
}

void Props::CreateGrass(const Matrix4& viewProjectionMatrix, Shapes& shapes, Vector3& position, Vector2& size, Texture2D* texture)
{

	float halfWidth = size.x * 0.5f;
	float halfHeight = size.y * 0.5f;

	// currently the pivot is located at the bottom left, so we want to set our own pivot point to be in the bottom center of the grass quad
	Vector3 pivotLocal(halfWidth, 0.0f, 0.0f);

	// this is the world position which is the final position of where the grass will be drawn
	Vector3 worldPos(position.x, position.y, position.z);

	Matrix4 T_pos = Matrix4::translate(worldPos);

	// -pivotLocal will move the pivot to origin for rotation, visually both grass would intersect at the pivot point
	Matrix4 T_pivot = Matrix4::translate(-pivotLocal);
	Matrix4 R = Matrix4::rotate(45.0f, Vector3(0,1,0));

	// what this does is first translate local pivot to origin, then rotate around origin, then translate to final world position
	Matrix4 grassTransformMatrix = T_pos * R * T_pivot;

	Matrix4 mvp = viewProjectionMatrix * grassTransformMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateSquare(
		Vector3(size.x, size.y, 0.0f),
		colorValues(1.0f, 1.0f, 1.0f, 1.0f),
		texture
	);

	// rotate the other grass to be perpendicular to the first one
	Matrix4 R2 = Matrix4::rotate(135.0f, Vector3(0, 1, 0));

	grassTransformMatrix = T_pos * R2 * T_pivot;

	mvp = viewProjectionMatrix * grassTransformMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateSquare(
		Vector3(size.x, size.y, 0.0f),
		colorValues(1.0f, 1.0f, 1.0f, 1.0f),
		texture
	);
}

void Props::CreateRock(const Matrix4& viewProjectionMatrix, Shapes& shapes, Vector3& position, Vector3& size, Texture2D* texture)
{	
	Transform rootTransform;
	rootTransform.setPosition(position.x, position.y, position.z);
	rootTransform.setScale(size.x, size.y, size.z);
	Matrix4 rootTransformMatrix = rootTransform.getMatrix();

	Transform rock1Transform;
	rock1Transform.setRotation(34.0f, 15.0f, 83.0f);
	rock1Transform.setPosition(1.0f, -0.2f, 1.0f);

	Matrix4 rock1TransformMatrix = rock1Transform.getMatrix();
	Matrix4 mvp = viewProjectionMatrix * rootTransformMatrix * rock1TransformMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCube(
		Vector3(0.4f, 0.35f, 0.3f),
		colorValues(1.0f, 1.0f, 1.0f, 1.0f),
		texture
	);

	Transform rock2Transform;
	rock2Transform.setRotation(256.0f, 45.0f, 23.0f);
	rock2Transform.setPosition(1.5f, 0.0f, 1.0f);

	Matrix4 rock2TransformMatrix = rock2Transform.getMatrix();
	mvp = viewProjectionMatrix * rootTransformMatrix * rock2TransformMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCube(
		Vector3(0.15f, 0.25f, 0.35f),
		colorValues(1.0f, 1.0f, 1.0f, 1.0f),
		texture
	);

	Transform rock3Transform;
	rock3Transform.setRotation(21.0f, 145.0f, 74.0f);
	rock3Transform.setPosition(1.6f, 0.0f, 0.7f);

	Matrix4 rock3TransformMatrix = rock3Transform.getMatrix();
	mvp = viewProjectionMatrix * rootTransformMatrix * rock3TransformMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCube(
		Vector3(0.5f, 0.4f, 0.3f),
		colorValues(1.0f, 1.0f, 1.0f, 1.0f),
		texture
	);
}

void Props::CreateCrystal(const Matrix4& viewProjectionMatrix, Shapes& shapes, Vector3& position, float height, Vector3& size, Vector3& rotation, Texture2D* texture)
{
	Transform crystal1Transform;
	crystal1Transform.setPosition(position.x, position.y, position.z);
	crystal1Transform.setScale(size.x, size.y, size.z);
	crystal1Transform.setRotation(rotation.x, rotation.y, rotation.z);
	Matrix4 crystal1TransformMatrix = crystal1Transform.getMatrix();
	Matrix4 mvp = viewProjectionMatrix * crystal1TransformMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCube(
		Vector3(1.0f, height, 1.0f),
		colorValues(0.8f, 0.8f, 1.0f, 1.0f),
		texture,
		cubeFacesValues(true, true, true, true, false, true)
	);

	Transform crystal2Transform;
	crystal2Transform.setPosition(0.0f, height, 0.0f);
	Matrix4 crystal2TransformMatrix = crystal2Transform.getMatrix();
	mvp = viewProjectionMatrix * crystal1TransformMatrix * crystal2TransformMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreatePyramid(
		Vector3(1.0f, 1.0f, 1.0f),
		colorValues(0.8f, 0.8f, 1.0f, 1.0f),
		texture,
		false
	);
}