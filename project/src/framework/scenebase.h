#ifndef _SCENE_BASE_H
#define _SCENE_BASE_H
#include "../angle_util/matrix.h"
#include "../angle_util/vector.h"
#include "app.h"

//! Scene base class.
class SceneBase
{
protected:

	void drawWorldOriginLines();
	void drawHorizontalGridLines();
	void drawVerticalGridLines();

public:
	virtual void init() = 0;
	virtual void deinit() = 0;
	virtual void update() = 0;
	virtual void draw(const Matrix4& projectionMatrix, const Matrix4& viewMatrix) = 0;
};

#endif
