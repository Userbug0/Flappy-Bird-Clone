#include "ParticlesController.h"

#include <ImGui/imgui.h>


ParticlesController::ParticlesController()
{
	m_ParticleDesc.Position = Vector2(0);
	m_ParticleDesc.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };;
	m_ParticleDesc.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };

	m_ParticleDesc.SizeBegin = 0.15f;
	m_ParticleDesc.SizeVariation = 0.05f; 
	m_ParticleDesc.SizeEnd = 0.f;

	m_ParticleDesc.Velocity = { 0, 0 };
	m_ParticleDesc.VelocityVariation = { 1.5f, 0.5f };
	m_ParticleDesc.LifeTime = 1.f;

	m_ParticleDesc.Amount = 10;
}

void ParticlesController::OnImGuiRender()
{
	ImGui::Begin("Edit");

	ImGui::ColorEdit4("Begin Color", m_ParticleDesc.ColorBegin.Data());
	ImGui::ColorEdit4("End Color", m_ParticleDesc.ColorEnd.Data());

	ImGui::DragFloat2("Velocity", m_ParticleDesc.VelocityVariation.Data(), 0.1f, 0.1f, 10);
	ImGui::DragFloat("Size", &m_ParticleDesc.SizeBegin, 0.02f, 0.05f, 2.f);

	ImGui::DragFloat("Life Time", &m_ParticleDesc.LifeTime, 0.1f, 0.1f, 10.f);

	ImGui::DragFloat("Amount", &m_ParticleDesc.Amount, 0.5f, 1, 100);

	ImGui::End();
}

