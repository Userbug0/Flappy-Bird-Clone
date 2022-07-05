#include "ParticlesGenerator.h"


ParticlesGenerator::ParticlesGenerator()
	: m_EmitterPosition(0.f), m_ElapsedTime(0)
{
	m_ParticlePool.resize(m_PoolIndex + 1);
}

void ParticlesGenerator::OnUpdate(Time frameTime)
{
	float seconds = frameTime.AsSeconds();
	GetEmitterPosition(seconds);

	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;
		
		if (particle.LifeRemaning <= 0.f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaning -= seconds;
		particle.Position += particle.Velocity * seconds;

		RenderParticle(particle);
	}
}

void ParticlesGenerator::RenderParticle(const Particle& particle)
{
	Renderer2D::DrawQuad(m_EmitterPosition, { 1.f, 1.f }, particle.ColorBegin);
}

void ParticlesGenerator::Emit(const ParticleDesc& desc)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];

	particle.Active = true;
	particle.ColorBegin = desc.ColorBegin;

	particle.LifeTime = desc.LifeTime;
	particle.LifeRemaning = desc.LifeTime;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}

void ParticlesGenerator::GetEmitterPosition(float seconds)
{
	m_ElapsedTime += seconds * 0.1f;
	m_EmitterPosition = Vector2(
		sin(m_ElapsedTime * 5.f) * 1.5f - 0.75f, 
		-0.5f + sin(m_ElapsedTime * 4) * 1.5);
}
