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

static bool PointInTri(const Vector2& p, const Vector2& p0, const Vector2& p1, const Vector2& p2)
{
	float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
	float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

	if ((s < 0) != (t < 0))
		return false;

	float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

	return A < 0 ?
		(s <= 0 && s + t >= A) :
		(s >= 0 && s + t <= A);
}


void Level::Init()
{
	m_Player.Init();
	m_PillarTexture = Texture2D::Create("assets/textures/Triangle.png");

	m_Pillars.resize(5);
	for (int i = 0; i < 5; i++)
		CreatePillar(i, i * 10.0f);
}

void Level::Reset()
{
	m_Player.Reset();
	m_GameOver = false;

	m_PillarTarget = 30.0f;
	m_PillarIndex = 0;
	for (int i = 0; i < 5; i++)
		CreatePillar(i, i * 10.0f);
}

void Level::OnUpdate(Time frameTime)
{
	m_Player.OnUpdate(frameTime);

	if (CollisionTest() == true)
	{
		GameOver();
		return;
	}

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

bool Level::CollisionTest()
{
	if (std::abs(m_Player.GetPosition().y) > 8.5f)
		return true;

	Vector4 playerVertices[4] = {
		{ -0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f, -0.25f, 0.0f, 1.0f },
		{  0.5f,  0.25f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.0f, 1.0f }
	};

	const auto& pos = m_Player.GetPosition();
	Vector4 playerTransformedVerts[4];
	for (int i = 0; i < 4; i++)
	{
		playerTransformedVerts[i] = playerVertices[i] * 
			Scale({ 0.87f, 1.3f, 1 }) * 
			Rotate(DegreeToRad(m_Player.GetRotation()), { 0.0f, 0.0f, 1.0f }) *
			Translate({ pos.x, pos.y, 0.0f });
	}


	// To match Triangle.png (each corner is 10% from the texture edge)
	Vector4 pillarVertices[3] = {
		{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
	};

	for (auto& p : m_Pillars)
	{
		Vector2 tri[3];

		// Top pillars
		for (int i = 0; i < 3; i++)
		{
			tri[i] = pillarVertices[i] * 
				Scale({ p.TopScale.x, p.TopScale.y, 1.0f }) *
				Rotate(DegreeToRad(180), { 0.0f, 0.0f, 1.0f }) *
				Translate({ p.TopPosition.x, p.TopPosition.y, 0.0f });
		}

		for (auto& vert : playerTransformedVerts)
		{
			if (PointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
				return true;
		}

		// Bottom pillars
		for (int i = 0; i < 3; i++)
		{
			tri[i] = pillarVertices[i] * 
				Scale({ p.BottomScale.x, p.BottomScale.y, 1.0f } ) * 
				Translate({ p.BottomPosition.x, p.BottomPosition.y, 0.0f });
		}

		for (auto& vert : playerTransformedVerts)
		{
			if (PointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
				return true;
		}
	}
	return false;
}

void Level::GameOver()
{
	m_GameOver = true;
}
