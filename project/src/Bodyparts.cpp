// Get the header of the signature declare in Bodyparts
#include "Bodyparts.h"

// Require the use of openGL functionality
#include <glad/glad.h>

// Require the use of Matrix4
#include "angle_util/matrix.h"



// Require the used of App::getTime
#include "Framework/app.h"

// Require the use transform wrappers to more readability
#include "Transform.h"

// Require the cylindroid to create seamless bodyparts by chaining different sizes of loops
#include "Cylindroid.h"

#include "MeshValues.h"

#include "Utility.h"

#include <corecrt_math_defines.h>

// Declare colors used for each part of the pokemon
colorValues defaultColor = colorValues(1.0f, 1.0f, 1.0f, 1.0f);

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

float speed = 1.5f;
float maxAngle = 10.0f;
float amplitude = 0.1f;
Vector3 overallScale = Vector3(0.1f, 0.1f, 0.1f);

// Create a single instance of cylindroid and point to the original class of cylindroid for each body part
Cylindroid* leftLegCylindroid;
Cylindroid* rightLegCylindroid;
Cylindroid* leftArmCylindroid;
Cylindroid* rightArmCylindroid;
Cylindroid* hairCylindroid;
Cylindroid* tailCylindroid;

void Bodyparts::CreateUpperTorso(const Matrix4& viewProjectionMatrix, const Matrix4& overallMatrix, Shapes& shapes, Texture2D* torsoTexture, Texture2D* spikeTexture)
{
	// CREATING MID UPPER TORSO -----------------------------------------------------------------------------------------------------------------------------
	// translate the mid upper torso to go up and down using sin waves and adjust it to be at the back of scene for better view
	// 
	//midUpperTorso.setPosition(0.0f, (sin(App::getTime()) * speed) * amplitude, 0.0f);
	midUpperTorso.setPosition(0.0f, Oscillation(0.0f, speed, amplitude), 0.0f);
	midUpperTorso.setScale(overallScale.x, overallScale.y, overallScale.z);

	// getting the matrix from the transform and setting this as the root
	midUpperTorsoMatrix = overallMatrix * midUpperTorso.getMatrix();

	// Moves the mid upper torso object from local space to world space
	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoMatrix;

	// replaces the current matrix to the completed mid upper torso matrix in world space
	glLoadMatrixf(mvp.data);

	// Creating the mesh model for the mid upper torso
	shapes.CreateCylinder(cylinderValues(8, 3.5f, 3.5f, 4.0f, 0.5f), defaultColor, false, false, torsoTexture);

	// CREATING TOP UPPER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform topUpperTorso;
	topUpperTorso.setPosition(0.0f, 4.0f, 0.0f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * topUpperTorso.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 4.0f, 3.5f, 3.0f, 0.5f), defaultColor, true, false, torsoTexture);

	// CREATING BOTTOM UPPER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform bottomUpperTorso;
	bottomUpperTorso.setPosition(0.0f, -2.0f, 0.0f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomUpperTorso.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 3.5f, 4.0f, 2.0f, 0.5f), defaultColor, false, false, torsoTexture);

	// CREATING WHITE SPIKE -----------------------------------------------------------------------------------------------------------------------------
	Transform spike;
	spike.rotateXBy(90.0f);
	spike.setPosition(0.0f, 4.0f, 1.5f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * spike.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 0.0f, 1.0f, 2.5f, 1.0f), defaultColor, false, false, spikeTexture);
}

