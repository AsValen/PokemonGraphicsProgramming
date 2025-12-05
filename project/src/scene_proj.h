#pragma once
#include "framework/scenebase.h"
#include "framework/texture/texture_utils.h"
#include <glad/glad.h> // Include glad.h to use gl functions
#include "helpers/plane_gen.h"
#include "Shapes.h" 
#include "Bodyparts.h"
// Add your own includes

class Scene_Project : public SceneBase
{
private:

public:

	void init() override
	{
		// Set custom clear colour
		// Change this if you want your background to be different colour
		glClearColor(0.25f, 0.25f, 0.25f, 0.5f);
	}

	void deinit() override
	{
	}

	void update() override
	{
	}

	void draw(const Matrix4& projectionMatrix, const Matrix4& viewMatrix) override
	{
		// Apply view projection matrix.
		Matrix4 vpMatrix = projectionMatrix * viewMatrix;
		glLoadMatrixf((GLfloat*)vpMatrix.data);

		// Comment out if you do not need these -------
		// Draw grid and origin lines.
		// These two functions are from SceneBase.
		drawHorizontalGridLines();
		//drawVerticalGridLines();
		drawWorldOriginLines();

		Shapes shapes;
		
		AssemblingPokemon(vpMatrix);
		//shapes.CreateSquare(Vector3(3, 5, 0), colorValues(1.0f, 1.0f, 1.0f, 1.0f), NULL);
		//shapes.CreateCube(Vector3(5, 5, 5), colorValues(1.0f, 1.0f, 1.0f, 1.0f));
		//shapes.CreatePyramid(Vector3(5, 5, 5), colorValues(1.0f, 1.0f, 1.0f, 1.0f));
		//shapes.CreateCylinder(cylinderValues(9, 5.0f, 5.0f, 5.0f, 1.0f), colorValues(1.0f, 1.0f, 1.0f, 1.0f));
		
		// --------------------------------------------
	}

	void AssemblingPokemon(const Matrix4& vpMatrix)
	{
		Bodyparts bodyparts;
		bodyparts.CreateUpperTorso(vpMatrix);
		bodyparts.CreateLowerTorso(vpMatrix);

	}
};