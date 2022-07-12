#include "Player.h"


void Player::Reset()
{
	m_Position = { -10.f, 0 };
	m_Velocity = { 4.f, 0 };
}

void Player::Init()
{
	m_Rocket = Texture2D::Create("assets/textures/rocket.png");

	m_EngineParticle.Position = { 0, 0 };
	m_EngineParticle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_EngineParticle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_EngineParticle.SizeBegin = 0.5f;
	m_EngineParticle.SizeVariation = 0.3f;
	m_EngineParticle.SizeEnd = 0.f;
	m_EngineParticle.Velocity = { -2.0f, 0.0f };
	m_EngineParticle.VelocityVariation = { 3.0f, 1.0f };
	m_EngineParticle.LifeTime = 1.f;

	m_SmokeParticle.Position = { 0, 0 };
	m_SmokeParticle.ColorBegin = { 0.8f, 0.8f, 0.8f, 1.0f };
	m_SmokeParticle.ColorEnd = { 0.6f, 0.6f, 0.6f, 1.0f };
	m_SmokeParticle.SizeBegin = 0.35f;
	m_SmokeParticle.SizeVariation = 0.15f;
	m_SmokeParticle.SizeEnd = 0.f;
	m_SmokeParticle.Velocity = { -2.0f, 0.0f };
	m_SmokeParticle.VelocityVariation = { 4.0f, 2.0f };
	m_SmokeParticle.LifeTime = 4.f;
}

void Player::OnUpdate(Time frameTime)
{
	float seconds = frameTime.AsSeconds();

	if (Input::IsMouseButtonPressed(Mouse::Left) || Input::IsKeyPressed(Key::Space))
	{
		m_Velocity.y += m_EnginePower * seconds;

		Vector2 emitter = { 0.f, 0.6f };
		Vector4 rotated = Vector4(emitter.x, emitter.y, 0, 1) * Rotate(DegreeToRad(m_Rotation), { 0, 0, 1 });
		m_EngineParticle.Position = m_Position - Vector2(rotated.x, rotated.y);
		m_ParticleSystem.Emit(m_EngineParticle);
	}
	else
	{
		m_Velocity.y -= m_Gravity * seconds;
	}

	m_Velocity.x += seconds * 0.1f;
	m_Velocity.y = Clamp(m_Velocity.y, -70.f / 8.f, 80.f / 8.f);
	m_Rotation = -90 + m_Velocity.y * 8;

	m_Position += m_Velocity * seconds;

	m_ElapsedTime += seconds;
	if (m_ElapsedTime > m_SmokeNextTime)
	{
		m_SmokeParticle.Position = m_Position;
		m_ParticleSystem.Emit(m_SmokeParticle);
		m_SmokeNextTime += m_SmokeInterval;
	}

	m_ParticleSystem.OnUpdate(frameTime);
}

void Player::OnRender()
{
	m_ParticleSystem.OnRender();
	Renderer2D::DrawRotatedQuad({m_Position.x, m_Position.y, 0.f}, { 0.87f, 1.3f }, DegreeToRad(m_Rotation), m_Rocket);
}