void Bodyparts::CreateLowerTorso(const Matrix4& viewProjectionMatrix, Shapes& shapes, Texture2D* beltTexture, Texture2D* lowerTorsoTexture)
{
	// CREATING TOP LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform topLowerTorso;
	topLowerTorso.setPosition(0.0f, -3.5f, 0.0f);
	Matrix4 topLowerTorsoMatrix = topLowerTorso.getMatrix();

	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoMatrix * topLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 4.0f, 4.5f, 1.5f, 0.5f), defaultColor, false, false, beltTexture);

	// CREATING MID LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform midLowerTorso;
	midLowerTorso.setPosition(0.0f, -2.0f, 0.0f);
	Matrix4 midLowerTorsoMatrix = midLowerTorso.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * topLowerTorsoMatrix * midLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 4.5f, 5.5f, 2.0f, 0.5f), defaultColor, false, false, lowerTorsoTexture);

	//CREATING BOTTOM LEFT LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform bottomLeftLowerTorso;
	bottomLeftLowerTorso.setPosition(-3.0f, -6.0f, 0.0f);
	bottomLeftLowerTorsoMatrix = topLowerTorsoMatrix * midLowerTorsoMatrix * bottomLeftLowerTorso.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomLeftLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 2.5f, 2.5f, 6.0f, 0.85f), defaultColor, true, true, lowerTorsoTexture);

	//CREATING BOTTOM MID LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform bottomMidLowerTorso;
	bottomMidLowerTorso.setPosition(0.0f, -3.0f, 0.0f);
	Matrix4 bottomMidLowerTorsoMatrix = topLowerTorsoMatrix * midLowerTorsoMatrix * bottomMidLowerTorso.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomMidLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 5.5f, 4.5f, 3.0f, 0.5f), defaultColor, false, true, lowerTorsoTexture);

	// CREATING BOTTOM RIGHT LOWER TORSO -----------------------------------------------------------------------------------------------------------------------------
	Transform bottomRightLowerTorso;
	bottomRightLowerTorso.setPosition(3.0f, -6.0f, 0.0f);
	bottomRightLowerTorsoMatrix = topLowerTorsoMatrix * midLowerTorsoMatrix * bottomRightLowerTorso.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * bottomRightLowerTorsoMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 2.5f, 2.5f, 6.0f, 0.85f), defaultColor, true, true, lowerTorsoTexture);
}

