#ifndef _CAMERAFLYING_H
#define _CAMERAFLYING_H

#include "../angle_util/matrix.h"
#include "../angle_util/vector.h"

class CameraFlying
{
	//! \name Attributes.
	//@{
protected:
	//! Camera position.
	Vector3 mPosition;

	//! Rotation matrix.
	Matrix4 mOrient;

	//! Flag to tell if we need to update world matrix.
	mutable bool mWorldMatrixDirty;

	//! Flag to tell if we need to update projection matrix.
	mutable bool mProjMatrixDirty;

	//! World matrix. (Cache)
	mutable Matrix4 mWorld;

	//! View matrix. (Cache)
	mutable Matrix4 mView;

	//! Projection matrix (Cache)
	mutable Matrix4 mProjection;

	//! Camera field of view
	float fieldOfView;

	//! Viewport aspect ratio
	float viewportAspectRatio;

	//@}

	//! \name Methods.
	//@{
public:
	CameraFlying(float fov) :
		mPosition(0.0f, 0.0f, 0.0f),
		mOrient(Matrix4::identity()),
		mWorldMatrixDirty(true),
		fieldOfView(fov)
	{ }

	//! Set camera viewport
	void setViewport(const int width, const int height);

	//! Set camera position.
	void setPosition(float x, float y, float z);

	//! Move camera in world space.
	void translate(float x, float y, float z);

	//! Move camera in local orient space.
	void translateLocal(float x, float y, float z);

	//! Rotate camera in world space.
	void rotate(float angle, const Vector3& axis);

	//! Rotate camera in local orient space.
	void rotateLocal(float angle, const Vector3& axis);

	void lookAt(const Vector3& direction);

	void lookAtPoint(const Vector3& coordinate);

	//! Return view matrix.
	inline const Matrix4& getViewMatrix() const
	{
		if (mWorldMatrixDirty)
		{
			mWorld = Matrix4::translate(mPosition) * mOrient;
			mView = Matrix4::invert(mWorld);
			mWorldMatrixDirty = false;
		}

		return mView;
	}

	//! Return projection matrix.
	inline const Matrix4& getProjectionMatrix() const
	{
		if (mProjMatrixDirty)
		{
			mProjection = Matrix4::perspective(fieldOfView, viewportAspectRatio, 0.1f, 500.0f);
			mProjMatrixDirty = false;
		}

		return mProjection;
	}

	//@}
};

#endif
