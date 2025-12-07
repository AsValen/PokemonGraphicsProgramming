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

#include "Utility.h"

#include <corecrt_math_defines.h>

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
Cylindroid* rightLegCylindroid;
Cylindroid* leftArmCylindroid;
Cylindroid* rightArmCylindroid;

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
	shapes.CreateCylinder(cylinderValues(8, 3.5f, 3.5f, 4.0f, 0.5f), colorValues(torsoColor.r, torsoColor.g, torsoColor.b, torsoColor.a), false, false);

	// CREATING TOP UPPER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform topUpperTorso;
	topUpperTorso.setPosition(0.0f, 4.0f, 0.0f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * topUpperTorso.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 4.0f, 3.5f, 3.0f, 0.5f), colorValues(torsoColor.r, torsoColor.g, torsoColor.b, torsoColor.a), true, false);

	// CREATING BOTTOM UPPER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform bottomUpperTorso;
	bottomUpperTorso.setPosition(0.0f, -2.0f, 0.0f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomUpperTorso.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 3.5f, 4.0f, 2.0f, 0.5f), colorValues(torsoColor.r, torsoColor.g, torsoColor.b, torsoColor.a), false, false);

	// CREATING WHITE SPIKE -----------------------------------------------------------------------------------------------------------------------------
	Transform spike;
	spike.rotateXBy(90.0f);
	spike.setPosition(0.0f, 4.0f, 1.5f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * spike.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 0.0f, 1.0f, 2.5f, 1.0f), colorValues(clearColor.r, clearColor.g, clearColor.b, clearColor.a));
}

void Bodyparts::CreateLowerTorso(const Matrix4& viewProjectionMatrix)
{
	// CREATING TOP LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform topLowerTorso;
	topLowerTorso.setPosition(0.0f, -3.5f, 0.0f);
	Matrix4 topLowerTorsoMatrix = topLowerTorso.getMatrix();

	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoMatrix * topLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 4.0f, 4.5f, 1.5f, 0.5f), colorValues(complimentColor.r, complimentColor.g, complimentColor.b, complimentColor.a), false, false);

	// CREATING MID LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform midLowerTorso;
	midLowerTorso.setPosition(0.0f, -2.0f, 0.0f);
	Matrix4 midLowerTorsoMatrix = midLowerTorso.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * topLowerTorsoMatrix * midLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 4.5f, 5.5f, 2.0f, 0.5f), colorValues(mainColor.r, mainColor.g, mainColor.b, mainColor.a), false, false);

	//CREATING BOTTOM LEFT LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform bottomLeftLowerTorso;
	bottomLeftLowerTorso.setPosition(-3.0f, -6.0f, 0.0f);
	bottomLeftLowerTorsoMatrix = topLowerTorsoMatrix * midLowerTorsoMatrix * bottomLeftLowerTorso.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomLeftLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 2.5f, 2.5f, 6.0f, 0.75f), colorValues(mainColor.r, mainColor.g, mainColor.b, mainColor.a));

	//CREATING BOTTOM MID LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform bottomMidLowerTorso;
	bottomMidLowerTorso.setPosition(0.0f, -3.0f, 0.0f);
	Matrix4 bottomMidLowerTorsoMatrix = topLowerTorsoMatrix * midLowerTorsoMatrix * bottomMidLowerTorso.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomMidLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 5.5f, 2.0f, 3.0f, 0.5f), colorValues(mainColor.r, mainColor.g, mainColor.b, mainColor.a), false);

	// CREATING BOTTOM RIGHT LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform bottomRightLowerTorso;
	bottomRightLowerTorso.setPosition(3.0f, -6.0f, 0.0f);
	bottomRightLowerTorsoMatrix = topLowerTorsoMatrix * midLowerTorsoMatrix * bottomRightLowerTorso.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomRightLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 2.5f, 2.5f, 6.0f, 0.75f), colorValues(mainColor.r, mainColor.g, mainColor.b, mainColor.a));
}

