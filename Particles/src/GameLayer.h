#pragma once

#include "Athena.h"

#include "ParticlesGenerator.h"
#include "ParticlesController.h"

using namespace Athena;


class GameLayer : public Layer
{
public:
	GameLayer();

	void OnUpdate(Time frameTime) override;
	void OnImGuiRender() override;
	void OnEvent(Event& event) override;

private:
	void OnMouseButtonPressed();

private:
	ParticlesGenerator m_Generator;
	ParticlesController m_Controller;
	OrthographicCameraController m_CameraController;

	Ref<Texture2D> m_CheckerBoard;
	Color m_SquareColor;
};