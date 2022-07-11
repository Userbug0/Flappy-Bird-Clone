#include "Level.h"


void Level::Init()
{
	m_Player.Init();
	m_PillarTexture = Texture2D::Create("assets/textures/Triangle.png");
}

void Level::Reset()
{

}

void Level::OnUpdate(Time frameTime)
{
	m_Player.OnUpdate(frameTime);
}

void Level::OnRender()
{
	Renderer2D::DrawQuad({ 3, -3, 1.9f}, {5, 5}, m_PillarTexture);
	m_Player.OnRender();
}
