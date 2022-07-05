#include "ParticlesLayer.h"

#include <ImGui/imgui.h>


ParticlesLayer::ParticlesLayer()
	: Layer("Particles"), m_CameraController(16.f / 9.f), m_SquareColor(Color::White)
{

}

void ParticlesLayer::OnAttach()
{

}

void ParticlesLayer::OnDetach()
{

}

void ParticlesLayer::OnUpdate(Time frameTime)
{
	Renderer2D::ResetStats();

	m_CameraController.OnUpdate(frameTime);

	RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

	static float rotation = 0.0f;
	rotation += frameTime.AsSeconds();

	Renderer2D::BeginScene(m_CameraController.GetCamera());
	Renderer2D::DrawRotatedQuad({ 0.65f, 0.65f }, { 0.8f, 0.8f }, rotation, m_SquareColor);
	Renderer2D::EndScene();
}

void ParticlesLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");

	auto stats = Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", m_SquareColor.Data());

	ImGui::End();
}

void ParticlesLayer::OnEvent(Event& event)
{
	m_CameraController.OnEvent(event);
}
