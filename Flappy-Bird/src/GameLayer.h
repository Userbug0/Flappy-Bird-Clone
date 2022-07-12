#pragma once

#include "Athena.h"

#include "ParticlesGenerator.h"
#include "Level.h"

#include <ImGui/imgui.h>


using namespace Athena;


class GameLayer : public Layer
{
public:
	GameLayer();

	void OnAttach() override;

	void OnUpdate(Time frameTime) override;
	void OnImGuiRender() override;
	void OnEvent(Event& event) override;

private:
	void CreateCamera(uint32_t width, uint32_t height);

	bool OnWindowResize(WindowResizedEvent& event);
	bool OnKeyPressed(KeyPressedEvent& event);

private:
	enum class GameState
	{
		Play = 0, Menu = 1, GameOver = 2
	};
	GameState m_State;

	Level m_Level;
	Scope<OrthographicCamera> m_Camera;
	ImFont* m_Font;

	bool m_Blink = false;
	float m_ElapsedTime = 0.f;
};
