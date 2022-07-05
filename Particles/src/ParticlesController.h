#pragma once

#include <Athena.h>

using namespace Athena;


struct ParticleDesc
{
	Vector2 Velocity, VelocityVariation;
	Color ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.f;
};


class ParticlesController
{
public:
	ParticlesController();

	void OnImGuiRender();

	inline const ParticleDesc& GetParticleDesc() const { return m_ParticleDesc; }

private:
	ParticleDesc m_ParticleDesc;
};
