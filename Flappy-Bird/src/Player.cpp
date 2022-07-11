#include "Player.h"


void Player::Init()
{
	m_Rocket = Texture2D::Create("assets/textures/rocket.png");

	m_EngineParticle.Position = { 0, 0 };
	m_EngineParticle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_EngineParticle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_EngineParticle.SizeBegin = 0.15f;
	m_EngineParticle.SizeVariation = 0.05f;
	m_EngineParticle.SizeEnd = 0.f;
	m_EngineParticle.Velocity = { 0, 0 };
	m_EngineParticle.VelocityVariation = { 1.5f, 0.5f };
	m_EngineParticle.LifeTime = 1.f;

	m_SmokeParticle.Position = { 0, 0 };
	m_SmokeParticle.ColorBegin = { 0.8f, 0.8f, 0.8f, 1.0f };
	m_SmokeParticle.ColorEnd = { 0.6f, 0.6f, 0.6f, 1.0f };
	m_SmokeParticle.SizeBegin = 0.15f;
	m_SmokeParticle.SizeVariation = 0.05f;
	m_SmokeParticle.SizeEnd = 0.f;
	m_SmokeParticle.Velocity = { 0, 0 };
	m_SmokeParticle.VelocityVariation = { 1.5f, 0.5f };
	m_SmokeParticle.LifeTime = 4.f;
}

void Player::OnUpdate(Time frameTime)
{

}

void Player::OnRender()
{

}