void Bodyparts::CreateLeftLeg(const Matrix4& viewProjectionMatrix)
{
	// CREATING LEFT LEG -----------------------------------------------------------------------------------------------------------------------------
	Transform leftLeg;
	leftLeg.setPosition(0.0f, 0.0f, 0.0f);
	// rotating the leg downwards and away from camera due to how cylindroids construct the loops and bridging them 
	leftLeg.setRotation(180.0f, 180.0f, 0.0f);
	Matrix4 leftLegMatrix = leftLeg.getMatrix();

	// remove the translation of mid upper torso matrix so that the leg does not bob up and down
	Matrix4 midUpperTorsoNoTranslationMatrix = midUpperTorsoMatrix;
	midUpperTorsoNoTranslationMatrix.data[12] = 0.0f;
	midUpperTorsoNoTranslationMatrix.data[13] = 0.0f;
	midUpperTorsoNoTranslationMatrix.data[14] = 0.0f;

	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoNoTranslationMatrix * bottomLeftLowerTorsoMatrix * leftLegMatrix;
	glLoadMatrixf(mvp.data);

	std::vector<cylindroidLoopValues> loops;

	loops.push_back(cylindroidLoopValues(1.2f, 0.0f, Vector3(0.0f, -1.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.2f, 2.0f, Vector3(0.0f, 0.0f, 1.0f), Vector3(((sin(App::getTime() * speed) * maxAngle) + -5.0f), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.2f, 3.5f, Vector3(0.0f, 0.0f, -1.0f), Vector3(((sin(App::getTime() * speed) * maxAngle)), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.5f, 5.0f, Vector3(0.0f, 3.0f, 0.0f), Vector3(10.0f, 10.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.5f, 5.3f, Vector3(-1.0f, 6.0f, -2.0f), Vector3(45.0f, 20.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(3.0f, 5.6f, Vector3(-1.0f, 10.0f, -1.0f), Vector3(90.0f, 20.0f, 0.0f), 0.5f));
	loops.push_back(cylindroidLoopValues(0.0f, 5.6f, Vector3(-1.0f, 10.0f, -1.0f), Vector3(90.0f, 20.0f, 0.0f), 0.5f));

	leftLegCylindroid = new Cylindroid(8.0f, loops, viewProjectionMatrix, complimentColor);
	leftLegCylindroid->draw();

	// CREATING ROOT TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform rootToes;
	rootToes.rotateYBy(20.0f);
	rootToes.setPosition(-0.6f, 0.0f, 0.0f);
	Matrix4 rootToesMatrix = rootToes.getMatrix();

	// CREATING RIGHT TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform rightToe;
	rightToe.setPosition(-2.0f, 8.6f, 5.0f);
	rightToe.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * midUpperTorsoNoTranslationMatrix * bottomLeftLowerTorsoMatrix * leftLegMatrix * rootToesMatrix * rightToe.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, complimentColor, viewProjectionMatrix);

	// CREATING CENTER TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform centerToe;
	centerToe.setPosition(0.0f, 8.6f, 5.0f);
	centerToe.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * midUpperTorsoNoTranslationMatrix * bottomLeftLowerTorsoMatrix * leftLegMatrix * rootToesMatrix * centerToe.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, complimentColor, viewProjectionMatrix);


	// CREATING LEFT TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform leftToe;
	leftToe.setPosition(2.0f, 8.6f, 5.0f);
	leftToe.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * midUpperTorsoNoTranslationMatrix * bottomLeftLowerTorsoMatrix * leftLegMatrix * rootToesMatrix * leftToe.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, complimentColor, viewProjectionMatrix);
}

void Bodyparts::CreateRightLeg(const Matrix4& viewProjectionMatrix)
{
	// CREATING RIGHT LEG -----------------------------------------------------------------------------------------------------------------------------
	Transform rightLeg;
	rightLeg.setPosition(0.0f, 0.0f, 0.0f);
	// rotating the leg downwards and away from camera due to how cylindroids construct the loops and bridging them 
	rightLeg.setRotation(180.0f, 180.0f, 0.0f);
	Matrix4 rightLegMatrix = rightLeg.getMatrix();

	// remove the translation of mid upper torso matrix so that the leg does not bob up and down
	Matrix4 midUpperTorsoNoTranslationMatrix = midUpperTorsoMatrix;
	midUpperTorsoNoTranslationMatrix.data[12] = 0.0f;
	midUpperTorsoNoTranslationMatrix.data[13] = 0.0f;
	midUpperTorsoNoTranslationMatrix.data[14] = 0.0f;

	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoNoTranslationMatrix * bottomRightLowerTorsoMatrix * rightLegMatrix;
	glLoadMatrixf(mvp.data);

	std::vector<cylindroidLoopValues> loops;

	loops.push_back(cylindroidLoopValues(1.2f, 0.0f, Vector3(0.0f, -1.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.2f, 2.0f, Vector3(0.0f, 0.0f, 1.0f), Vector3(((sin(App::getTime() * speed) * maxAngle) + -5.0f), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.2f, 3.5f, Vector3(0.0f, 0.0f, -1.0f), Vector3(((sin(App::getTime() * speed) * maxAngle)), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.5f, 5.0f, Vector3(0.0f, 3.0f, 0.0f), Vector3(10.0f, -10.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.5f, 5.3f, Vector3(1.0f, 6.0f, -2.0f), Vector3(45.0f, -20.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(3.0f, 5.6f, Vector3(1.0f, 10.0f, -1.0f), Vector3(90.0f, -20.0f, 0.0f), 0.5f));
	loops.push_back(cylindroidLoopValues(0.0f, 5.6f, Vector3(1.0f, 10.0f, -1.0f), Vector3(90.0f, -20.0f, 0.0f), 0.5f));

	rightLegCylindroid = new Cylindroid(8.0f, loops, viewProjectionMatrix, complimentColor);
	rightLegCylindroid->draw();

	// CREATING ROOT TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform rootToes;
	rootToes.rotateYBy(-20.0f);
	rootToes.setPosition(0.6f, 0.0f, 0.0f);
	Matrix4 rootToesMatrix = rootToes.getMatrix();


	// CREATING RIGHT TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform rightToe;
	rightToe.setPosition(-2.0f, 8.6f, 5.0f);
	rightToe.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * midUpperTorsoNoTranslationMatrix * bottomRightLowerTorsoMatrix * rightLegMatrix * rootToesMatrix * rightToe.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, complimentColor, viewProjectionMatrix);

	// CREATING CENTER TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform centerToe;
	centerToe.setPosition(0.0f, 8.6f, 5.0f);
	centerToe.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * midUpperTorsoNoTranslationMatrix * bottomRightLowerTorsoMatrix * rightLegMatrix * rootToesMatrix * centerToe.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, complimentColor, viewProjectionMatrix);


	// CREATING LEFT TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform leftToe;
	leftToe.setPosition(2.0f, 8.6f, 5.0f);
	leftToe.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * midUpperTorsoNoTranslationMatrix * bottomRightLowerTorsoMatrix * rightLegMatrix * rootToesMatrix * leftToe.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, complimentColor, viewProjectionMatrix);
}

void Bodyparts::CreateLeftArm(const Matrix4& viewProjectionMatrix)
{
	// CREATING LEFT ARM BRACER -----------------------------------------------------------------------------------------------------------------------------
	Transform leftArmBracer;
	leftArmBracer.setPosition(-3.0f, 6.0f, 0.0f);
	leftArmBracer.setRotation(90.0f, -90.0f, 0.0f);
	Matrix4 leftArmBracerMatrix = leftArmBracer.getMatrix();

	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoMatrix * leftArmBracerMatrix;
	glLoadMatrixf(mvp.data);
	shapes.CreateCylinder(cylinderValues(8, 2.0f, 2.0f, 1.5f, 1.0f), colorValues(complimentColor.r, complimentColor.g, complimentColor.b, complimentColor.a));

	// CREATING LEFT ARM -----------------------------------------------------------------------------------------------------------------------------

	Transform leftArm;
	leftArm.setPosition(0.0f, 1.5f, 0.0f);
	Matrix4 leftArmMatrix = leftArm.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * leftArmBracerMatrix * leftArmMatrix;
	glLoadMatrixf(mvp.data);

	std::vector<cylindroidLoopValues> loops;

	loops.push_back(cylindroidLoopValues(1.5f, 0.0f));
	loops.push_back(cylindroidLoopValues(1.5f, 2.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(45.0f, 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.5f, 6.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(Oscillation(45.0f, speed, maxAngle), 0.0f, Oscillation(-20.0f, speed, maxAngle))));
	loops.push_back(cylindroidLoopValues(2.5f, 7.0f, Vector3(2.0f, 5.0f, 2.0f), Vector3(Oscillation(45.0f, speed, maxAngle), Oscillation(15.0f, speed, maxAngle), Oscillation(-60.0f, speed, maxAngle)), 0.5f));
	loops.push_back(cylindroidLoopValues(0.0f, 7.0f, Vector3(2.0f, 5.0f, 2.0f), Vector3(Oscillation(45.0f, speed, maxAngle), Oscillation(15.0f, speed, maxAngle), Oscillation(-60.0f, speed, maxAngle)), 0.5f));

	leftArmCylindroid = new Cylindroid(8.0f, loops, viewProjectionMatrix, mainColor);
	leftArmCylindroid->draw();

	Vector3 handEndPoint = leftArmCylindroid->getEndPosition();

	// CREATING WHITE SPIKE -----------------------------------------------------------------------------------------------------------------------------
	Transform spike;
	spike.setRotation(Oscillation(70.0f, speed, maxAngle), Oscillation(200.0f, speed, maxAngle), Oscillation(-70.0f, speed, maxAngle));
	//spike.rotateXBy(-90.0f);
	spike.setPosition(handEndPoint.x - 1.0f, handEndPoint.y, handEndPoint.z - 1.2f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * leftArmBracerMatrix * leftArmMatrix * spike.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 0.0f, 1.0f, 2.5f, 1.0f), colorValues(clearColor.r, clearColor.g, clearColor.b, clearColor.a));

	// CREATING ROOT FINGERS -----------------------------------------------------------------------------------------------------------------------------

	Transform rootFingers;
	rootFingers.setRotation(Oscillation(40.0f, speed, maxAngle), Oscillation(30.0f, speed, maxAngle), Oscillation(-70.0f, speed, maxAngle));
	rootFingers.setPosition(handEndPoint.x - 0.5f, handEndPoint.y, handEndPoint.z);
	Matrix4 rootFingersMatrix = rootFingers.getMatrix();

	// CREATING RIGHT FINGER -----------------------------------------------------------------------------------------------------------------------------
	Transform rightFinger;
	rightFinger.setPosition(1.5f, 0.5f, 0.5f);
	rightFinger.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * midUpperTorsoMatrix * leftArmBracerMatrix * leftArmMatrix * rootFingersMatrix * rightFinger.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, complimentColor, viewProjectionMatrix);

	// CREATING CENTER FINGER -----------------------------------------------------------------------------------------------------------------------------
	Transform centerFinger;
	centerFinger.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * midUpperTorsoMatrix * leftArmBracerMatrix * leftArmMatrix * rootFingersMatrix * centerFinger.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, complimentColor, viewProjectionMatrix);


	// CREATING LEFT FINGER -----------------------------------------------------------------------------------------------------------------------------
	Transform leftFinger;
	leftFinger.setPosition(-1.5f, -0.5f, -0.5f);
	leftFinger.setScale(0.6f, 0.6f, 0.6f);;
	mvp = viewProjectionMatrix * midUpperTorsoMatrix * leftArmBracerMatrix * leftArmMatrix * rootFingersMatrix * leftFinger.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, complimentColor, viewProjectionMatrix);
}

void Bodyparts::CreateRightArm(const Matrix4& viewProjectionMatrix)
{

	// CREATING RIGHT ARM BRACER -----------------------------------------------------------------------------------------------------------------------------

	Transform rightArmBracer;
	rightArmBracer.setPosition(3.0f, 6.0f, 0.0f);
	rightArmBracer.setRotation(90.0f, 90.0f, 0.0f);
	Matrix4 rightArmBracerMatrix = rightArmBracer.getMatrix();

	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoMatrix * rightArmBracerMatrix;
	glLoadMatrixf(mvp.data);
	shapes.CreateCylinder(cylinderValues(8, 2.0f, 2.0f, 1.5f, 1.0f), colorValues(complimentColor.r, complimentColor.g, complimentColor.b, complimentColor.a));

	// CREATING RIGHT ARM -----------------------------------------------------------------------------------------------------------------------------

	Transform rightArm;
	rightArm.setPosition(0.0f, 1.5f, 0.0f);
	Matrix4 rightArmMatrix = rightArm.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * rightArmBracerMatrix * rightArmMatrix;
	glLoadMatrixf(mvp.data);

	std::vector<cylindroidLoopValues> loops;

	loops.push_back(cylindroidLoopValues(1.5f, 0.0f));

	loops.push_back(cylindroidLoopValues(1.5f, 2.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(45.0f, 0.0f, 0.0f)));

	loops.push_back(cylindroidLoopValues(1.5f, 6.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(Oscillation(45.0f, speed, maxAngle), 0.0f, -Oscillation(-20.0f, speed, maxAngle))));

	loops.push_back(cylindroidLoopValues(2.5f, 7.0f, Vector3(-2.0f, 5.0f, 2.0f), Vector3(Oscillation(45.0f, speed, maxAngle), -Oscillation(15.0f, speed, maxAngle), -Oscillation(-60.0f, speed, maxAngle)), 0.5f));

	loops.push_back(cylindroidLoopValues(0.0f, 7.0f, Vector3(-2.0f, 5.0f, 2.0f), Vector3(Oscillation(45.0f, speed, maxAngle), -Oscillation(15.0f, speed, maxAngle), -Oscillation(-60.0f, speed, maxAngle)), 0.5f));

	rightArmCylindroid = new Cylindroid(8.0f, loops, viewProjectionMatrix, mainColor);
	rightArmCylindroid->draw();

	Vector3 handEndPoint = rightArmCylindroid->getEndPosition();


	// WHITE SPIKE -----------------------------------------------------------------------------------------------------------------------------

	Transform spike;
	spike.setRotation(Oscillation(70.0f, speed, maxAngle), -Oscillation(200.0f, speed, maxAngle), -Oscillation(-70.0f, speed, maxAngle));

	spike.setPosition(handEndPoint.x + 1.0f, handEndPoint.y, handEndPoint.z - 1.2f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * rightArmBracerMatrix * rightArmMatrix * spike.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 0.0f, 1.0f, 2.5f, 1.0f), colorValues(clearColor.r, clearColor.g, clearColor.b, clearColor.a)
	);


	// ROOT FINGERS -----------------------------------------------------------------------------------------------------------------------------

	Transform rootFingers;
	rootFingers.setRotation(Oscillation(40.0f, speed, maxAngle), -Oscillation(30.0f, speed, maxAngle), -Oscillation(-70.0f, speed, maxAngle));

	rootFingers.setPosition(handEndPoint.x + 0.5f, handEndPoint.y, handEndPoint.z);

	Matrix4 rootFingersMatrix = rootFingers.getMatrix();

	// RIGHT FINGER -----------------------------------------------------------------------------------------------------------------------------

	Transform rightFinger;
	rightFinger.setPosition(-1.5f, 0.5f, 0.5f);
	rightFinger.setScale(0.6f, 0.6f, 0.6f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * rightArmBracerMatrix * rightArmMatrix * rootFingersMatrix * rightFinger.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, complimentColor, viewProjectionMatrix);


	// CENTER FINGER -----------------------------------------------------------------------------------------------------------------------------

	Transform centerFinger;
	centerFinger.setScale(0.6f, 0.6f, 0.6f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * rightArmBracerMatrix * rightArmMatrix * rootFingersMatrix * centerFinger.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, complimentColor, viewProjectionMatrix);

	// LEFT FINGER (mirrored) -----------------------------------------------------------------------------------------------------------------------------

	Transform leftFinger;
	leftFinger.setPosition(1.5f, -0.5f, -0.5f); // mirrored
	leftFinger.setScale(0.6f, 0.6f, 0.6f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * rightArmBracerMatrix * rightArmMatrix * rootFingersMatrix * leftFinger.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, complimentColor, viewProjectionMatrix);
}