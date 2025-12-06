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

// Require the use transform wrappers to more readability
#include "Transform.h"

// Require the cylindroid to create seamless bodyparts by chaining different sizes of loops
#include "Cylindroid.h"

#include "MeshValues.h"

#include <iostream>

using namespace std;

// Declare colors used for each part of the pokemon
colorValues mainColor = colorValues(0.22f, 0.54f, 0.69f, 1.0f);
colorValues complimentColor = colorValues(0.36f, 0.36f, 0.36f, 1.0f);
colorValues torsoColor = colorValues(0.94f, 0.94f, 0.7f, 1.0f);
colorValues eyeColor = colorValues(0.66f, 0.21f, 0.21f, 1.0f);
colorValues clearColor = colorValues(0.94f, 0.94f, 0.94f, 1.0f);
colorValues pawStumbsColor = colorValues(0.96f, 0.63f, 0.69f, 1.0f);

// Declare instance of mid upper torso matrix for the rest of the bodypart to move according to transformation hierachy
Transform midUpperTorso;
Matrix4 midUpperTorsoMatrix;
Matrix4 bottomLeftLowerTorsoMatrix;
Matrix4 bottomRightLowerTorsoMatrix;

float speed = 1.0f;
float maxAngle = 10.0f;
float amplitude = 0.2f;

// Declare instance of shapes to use any create functions
Shapes shapes;

// Create a single instance of LeftLeg cylindroid and point to the original class of cylindroid
Cylindroid* leftLegCylindroid;

void Bodyparts::CreateUpperTorso(const Matrix4& viewProjectionMatrix)
{
	// CREATING MID UPPER TORSO -----------------------------------------------------------------------------------------------------------------------------
	// translate the mid upper torso to go up and down using sin waves and adjust it to be at the back of scene for better view
	midUpperTorso.setPosition(0.0f, (sin(App::getTime()) * speed) * amplitude, 0.0f);
	midUpperTorso.setScale(0.3f, 0.3f, 0.3f);

	// getting the matrix from the transform and setting this as the root
	midUpperTorsoMatrix = midUpperTorso.getMatrix();

	// Moves the mid upper torso object from local space to world space
	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoMatrix;

	// replaces the current matrix to the completed mid upper torso matrix in world space
	glLoadMatrixf(mvp.data);

	// Creating the mesh model for the mid upper torso
	shapes.CreateCylinder(cylinderValues(8, 2.0f, 2.0f, 2.0f, 0.5f), colorValues(torsoColor.r, torsoColor.g, torsoColor.b, torsoColor.a), false, false);

	// CREATING TOP UPPER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform topUpperTorso;
	topUpperTorso.setPosition(0.0f, 2.0f, 0.0f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * topUpperTorso.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 2.5f, 2.0f, 3.0f, 0.5f), colorValues(torsoColor.r, torsoColor.g, torsoColor.b, torsoColor.a), true, false);

	// CREATING BOTTOM UPPER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform bottomUpperTorso;
	bottomUpperTorso.setPosition(0.0f, -2.0f, 0.0f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomUpperTorso.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 2.0f, 3.5f, 2.0f, 0.5f), colorValues(torsoColor.r, torsoColor.g, torsoColor.b, torsoColor.a), false, false);

	// CREATING WHITE SPIKE -----------------------------------------------------------------------------------------------------------------------------
	Transform spike;
	spike.rotateXBy(90.0f);
	spike.setPosition(0.0f, 4.0f, 1.0f);
	
	mvp = viewProjectionMatrix * midUpperTorsoMatrix * spike.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 0.0f, 0.5f, 1.0f, 1.0f), colorValues(clearColor.r, clearColor.g, clearColor.b, clearColor.a));
}

