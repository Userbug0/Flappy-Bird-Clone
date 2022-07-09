#include "GameLayer.h"

#include <ImGui/imgui.h>


GameLayer::GameLayer()
	: Layer("Particles"), m_Generator(10000), m_CameraController(16.f / 9.f), m_SquareColor(Color::White)
{
	m_CheckerBoard = Texture2D::Create("assets/textures/CheckerBoard.png");
}

void GameLayer::OnUpdate(Time frameTime)
{
	Renderer2D::ResetStats();
	RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

	m_CameraController.OnUpdate(frameTime);

	if (Input::IsMouseButtonPressed(Mouse::Left) || Input::IsMouseButtonPressed(Mouse::Right))
		OnMouseButtonPressed();

	Renderer2D::BeginScene(m_CameraController.GetCamera());

	Renderer2D::DrawQuad({ -0.f, -0.f, 0.1f }, { 10.f, 10.f }, m_CheckerBoard, 10, Color(1.f, 0.95f, 0.95f));

	for (float x = -2.5f; x < 2.5f; x += 0.23f)
	{
		for (float y = -2.5f; y < 2.5f; y += 0.23f)
		{
			Color color = { (x + 2.5f) / 5, 0.4f, (y + 2.5f) / 5, 0.7f };
			Renderer2D::DrawQuad({ x, y, 0.05f }, { 0.2f, 0.2f }, color);
		}
	}

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
	x = bounds.GetWidth() * 0.5f - (x / width) * bounds.GetWidth();
	y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
	desc.Position = { x + pos.x, y + pos.y };
	for(int i = 0; i < desc.Amount; ++i)
		m_Generator.Emit(desc);
}
