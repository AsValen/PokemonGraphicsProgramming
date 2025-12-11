#pragma once
#include "framework/scenebase.h"
#include "framework/texture/texture_utils.h"
#include <glad/glad.h> // Include glad.h to use gl functions
#include "helpers/plane_gen.h"
#include "Shapes.h" 
#include "Bodyparts.h"
#include "Transform.h"
#include "Props.h"



class Scene_Project : public SceneBase
{
private:

	Shapes shapes;
	Props props;

	float alphaTestMinVal = 0.0f;

	Texture2D* torsoTexture;
	Texture2D* beltTexture;
	Texture2D* lowerTorsoTexture;

	Texture2D* legTexture;
	Texture2D* toeTexture;

	Texture2D* bracerTexture;
	Texture2D* armTexture;
	Texture2D* fingerTexture;

	Texture2D* tailTexture;
	Texture2D* spikeTexture;

	Texture2D* earTexture;
	Texture2D* topBottomEarTexture;
	Texture2D* hairTexture;
	Texture2D* neckTexture;
	Texture2D* headTexture;
	Texture2D* snoutTexture;
	Texture2D* snoutTipTexture;

	Texture2D* groundTexture;
	Texture2D* grassTexture;
	Texture2D* rockTexture;
	Texture2D* crystalTexture;

public:

	void init() override
	{
		glClearColor(0.0f, 0.2f, 0.5f, 1.0f);


		TextureConfig textureCfg(TextureWrapMode::CLAMP, TextureWrapMode::CLAMP, TextureFilterMode::NEAREST, true);
		groundTexture = TextureUtils::loadFromFile("../assets/GroundTexture.jpg", textureCfg);
		grassTexture = TextureUtils::loadFromFile("../assets/GrassTexture.png", textureCfg);
		rockTexture = TextureUtils::loadFromFile("../assets/RockTexture.jpg", textureCfg);
		crystalTexture = TextureUtils::loadFromFile("../assets/CrystalTexture.jpg", textureCfg);

		TextureConfig characterCfg(TextureWrapMode::CLAMP, TextureWrapMode::CLAMP, TextureFilterMode::LINEAR, true);
		torsoTexture = TextureUtils::loadFromFile("../assets/LucarioTorsoTexture.png", characterCfg);
		beltTexture = TextureUtils::loadFromFile("../assets/LucarioBeltTexture.png", characterCfg);
		lowerTorsoTexture = TextureUtils::loadFromFile("../assets/LucarioLowerTorsoTexture.png", characterCfg);

		legTexture = TextureUtils::loadFromFile("../assets/LucarioLegTexture6.png", characterCfg);
		toeTexture = TextureUtils::loadFromFile("../assets/LucarioFingerToeTexture.png", characterCfg);

		bracerTexture = TextureUtils::loadFromFile("../assets/LucarioArmBracerTexture.png", characterCfg);
		armTexture = TextureUtils::loadFromFile("../assets/LucarioArmTexture2.png", characterCfg);
		fingerTexture = TextureUtils::loadFromFile("../assets/LucarioFingerToeTexture.png", characterCfg);

		tailTexture = TextureUtils::loadFromFile("../assets/LucarioTailTexture.png", characterCfg);
		spikeTexture = TextureUtils::loadFromFile("../assets/LucarioSpikeTexture.png", characterCfg);

		earTexture = TextureUtils::loadFromFile("../assets/LucarioEarTexture3.png", characterCfg);
		topBottomEarTexture = TextureUtils::loadFromFile("../assets/LucarioTopBottomEarTexture.png", characterCfg);
		hairTexture = TextureUtils::loadFromFile("../assets/LucarioHairTexture.png", characterCfg);
		neckTexture = TextureUtils::loadFromFile("../assets/LucarioNeckTexture.png", characterCfg);
		headTexture = TextureUtils::loadFromFile("../assets/LucarioHeadTexture4.png", characterCfg);
		snoutTexture = TextureUtils::loadFromFile("../assets/LucarioSnoutTexture4.png", characterCfg);
		snoutTipTexture = TextureUtils::loadFromFile("../assets/LucarioSnoutTipTexture.png", characterCfg);
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
		//drawHorizontalGridLines();
		//drawVerticalGridLines();
		//drawWorldOriginLines();
		
		DrawOpaques(vpMatrix);
		DrawAlphaTest(vpMatrix);
		DrawAlphaBlend(vpMatrix);
	}

