#include <Athena.h>
#include <Athena/Core/EntryPoint.h>

#include "GameLayer.h"


class FlappyBird : public Application
{
public:
	FlappyBird()
	{
		PushLayer(new GameLayer());
	}

	~FlappyBird()
	{

	}
};


Athena::Application* Athena::CreateApplication()
{
	return new FlappyBird();
}
