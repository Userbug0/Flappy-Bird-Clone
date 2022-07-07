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
	float life = particle.LifeRemaning / particle.LifeTime;

	Color color = Lerp(particle.ColorEnd, particle.ColorBegin, life);
	float size = Lerp(particle.SizeEnd, particle.SizeBegin, life);

	Renderer2D::DrawQuad(particle.Position, { size, size }, color);
}

void ParticlesGenerator::Emit(const ParticleDesc& desc)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;

	particle.ColorBegin = desc.ColorBegin;
	particle.ColorEnd = desc.ColorEnd;

	particle.SizeBegin = desc.SizeBegin + desc.SizeVariation * (Random::Float() - 0.5f);
	particle.SizeEnd = desc.SizeEnd;	

	particle.Position = m_EmitterPosition;
	particle.Velocity = desc.Velocity;
	particle.Velocity.x += desc.VelocityVariation.x * (Random::Float() - 0.5f);
	particle.Velocity.y += desc.VelocityVariation.y * (Random::Float() - 0.5f);

	particle.LifeTime = desc.LifeTime;
	particle.LifeRemaning = desc.LifeTime;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}

void ParticlesGenerator::GetEmitterPosition(float seconds)
{
	m_ElapsedTime += seconds * 0.3f;
	m_EmitterPosition = Vector2(
		sin(m_ElapsedTime * 5.f) * 1.5f - 0.75f, 
		-0.5f + sin(m_ElapsedTime * 4) * 1.5f);
}
