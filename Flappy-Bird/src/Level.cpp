#include "Level.h"


static Vector4 HSVtoRGB(const Vector3& hsv)
{
	int H = (int)(hsv.x * 360.0f);
	double S = hsv.y;
	double V = hsv.z;

	double C = S * V;
	double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if (H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;
	}
	else if (H >= 60 && H < 120) {
		Rs = X;
		Gs = C;
		Bs = 0;
	}
	else if (H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;
	}
	else if (H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;
	}
	else if (H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;
	}

	return { (float)(Rs + m), (float)(Gs + m), (float)(Bs + m), 1.0f };
}


void Level::Init()
{
	m_Player.Init();
	m_PillarTexture = Texture2D::Create("assets/textures/Triangle.png");

	m_Pillars.resize(5);
	for (int i = 0; i < 5; i++)
		CreatePillar(i, i * 13.0f);
}

void Level::Reset()
{
	m_Player.Reset();
}

void Level::OnUpdate(Time frameTime)
{
	m_Player.OnUpdate(frameTime);

	m_PillarHSV.x += 0.1f * frameTime.AsSeconds();
	if (m_PillarHSV.x > 1.0f)
		m_PillarHSV.x = 0.0f;

	if (m_Player.GetPosition().x > m_PillarTarget)
	{
		CreatePillar(m_PillarIndex, m_PillarTarget + 20.0f);
		m_PillarIndex = ++m_PillarIndex % m_Pillars.size();
		m_PillarTarget += 10.0f;
	}
}

void Level::OnRender()
{
	Vector2 playerPos = m_Player.GetPosition();
	Color color = HSVtoRGB(m_PillarHSV);

	// Floor and Ceil
	Renderer2D::DrawQuad({ playerPos.x,  24.f, 1.5f }, { 30.f, 30.f }, color);
	Renderer2D::DrawQuad({ playerPos.x, -24.f, 1.5f }, { 30.f, 30.f }, color);

	for (auto& pillar : m_Pillars)
	{
		Renderer2D::DrawQuad(pillar.BottomPosition, pillar.BottomScale, m_PillarTexture, 1, color);
		Renderer2D::DrawRotatedQuad(pillar.TopPosition, pillar.TopScale, DegreeToRad(180), m_PillarTexture, 1, color);
	}
	m_Player.OnRender();
}

void Level::CreatePillar(size_t index, float offset)
{
	Pillar& pillar = m_Pillars[index];
	pillar.TopPosition.x = offset;
	pillar.BottomPosition.x = offset;
	pillar.TopPosition.z = 1.5f;
	pillar.BottomPosition.z = 1.5f;

	float center = Random::Float() * 35.0f - 17.5f;
	float gap = 2.0f + Random::Float() * 5.0f;

	pillar.TopPosition.y = 8.f - ((10.0f - center) * 0.2f) + gap * 0.5f;
	pillar.BottomPosition.y = -8.f - ((-10.0f - center) * 0.2f) - gap * 0.5f;
}
