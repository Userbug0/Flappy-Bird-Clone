#include "atnpch.h"
#include "OrthographicCameraController.h"

#include "Athena/Core/Input.h"


namespace Athena
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Rotation(rotation), 
		m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }), 
		m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top)
	{

	}

	void OrthographicCameraController::OnUpdate(Time frameTime)
	{
		ATN_PROFILE_FUNCTION();

		float seconds = frameTime.AsSeconds();

		if (Input::IsKeyPressed(Key::A))
			m_CameraPosition.x -= m_CameraSpeed * seconds;
		else if (Input::IsKeyPressed(Key::D))
			m_CameraPosition.x += m_CameraSpeed * seconds;
		else if (Input::IsKeyPressed(Key::W))
			m_CameraPosition.y += m_CameraSpeed * seconds;
		else if (Input::IsKeyPressed(Key::S))
			m_CameraPosition.y -= m_CameraSpeed * seconds;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				m_CameraRotation += m_CameraRotationSpeed * seconds;
			else if (Input::IsKeyPressed(Key::E))
				m_CameraRotation -= m_CameraRotationSpeed * seconds;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		ATN_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(ATN_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizedEvent>(ATN_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}
	
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		ATN_PROFILE_FUNCTION();

		m_ZoomLevel -= event.GetYOffset() * 0.4f;
		m_ZoomLevel = max(m_ZoomLevel, 0.2f);

		m_Bounds = { -m_ZoomLevel * m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);

		m_CameraSpeed = m_ZoomLevel * 1.5f;
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizedEvent& event)
	{
		ATN_PROFILE_FUNCTION();

		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		m_Bounds = { -m_ZoomLevel * m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);

		return false;
	}
}
