#pragma once

#include "Athena.h"

using namespace Athena;


class ParticlesLayer : public Layer
{
public:
	ParticlesLayer();

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Time frameTime) override;
	void OnImGuiRender() override;
	void OnEvent(Event& event) override;

private:
	Color m_SquareColor;
	OrthographicCameraController m_CameraController;
};
