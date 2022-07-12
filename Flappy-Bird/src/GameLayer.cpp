#include "GameLayer.h"


GameLayer::GameLayer()
	: Layer("Flappy-Bird"), m_State(GameState::Play)
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());
}

void GameLayer::OnAttach()
{
	m_Level.Init();

	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans-Regular.ttf", 120.0f);
}

void GameLayer::OnUpdate(Time frameTime)
{

	switch (m_State)
	{
	case GameState::Play:
	{
		m_Level.OnUpdate(frameTime);

		if (m_Level.IsGameOver() == true)
			m_State = GameState::GameOver;

		m_Camera->SetPosition(m_Level.GetPlayer().GetPosition());
		break;
	}
	case GameState::GameOver:
	{
		m_ElapsedTime += frameTime.AsSeconds();
		if ((int)(m_ElapsedTime * 10.0f) % 8 > 4)
			m_Blink = !m_Blink;
	}
	}

	Renderer2D::ResetStats();
	RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

	Renderer2D::BeginScene(*m_Camera);

	m_Level.OnRender();

	Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
	switch (m_State)
	{
	case GameState::Play:
	{
		uint32_t playerScore = m_Level.GetPlayer().GetScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
		break;
	}
	case GameState::Menu:
	{
		auto pos = ImGui::GetWindowPos();
		auto width = Application::Get().GetWindow().GetWidth();
		auto height = Application::Get().GetWindow().GetHeight();
		pos.x += width * 0.5f - 400.0f;
		pos.y += 50.0f;
		ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Press Enter to Play!");
		break;
	}
	case GameState::GameOver:
	{
		auto pos = ImGui::GetWindowPos();
		auto width = Application::Get().GetWindow().GetWidth();
		auto height = Application::Get().GetWindow().GetHeight();
		pos.x += width * 0.5f - 400.0f;
		pos.y += 50.0f;
		if (m_Blink)
			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Press Enter to Play!");

		pos.x += 300.0f;
		pos.y += 150.0f;
		uint32_t playerScore = m_Level.GetPlayer().GetScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
		break;
	}
	}
}

void GameLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizedEvent>(ATN_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<KeyPressedEvent>(ATN_BIND_EVENT_FN(GameLayer::OnKeyPressed));
}

bool GameLayer::OnWindowResize(WindowResizedEvent& event)
{
	CreateCamera(event.GetWidth(), event.GetHeight());
	m_Camera->SetPosition(m_Level.GetPlayer().GetPosition());

	return false;
}

bool GameLayer::OnKeyPressed(KeyPressedEvent & event)
{
	KeyCode key = event.GetKeyCode();
	if (key == Key::Enter)
	{
		if (m_State == GameState::GameOver)
		{
			m_Level.Reset();
			m_State = GameState::Play;
		}
		else if (m_State == GameState::Menu)
		{
			m_State = GameState::Play;
		}
	}

	else if (key == Key::Escape)
	{
		m_State = GameState::Menu;
	}

	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camHeight = 8.0f;
	float bottom = -camHeight;
	float top = camHeight;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}
