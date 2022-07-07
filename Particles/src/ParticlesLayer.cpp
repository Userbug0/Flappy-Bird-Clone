#include "ParticlesLayer.h"

#include <ImGui/imgui.h>


ParticlesLayer::ParticlesLayer()
	: Layer("Particles"), m_CameraController(16.f / 9.f), m_SquareColor(Color::White)
{

}

void ParticlesLayer::OnUpdate(Time frameTime)
{
	Renderer2D::ResetStats();
	RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

	m_CameraController.OnUpdate(frameTime);

	m_Generator.Emit(m_Controller.GetParticleDesc());

	Renderer2D::BeginScene(m_CameraController.GetCamera());
	m_Generator.OnUpdate(frameTime);
	Renderer2D::EndScene();
}

void ParticlesLayer::OnImGuiRender()
{
	ImGui::Begin("Renderer2D Stats");

	auto stats = Renderer2D::GetStats();
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::End();

	m_Controller.OnImGuiRender();
}

void ParticlesLayer::OnEvent(Event& event)
{
	m_CameraController.OnEvent(event);
	m_Generator.OnEvent(event);
}