void Bodyparts::CreateLowerTorso(const Matrix4& viewProjectionMatrix)
{
	// CREATING TOP LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform topLowerTorso;
	topLowerTorso.setPosition(0.0f, -3.5f, 0.0f);
	Matrix4 topLowerTorsoMatrix = topLowerTorso.getMatrix();

	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoMatrix * topLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 3.5f, 4.5f, 1.5f, 0.5f), colorValues(complimentColor.r, complimentColor.g, complimentColor.b, complimentColor.a), false, false);

	// CREATING MID LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform midLowerTorso;
	midLowerTorso.setPosition(0.0f, -2.0f, 0.0f);
	Matrix4 midLowerTorsoMatrix = midLowerTorso.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * topLowerTorsoMatrix * midLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 4.5f, 5.5f, 2.0f, 0.5f), colorValues(mainColor.r, mainColor.g, mainColor.b, mainColor.a), false, false);

	//CREATING BOTTOM LEFT LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform bottomLeftLowerTorso;
	bottomLeftLowerTorso.setPosition(-3.0f, -4.0f, 0.0f);
	bottomLeftLowerTorsoMatrix = topLowerTorsoMatrix * midLowerTorsoMatrix * bottomLeftLowerTorso.getMatrix();

    mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomLeftLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 2.5f, 2.5f, 4.0f, 0.75f), colorValues(mainColor.r, mainColor.g, mainColor.b, mainColor.a));

	//CREATING BOTTOM MID LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform bottomMidLowerTorso;
	bottomMidLowerTorso.setPosition(0.0f, -3.0f, 0.0f);
	Matrix4 bottomMidLowerTorsoMatrix = topLowerTorsoMatrix * midLowerTorsoMatrix * bottomMidLowerTorso.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomMidLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 5.5f, 2.0f, 3.0f, 0.5f), colorValues(mainColor.r, mainColor.g, mainColor.b, mainColor.a), false);

	// CREATING BOTTOM RIGHT LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform bottomRightLowerTorso;
	bottomRightLowerTorso.setPosition(3.0f, -4.0f, 0.0f);
	bottomRightLowerTorsoMatrix = topLowerTorsoMatrix * midLowerTorsoMatrix * bottomRightLowerTorso.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomRightLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 2.5f, 2.5f, 4.0f, 0.75f), colorValues(mainColor.r, mainColor.g, mainColor.b, mainColor.a));
}

void Bodyparts::CreateLeg(const Matrix4& viewProjectionMatrix)
{
	std::vector<cylindroidLoopValues> loops;

	loops.push_back(cylindroidLoopValues(1.2f, 0.0f, Vector3(0.0f, -1.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.2f, 2.0f, Vector3(0.0f, 0.0f, 1.0f), Vector3(((sin(App::getTime() * speed) * maxAngle) + -5.0f), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.2f, 3.5f, Vector3(0.0f, 0.0f, -1.0f), Vector3(((sin(App::getTime() * speed) * maxAngle)), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.5f, 5.0f, Vector3(0.0f, 3.0f, 0.0f), Vector3(10.0f, 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.5f, 5.3f, Vector3(0.0f, 6.0f, -2.0f), Vector3(45.0f, 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(2.5f, 5.6f, Vector3(0.0f, 10.0f, -1.0f), Vector3(90.0f, 0.0f, 0.0f), 0.5f));
	loops.push_back(cylindroidLoopValues(0.0f, 5.6f, Vector3(0.0f, 10.0f, -1.0f), Vector3(90.0f, 0.0f, 0.0f), 0.5f));

	leftLegCylindroid = new Cylindroid(8.0f, loops, viewProjectionMatrix, complimentColor);
	leftLegCylindroid->draw();
}

void Bodyparts::CreateLeftLeg(const Matrix4& viewProjectionMatrix)
{
	Transform leftLeg;
	leftLeg.setPosition(0.0f, 0.0f, 0.0f);
	// rotating the leg downwards and away from camera due to how cylindroids construct the loops and bridging them 
	leftLeg.setRotation(180.0f, 180.0f, 0.0f);
	// making the leg slighly shorter in the y axis
	leftLeg.setScale(1.0f, 0.8f, 1.0f);
	Matrix4 leftLegMatrix = leftLeg.getMatrix();
	
	// remove the translation of mid upper torso matrix so that the leg does not bob up and down
	Matrix4 midUpperTorsoNoTranslationMatrix = midUpperTorsoMatrix;
	midUpperTorsoNoTranslationMatrix.data[12] = 0.0f;
	midUpperTorsoNoTranslationMatrix.data[13] = 0.0f;
	midUpperTorsoNoTranslationMatrix.data[14] = 0.0f;

	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoNoTranslationMatrix * bottomLeftLowerTorsoMatrix * leftLegMatrix;
	glLoadMatrixf(mvp.data);

	Bodyparts::CreateLeg(viewProjectionMatrix);
}
