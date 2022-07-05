#pragma once

#include "Athena.h"

#include "ParticlesGenerator.h"
#include "ParticlesController.h"

using namespace Athena;


class ParticlesLayer : public Layer
{
public:
	ParticlesLayer();

	void OnUpdate(Time frameTime) override;
	void OnImGuiRender() override;
	void OnEvent(Event& event) override;

private:
	ParticlesGenerator m_Generator;
	ParticlesController m_Controller;

	Color m_SquareColor;
	OrthographicCameraController m_CameraController;
};