	void DrawOpaques(const Matrix4& vpMatrix)
	{
		DrawProps(vpMatrix);
		DrawPokemon(vpMatrix);
	}

	void DrawAlphaTest(const Matrix4& vpMatrix)
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, alphaTestMinVal);

		DrawAlphaTestProps(vpMatrix);

		glPopAttrib();
	}

	void DrawAlphaBlend(const Matrix4& vpMatrix)
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		DrawAlphaBlendProps(vpMatrix);

		glDisable(GL_BLEND);
		glPopAttrib();
	}

	void DrawPokemon(const Matrix4& vpMatrix)
	{
		Transform overallPokemon;
		overallPokemon.setPosition(0.0f, 2.3f, 0.0f);

		Matrix4 overallPokemonMatrix = overallPokemon.getMatrix();

		Matrix4 mvp = vpMatrix * overallPokemonMatrix;
		glLoadMatrixf(mvp.data);

		Bodyparts bodyparts;
		bodyparts.CreateUpperTorso(vpMatrix, overallPokemonMatrix, shapes, torsoTexture, spikeTexture);
		bodyparts.CreateLowerTorso(vpMatrix, shapes, beltTexture, lowerTorsoTexture);
		bodyparts.CreateLeftLeg(vpMatrix, overallPokemonMatrix, shapes, legTexture, toeTexture);
		bodyparts.CreateRightLeg(vpMatrix, overallPokemonMatrix, shapes, legTexture, toeTexture);
		bodyparts.CreateLeftArm(vpMatrix, shapes, bracerTexture, armTexture, fingerTexture, spikeTexture);
		bodyparts.CreateRightArm(vpMatrix, shapes, bracerTexture, armTexture, fingerTexture, spikeTexture);
		bodyparts.CreateHead(vpMatrix, shapes, neckTexture, headTexture, snoutTexture, snoutTipTexture, earTexture, topBottomEarTexture, hairTexture);
		bodyparts.CreateTail(vpMatrix, tailTexture);
	}

	void DrawProps(const Matrix4& vpMatrix)
	{
		props.CreateGround(vpMatrix, shapes, groundTexture);

		// Rock props
		props.CreateRock(vpMatrix, shapes, Vector3(2.0f, 0.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f), rockTexture);
		props.CreateRock(vpMatrix, shapes, Vector3(-4.0f, 0.0f, -4.0f), Vector3(1.0f, 1.0f, 1.0f), rockTexture);

		// Crystal props
		props.CreateCrystal(vpMatrix, shapes, Vector3(-1.5f, -0.2f, -2.0f), 2.0f, Vector3(0.3f, 0.3f, 0.3f), Vector3(-200.0f, 0.0f, -200.0f), crystalTexture);
		props.CreateCrystal(vpMatrix, shapes, Vector3(3.2f, -0.2f, 2.3f), 2.0f, Vector3(0.3f, 0.6f, 0.3f), Vector3(-10.0f, 0.0f, 10.0f), crystalTexture);
		props.CreateCrystal(vpMatrix, shapes, Vector3(2.5f, -0.2f, -3.0f), 2.0f, Vector3(0.5f, 0.4f, 0.5f), Vector3(-20.0f, 0.0f, -30.0f), crystalTexture);
		props.CreateCrystal(vpMatrix, shapes, Vector3(2.5f, -0.2f, -3.0f), 2.0f, Vector3(0.2f, 0.3f, 0.2f), Vector3(10.0f, 0.0f, 20.0f), crystalTexture);
	}

	void DrawAlphaTestProps(const Matrix4& vpMatrix)
	{
		// Grass props
		props.CreateGrass(vpMatrix, shapes, Vector3(-2.0f, 0.0f, 1.0f), Vector2(0.5f, 0.5f), grassTexture);
		props.CreateGrass(vpMatrix, shapes, Vector3(1.0f, 0.0f, 4.0f), Vector2(0.5f, 0.5f), grassTexture);
		props.CreateGrass(vpMatrix, shapes, Vector3(3.0f, 0.0f, -1.0f), Vector2(0.5f, 0.5f), grassTexture);
	}

	void DrawAlphaBlendProps(const Matrix4& vpMatrix)
	{
	
	}
};