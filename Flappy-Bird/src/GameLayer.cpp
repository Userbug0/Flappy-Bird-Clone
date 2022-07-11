#include "GameLayer.h"

#include <ImGui/imgui.h>


GameLayer::GameLayer()
	: Layer("Flappy-Bird"), m_State(GameState::Play)
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());
}

void GameLayer::OnAttach()
{
	m_Level.Init();
}

void GameLayer::OnUpdate(Time frameTime)
{
	if (m_State == GameState::Play)
	{
		m_Level.OnUpdate(frameTime);
		m_Camera->SetPosition(m_Level.GetPlayer().GetPosition());
	}

	Renderer2D::ResetStats();
	RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

	Renderer2D::BeginScene(*m_Camera);

	m_Level.OnRender();

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
}

void GameLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizedEvent>(ATN_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(ATN_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnWindowResize(WindowResizedEvent& event)
{
	CreateCamera(event.GetWidth(), event.GetHeight());
	return false;
}

bool GameLayer::OnMouseButtonPressed(MouseButtonPressedEvent& event)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}
