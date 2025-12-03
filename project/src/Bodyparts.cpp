// Get the header of the signature declare in Bodyparts
#include "Bodyparts.h"

// Require the use of openGL functionality
#include <glad/glad.h>

// Require the use of Matrix4
#include "angle_util/matrix.h"

// Require the use of creating shapes
#include "Shapes.h"

// Require the used of App::getTime
#include "Framework/app.h"

// Declare colors used for each part of the pokemon
Vector3 mainColor = Vector3(0.22f, 0.54f, 0.69f);
Vector3 complimentColor = Vector3(0.36f, 0.36f, 0.36f);
Vector3 torsoColor = Vector3(0.94f, 0.94f, 0.7f);
Vector3 eyeColor = Vector3(0.66f, 0.21f, 0.21f);
Vector3 clearColor = Vector3(0.94f, 0.94f, 0.94f);

// Declare instance of mid upper torso matrix for the rest of the bodypart to move according to transformation hierachy
Matrix4 midUpperTorsoMatrix;

// Declare instance of shapes to use any create functions
Shapes shapes;

void Bodyparts::CreateUpperTorso(const Matrix4& viewProjectionMatrix)
{
	// CREATING MID UPPER TORSO -----------------------------------------------------------------------------------------------------------------------------
	// translate the mid upper torso to go up and down using sin waves and adjust it to be at the back of scene for better view
	midUpperTorsoMatrix = Matrix4::translate(Vector3(0.0f, sin(App::getTime()), -10.0f));

	// 
	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 2.0f, 2.0f, 2.0f, 0.5f), colorValues(torsoColor.x, torsoColor.y, torsoColor.z, 1.0f), false, false);

	// Create top upper torso
	Matrix4 topUpperTorsoMatrix = Matrix4::translate(Vector3(0.0f, 2.0f, 0.0f));

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * topUpperTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 2.5f, 2.0f, 3.0f, 0.5f), colorValues(torsoColor.x, torsoColor.y, torsoColor.z, 1.0f), true, false);

	// Create bottom upper torso
	Matrix4 bottomUpperTorsoMatrix = Matrix4::translate(Vector3(0.0f, -2.0f, 0.0f));

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomUpperTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 2.0f, 3.5f, 2.0f, 0.5f), colorValues(torsoColor.x, torsoColor.y, torsoColor.z, 1.0f), false, true);

	// Create white spike
	Matrix4 spikeMatrix = Matrix4::translate(Vector3(0.0f, 4.0f, 1.0f)) * Matrix4::rotate(90.0f, Vector3(1, 0, 0));
	
	mvp = viewProjectionMatrix * midUpperTorsoMatrix * spikeMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 0.0f, 0.5f, 1.0f, 1.0f), colorValues(clearColor.x, clearColor.y, clearColor.z, 1.0f));
}