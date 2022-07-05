#include "ParticlesController.h"

#include <ImGui/imgui.h>


ParticlesController::ParticlesController()
{
	m_ParticleDesc.ColorBegin = Color::White;
}

void ParticlesController::OnImGuiRender()
{
	ImGui::Begin("Edit");

	ImGui::ColorEdit4("Square Color", m_ParticleDesc.ColorBegin.Data());

	ImGui::End();
}

