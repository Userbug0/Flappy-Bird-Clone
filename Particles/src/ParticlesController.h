#pragma once

#include <Athena.h>

using namespace Athena;


struct ParticleDesc
{
	Vector2 Position;
	Vector2 Velocity, VelocityVariation;
	Color ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 0.5f;
};


class ParticlesController
{
public:
	ParticlesController();

	void OnImGuiRender();

	inline ParticleDesc& GetParticleDesc() { return m_ParticleDesc; }
	inline const ParticleDesc& GetParticleDesc() const { return m_ParticleDesc; }

private:
	ParticleDesc m_ParticleDesc;
};
