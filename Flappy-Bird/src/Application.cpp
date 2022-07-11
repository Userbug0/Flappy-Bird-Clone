#include <Athena.h>
#include <Athena/Core/EntryPoint.h>

#include "GameLayer.h"


class Particles : public Application
{
public:
	Particles()
	{
		PushLayer(new GameLayer());
	}

	~Particles()
	{

	}
};


Athena::Application* Athena::CreateApplication()
{
	return new Particles();
}
