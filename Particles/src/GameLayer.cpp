#include "GameLayer.h"

#include <ImGui/imgui.h>


GameLayer::GameLayer()
	: Layer("Particles"), m_CameraController(16.f / 9.f), m_SquareColor(Color::White)
{

}

void GameLayer::OnUpdate(Time frameTime)
{
	Renderer2D::ResetStats();
	RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

	m_CameraController.OnUpdate(frameTime);

	if (Input::IsMouseButtonPressed(Mouse::Left) || Input::IsMouseButtonPressed(Mouse::Right))
		OnMouseButtonPressed();

	Renderer2D::BeginScene(m_CameraController.GetCamera());
	m_Generator.OnUpdate(frameTime);
	Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
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

void GameLayer::OnEvent(Event& event)
{
	m_CameraController.OnEvent(event);
}

void GameLayer::OnMouseButtonPressed()
{
	auto& desc = m_Controller.GetParticleDesc();
	int width = Application::Get().GetWindow().GetWidth();
	int height = Application::Get().GetWindow().GetHeight();
	auto [x, y] = Input::GetMouse();

	auto bounds = m_CameraController.GetBounds();
	Vector3 pos = m_CameraController.GetCamera().GetPosition();
	x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
	y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
	desc.Position = { -x - pos.x, y + pos.y };
	for(int i = 0; i < 5; ++i)
		m_Generator.Emit(desc);
}