void Bodyparts::CreateLeftLeg(const Matrix4& viewProjectionMatrix, const Matrix4& overallMatrix, Shapes& shapes, Texture2D* legTexture, Texture2D* toeTexture)
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

	Matrix4 mvp = viewProjectionMatrix * overallMatrix * midUpperTorsoNoTranslationMatrix * bottomLeftLowerTorsoMatrix * leftLegMatrix;
	glLoadMatrixf(mvp.data);

	std::vector<cylindroidLoopValues> loops;

	loops.push_back(cylindroidLoopValues(1.2f, 0.0f, Vector3(0.0f, -1.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.2f, 2.0f, Vector3(0.0f, 0.0f, 1.0f), Vector3(Oscillation(-10.0f, speed, maxAngle), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.2f, 3.5f, Vector3(0.0f, 0.0f, -1.0f), Vector3(Oscillation(0.0f, speed, maxAngle), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.5f, 5.0f, Vector3(0.0f, 3.0f, 0.0f), Vector3(10.0f, 10.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.5f, 5.3f, Vector3(-1.0f, 6.5f, -2.0f), Vector3(45.0f, 20.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(3.0f, 5.6f, Vector3(-1.0f, 10.3f, -1.0f), Vector3(90.0f, 20.0f, 0.0f), 0.4f));
	loops.push_back(cylindroidLoopValues(0.0f, 5.6f, Vector3(-1.0f, 10.3f, -1.0f), Vector3(90.0f, 20.0f, 0.0f)));

	leftLegCylindroid = new Cylindroid(8.0f, loops, viewProjectionMatrix, defaultColor, legTexture);
	leftLegCylindroid->draw();

	// CREATING ROOT TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform rootToes;
	rootToes.rotateYBy(20.0f);
	rootToes.setPosition(-0.6f, 0.5f, 0.0f);
	Matrix4 rootToesMatrix = rootToes.getMatrix();

	// CREATING RIGHT TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform rightToe;
	rightToe.setPosition(-2.0f, 8.6f, 5.0f);
	rightToe.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * overallMatrix * midUpperTorsoNoTranslationMatrix * bottomLeftLowerTorsoMatrix * leftLegMatrix * rootToesMatrix * rightToe.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, defaultColor, viewProjectionMatrix, toeTexture);

	// CREATING CENTER TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform centerToe;
	centerToe.setPosition(0.0f, 8.6f, 5.0f);
	centerToe.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * overallMatrix * midUpperTorsoNoTranslationMatrix * bottomLeftLowerTorsoMatrix * leftLegMatrix * rootToesMatrix * centerToe.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, defaultColor, viewProjectionMatrix, toeTexture);


	// CREATING LEFT TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform leftToe;
	leftToe.setPosition(2.0f, 8.6f, 5.0f);
	leftToe.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * overallMatrix * midUpperTorsoNoTranslationMatrix * bottomLeftLowerTorsoMatrix * leftLegMatrix * rootToesMatrix * leftToe.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, defaultColor, viewProjectionMatrix, toeTexture);
}

void Bodyparts::CreateRightLeg(const Matrix4& viewProjectionMatrix, const Matrix4& overallMatrix, Shapes& shapes, Texture2D* legTexture, Texture2D* toeTexture)
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

	Matrix4 mvp = viewProjectionMatrix * overallMatrix * midUpperTorsoNoTranslationMatrix * bottomRightLowerTorsoMatrix * rightLegMatrix;
	glLoadMatrixf(mvp.data);

	std::vector<cylindroidLoopValues> loops;

	loops.push_back(cylindroidLoopValues(1.2f, 0.0f, Vector3(0.0f, -1.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.2f, 2.0f, Vector3(0.0f, 0.0f, 1.0f), Vector3(Oscillation(-10.0f, speed, maxAngle), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.2f, 3.5f, Vector3(0.0f, 0.0f, -1.0f), Vector3(Oscillation(0.0f, speed, maxAngle), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.5f, 5.0f, Vector3(0.0f, 3.0f, 0.0f), Vector3(10.0f, -10.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.5f, 5.3f, Vector3(1.0f, 6.5f, -2.0f), Vector3(45.0f, -20.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(3.0f, 5.6f, Vector3(1.0f, 10.3f, -1.0f), Vector3(90.0f, -20.0f, 0.0f), 0.4f));
	loops.push_back(cylindroidLoopValues(0.0f, 5.6f, Vector3(1.0f, 10.3f, -1.0f), Vector3(90.0f, -20.0f, 0.0f)));

	rightLegCylindroid = new Cylindroid(8.0f, loops, viewProjectionMatrix, defaultColor, legTexture);
	rightLegCylindroid->draw();

	// CREATING ROOT TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform rootToes;
	rootToes.rotateYBy(-20.0f);
	rootToes.setPosition(0.6f, 0.5f, 0.0f);
	Matrix4 rootToesMatrix = rootToes.getMatrix();


	// CREATING RIGHT TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform rightToe;
	rightToe.setPosition(-2.0f, 8.6f, 5.0f);
	rightToe.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * overallMatrix * midUpperTorsoNoTranslationMatrix * bottomRightLowerTorsoMatrix * rightLegMatrix * rootToesMatrix * rightToe.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, defaultColor, viewProjectionMatrix, toeTexture);

	// CREATING CENTER TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform centerToe;
	centerToe.setPosition(0.0f, 8.6f, 5.0f);
	centerToe.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * overallMatrix * midUpperTorsoNoTranslationMatrix * bottomRightLowerTorsoMatrix * rightLegMatrix * rootToesMatrix * centerToe.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, defaultColor, viewProjectionMatrix, toeTexture);


	// CREATING LEFT TOES -----------------------------------------------------------------------------------------------------------------------------
	Transform leftToe;
	leftToe.setPosition(2.0f, 8.6f, 5.0f);
	leftToe.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * overallMatrix * midUpperTorsoNoTranslationMatrix * bottomRightLowerTorsoMatrix * rightLegMatrix * rootToesMatrix * leftToe.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, defaultColor, viewProjectionMatrix, toeTexture);
}

void Bodyparts::CreateLeftArm(const Matrix4& viewProjectionMatrix, Shapes& shapes, Texture2D* bracerTexture, Texture2D* armTexture, Texture2D* fingerTexture, Texture2D* spikeTexture)
{
	// CREATING LEFT ARM BRACER -----------------------------------------------------------------------------------------------------------------------------
	Transform leftArmBracer;
	leftArmBracer.setPosition(-3.0f, 6.0f, 0.0f);
	leftArmBracer.setRotation(90.0f, -90.0f, 0.0f);
	Matrix4 leftArmBracerMatrix = leftArmBracer.getMatrix();

	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoMatrix * leftArmBracerMatrix;
	glLoadMatrixf(mvp.data);
	shapes.CreateCylinder(cylinderValues(8, 2.0f, 2.0f, 1.5f, 1.0f), defaultColor, true, true, bracerTexture);

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

	leftArmCylindroid = new Cylindroid(8.0f, loops, viewProjectionMatrix, defaultColor, armTexture);
	leftArmCylindroid->draw();

	Vector3 handEndPoint = leftArmCylindroid->getEndPosition();

	// CREATING WHITE SPIKE -----------------------------------------------------------------------------------------------------------------------------
	Transform spike;
	spike.setRotation(Oscillation(70.0f, speed, maxAngle), Oscillation(200.0f, speed, maxAngle), Oscillation(-70.0f, speed, maxAngle));
	//spike.rotateXBy(-90.0f);
	spike.setPosition(handEndPoint.x - 1.0f, handEndPoint.y, handEndPoint.z - 1.2f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * leftArmBracerMatrix * leftArmMatrix * spike.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 0.0f, 1.0f, 2.5f, 1.0f), defaultColor, true, true, spikeTexture);

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

	shapes.CreateSphere(10, 2.0f, defaultColor, viewProjectionMatrix, fingerTexture);

	// CREATING CENTER FINGER -----------------------------------------------------------------------------------------------------------------------------
	Transform centerFinger;
	centerFinger.setScale(0.6f, 0.6f, 0.6f);
	mvp = viewProjectionMatrix * midUpperTorsoMatrix * leftArmBracerMatrix * leftArmMatrix * rootFingersMatrix * centerFinger.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, defaultColor, viewProjectionMatrix, fingerTexture);


	// CREATING LEFT FINGER -----------------------------------------------------------------------------------------------------------------------------
	Transform leftFinger;
	leftFinger.setPosition(-1.5f, -0.5f, -0.5f);
	leftFinger.setScale(0.6f, 0.6f, 0.6f);;
	mvp = viewProjectionMatrix * midUpperTorsoMatrix * leftArmBracerMatrix * leftArmMatrix * rootFingersMatrix * leftFinger.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, defaultColor, viewProjectionMatrix, fingerTexture);
}

void Bodyparts::CreateRightArm(const Matrix4& viewProjectionMatrix, Shapes& shapes, Texture2D* bracerTexture, Texture2D* armTexture, Texture2D* fingerTexture, Texture2D* spikeTexture)
{

	// CREATING RIGHT ARM BRACER -----------------------------------------------------------------------------------------------------------------------------

	Transform rightArmBracer;
	rightArmBracer.setPosition(3.0f, 6.0f, 0.0f);
	rightArmBracer.setRotation(90.0f, 90.0f, 0.0f);
	Matrix4 rightArmBracerMatrix = rightArmBracer.getMatrix();

	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoMatrix * rightArmBracerMatrix;
	glLoadMatrixf(mvp.data);
	shapes.CreateCylinder(cylinderValues(8, 2.0f, 2.0f, 1.5f, 1.0f), defaultColor, true, true, bracerTexture);

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

	rightArmCylindroid = new Cylindroid(8.0f, loops, viewProjectionMatrix, defaultColor, armTexture);
	rightArmCylindroid->draw();

	Vector3 handEndPoint = rightArmCylindroid->getEndPosition();


	// WHITE SPIKE -----------------------------------------------------------------------------------------------------------------------------

	Transform spike;
	spike.setRotation(Oscillation(70.0f, speed, maxAngle), -Oscillation(200.0f, speed, maxAngle), -Oscillation(-70.0f, speed, maxAngle));

	spike.setPosition(handEndPoint.x + 1.0f, handEndPoint.y, handEndPoint.z - 1.2f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * rightArmBracerMatrix * rightArmMatrix * spike.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 0.0f, 1.0f, 2.5f, 1.0f), defaultColor, true, true, spikeTexture);


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

	shapes.CreateSphere(10, 2.0f, defaultColor, viewProjectionMatrix, fingerTexture);


	// CENTER FINGER -----------------------------------------------------------------------------------------------------------------------------

	Transform centerFinger;
	centerFinger.setScale(0.6f, 0.6f, 0.6f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * rightArmBracerMatrix * rightArmMatrix * rootFingersMatrix * centerFinger.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, defaultColor, viewProjectionMatrix, fingerTexture);

	// LEFT FINGER -----------------------------------------------------------------------------------------------------------------------------

	Transform leftFinger;
	leftFinger.setPosition(1.5f, -0.5f, -0.5f);
	leftFinger.setScale(0.6f, 0.6f, 0.6f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * rightArmBracerMatrix * rightArmMatrix * rootFingersMatrix * leftFinger.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 2.0f, defaultColor, viewProjectionMatrix, fingerTexture);
}

