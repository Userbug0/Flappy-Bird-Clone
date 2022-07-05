#include <Athena.h>
#include <Athena/Core/EntryPoint.h>

#include "ParticlesLayer.h"


class Particles : public Application
{
public:
	Particles()
	{
		PushLayer(new ParticlesLayer());
	}

	~Particles()
	{

	}
};


Athena::Application* Athena::CreateApplication()
{
	return new Particles();
}
