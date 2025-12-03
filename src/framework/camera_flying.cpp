#include "camera_flying.h"

void CameraFlying::setPosition(float x, float y, float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
	mWorldMatrixDirty = true;
}

void CameraFlying::translate(float x, float y, float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
	mWorldMatrixDirty = true;
}

void CameraFlying::translateLocal(float x, float y, float z)
{
	Vector3 localOrientOffset = mOrient * Vector3(x, y, z);
	mPosition += localOrientOffset;
	mWorldMatrixDirty = true;
}

void CameraFlying::rotate(float angle, const Vector3& axis)
{
	mOrient = Matrix4::rotate(angle, axis) * mOrient;
	mWorldMatrixDirty = true;
}

void CameraFlying::rotateLocal(float angle, const Vector3& axis)
{
	mOrient = mOrient * Matrix4::rotate(angle, axis);
	mWorldMatrixDirty = true;
}

void CameraFlying::lookAt(const Vector3& direction)
{
	mOrient = Matrix4::lookAt(direction, Vector3(0.0, 1.0, 0.0));
	mWorldMatrixDirty = true;
}

void CameraFlying::lookAtPoint(const Vector3& coordinate)
{
	Vector3 dir = Vector3::normalize(mPosition - coordinate);
	mOrient = Matrix4::lookAt(dir, Vector3(0.0, 1.0, 0.0));
	mWorldMatrixDirty = true;
}

void CameraFlying::setViewport(const int width, const int height)
{
	viewportAspectRatio = width / (float)height;
	mProjMatrixDirty = true;
}