void Bodyparts::CreateHead(const Matrix4& viewProjectionMatrix, Shapes& shapes, Texture2D* neckTexture, Texture2D* headTexture, Texture2D* snoutTexture, Texture2D* snoutTipTexture, Texture2D* earTexture, Texture2D* earTopBottomTexture, Texture2D* hairTexture)
{
	// CREATING NECK  -----------------------------------------------------------------------------------------------------------------------------

	Transform neck;
	neck.setPosition(0.0f, 7.0f, 0.0f);
	Matrix4 neckMatrix = neck.getMatrix();

	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 1.0f, 1.0f, 1.0f), defaultColor, false, false, neckTexture);

	// CREATING HEAD -----------------------------------------------------------------------------------------------------------------------------

	Transform head;
	head.setPosition(0.0f, 0.5f, 0.0f);
	Matrix4 headMatrix = head.getMatrix();

	Transform localHead;
	localHead.setRotation(0.0f, 63.0f, 0.0f);

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix * headMatrix * localHead.getMatrix();
	glLoadMatrixf(mvp.data);

	shapes.CreateSphere(10, 4.5f, defaultColor, viewProjectionMatrix, headTexture);

	// CREATING SNOUT -----------------------------------------------------------------------------------------------------------------------------

	Transform snout;
	snout.setRotation(-90.0f, 0.0f, -90.0f);
	snout.setPosition(0.0f, 3.0f, 7.5f);
	snout.setScale(0.8f, 1.0f, 0.8f);
	Matrix4 snoutMatrix = snout.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix * headMatrix * snoutMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 2.0f, 1.0f, 5.0f), defaultColor, false, true, snoutTexture, snoutTipTexture);

	// CREATING LEFT EAR -----------------------------------------------------------------------------------------------------------------------------

	Transform leftEar;
	leftEar.setPosition(-2.0f, 8.0f, -0.5f);
	leftEar.setRotation(0.0f, 90.0f, 0.0f);
	Matrix4 leftEarMatrix = leftEar.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix * headMatrix * leftEarMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 1.5f, 1.5f, 3.0f), defaultColor, false, false, earTexture);

	Transform leftBottomEar;
	leftBottomEar.setPosition(0.0f, -1.0f, 0.0f);
	Matrix4 leftBottomEarMatrix = leftBottomEar.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix * headMatrix * leftEarMatrix * leftBottomEarMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 1.5f, 1.5f, 1.0f), defaultColor, false, false, earTopBottomTexture);

	Transform leftTopEar;
	leftTopEar.setPosition(0.0f, 3.0f, 0.0f);
	Matrix4 leftTopEarMatrix = leftTopEar.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix * headMatrix * leftEarMatrix * leftTopEarMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 0.0f, 1.5f, 3.0f), defaultColor, false, false, earTopBottomTexture);

	// CREATING RIGHT EAR -----------------------------------------------------------------------------------------------------------------------------

	Transform rightEar;
	rightEar.setPosition(2.0f, 8.0f, -0.5f);
	rightEar.setRotation(0.0f, 90.0f, 0.0f);
	Matrix4 rightEarMatrix = rightEar.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix * headMatrix * rightEarMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 1.5f, 1.5f, 3.0f), defaultColor, false, false, earTexture);


	Transform rightBottomEar;
	rightBottomEar.setPosition(0.0f, -1.0f, 0.0f);
	Matrix4 rightBottomEarMatrix = rightBottomEar.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix * headMatrix * rightEarMatrix * rightBottomEarMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 1.5f, 1.5f, 1.0f), defaultColor, false, false, earTopBottomTexture);

	Transform rightTopEar;
	rightTopEar.setPosition(0.0f, 3.0f, 0.0f);
	Matrix4 rightTopEarMatrix = rightTopEar.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix * headMatrix * rightEarMatrix * rightTopEarMatrix;
	glLoadMatrixf(mvp.data);

	shapes.CreateCylinder(cylinderValues(8, 0.0f, 1.5f, 3.0f), defaultColor, false, false, earTopBottomTexture);

	// CREATING HAIR PAIR 1 -----------------------------------------------------------------------------------------------------------------------------

	Transform hairPair1;
	hairPair1.rotateXBy(105.0f);
	hairPair1.rotateYBy(180.0f);
	hairPair1.rotateZBy(-15.0f);
	hairPair1.setPosition(-1.5f, 7.0f, -2.5f);
	Matrix4 hairPair1Matrix = hairPair1.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix * headMatrix * hairPair1Matrix;
	glLoadMatrixf(mvp.data);

	CreateHair(viewProjectionMatrix, hairTexture);

	hairPair1.rotateYBy(30.0f);
	hairPair1.setPosition(-2.5f, 7.0f, -2.0f);
	hairPair1Matrix = hairPair1.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix * headMatrix * hairPair1Matrix;
	glLoadMatrixf(mvp.data);

	CreateHair(viewProjectionMatrix, hairTexture);

	// CREATING HAIR PAIR 2 -----------------------------------------------------------------------------------------------------------------------------

	Transform hairPair2;
	hairPair2.rotateXBy(105.0f);
	hairPair2.rotateYBy(180.0f);
	hairPair2.rotateZBy(15.0f);
	hairPair2.setPosition(1.5f, 7.0f, -2.5f);
	Matrix4 hairPair2Matrix = hairPair2.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix * headMatrix * hairPair2Matrix;
	glLoadMatrixf(mvp.data);

	CreateHair(viewProjectionMatrix, hairTexture);

	hairPair2.rotateYBy(-30.0f);
	hairPair2.setPosition(2.5f, 7.0f, -2.0f);
	hairPair2Matrix = hairPair2.getMatrix();

	mvp = viewProjectionMatrix * midUpperTorsoMatrix * neckMatrix * headMatrix * hairPair2Matrix;
	glLoadMatrixf(mvp.data);

	CreateHair(viewProjectionMatrix, hairTexture);
}

