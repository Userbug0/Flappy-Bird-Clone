#include "ParticlesController.h"

#include <ImGui/imgui.h>


ParticlesController::ParticlesController()
{
	m_ParticleDesc.ColorBegin = { 0.9f, 0.4f, 0.5f };
	m_ParticleDesc.ColorEnd = Color::Green;

	m_ParticleDesc.SizeBegin = 0.5f;
	m_ParticleDesc.SizeVariation = 0.2f; 
	m_ParticleDesc.SizeEnd = 0.f;

	m_ParticleDesc.Velocity = { 0, 0 };
	m_ParticleDesc.VelocityVariation = { 4, 4 };
	m_ParticleDesc.LifeTime = 1;
}

void ParticlesController::OnImGuiRender()
{
	ImGui::Begin("Edit");

	ImGui::ColorEdit4("Begin Color", m_ParticleDesc.ColorBegin.Data());
	ImGui::ColorEdit4("End Color", m_ParticleDesc.ColorEnd.Data());

	ImGui::DragFloat2("Velocity", m_ParticleDesc.VelocityVariation.Data(), 0.1f, 1, 10);
	ImGui::DragFloat("Size", &m_ParticleDesc.SizeBegin, 0.1f, 0.1f, 1.f);

	ImGui::DragFloat("Life Time", &m_ParticleDesc.LifeTime, 0.1f, 0.1f, 10.f);

	ImGui::End();
}