void Bodyparts::CreateHair(const Matrix4& viewProjectionMatrix, Texture2D* hairTexture)
{
	std::vector<cylindroidLoopValues> loops;

	loops.push_back(cylindroidLoopValues(0.5f, 0.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(0.8f, 2.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(Oscillation(10.0f, speed, maxAngle), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(1.5f, 6.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(Oscillation(20.0f, speed, maxAngle), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(2.0f, 12.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(Oscillation(30.0f, speed, maxAngle), 0.0f, 0.0f)));
	loops.push_back(cylindroidLoopValues(0.0f, 12.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(Oscillation(30.0f, speed, maxAngle), 0.0f, 0.0f)));

	hairCylindroid = new Cylindroid(8.0f, loops, viewProjectionMatrix, defaultColor, hairTexture);
	hairCylindroid->draw();
}

void Bodyparts::CreateTail(const Matrix4& viewProjectionMatrix, Texture2D* tailTexture)
{
	Transform tail;
	tail.rotateXBy(-90.0f);
	tail.setPosition(0.0f, -7.0f, -2.0f);
	Matrix4 tailMatrix = tail.getMatrix();

	Matrix4 mvp = viewProjectionMatrix * midUpperTorsoMatrix * tailMatrix;
	glLoadMatrixf(mvp.data);
	
	std::vector<cylindroidLoopValues> loops;

	loops.push_back(cylindroidLoopValues(1.0f, 0.0f));
	loops.push_back(cylindroidLoopValues(1.5f, 2.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(20.0f, 0.0f, Oscillation(0.0f, speed, maxAngle))));
	loops.push_back(cylindroidLoopValues(1.8f, 7.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 0.0f, Oscillation(0.0f, speed, maxAngle + 10.0f))));
	loops.push_back(cylindroidLoopValues(1.8f, 12.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 0.0f, Oscillation(0.0f, speed, maxAngle + 15.0f))));
	loops.push_back(cylindroidLoopValues(2.5f, 15.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, Oscillation(0.0f, speed, maxAngle + 20.0f))));
	loops.push_back(cylindroidLoopValues(0.0f, 16.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, Oscillation(0.0f, speed, maxAngle + 20.0f))));

	tailCylindroid = new Cylindroid(8.0f, loops, viewProjectionMatrix, defaultColor, tailTexture);
	tailCylindroid->draw();
}