#pragma once

#include "Athena/Core/Time.h"
#include "Athena/Events/Event.h"
#include "Athena/Events/ApplicationEvent.h"
#include "Athena/Events/MouseEvent.h"

#include "Athena/Renderer/OrthographicCamera.h"


namespace Athena
{
	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Left - Right; }
		float GetHeight() { return Top - Bottom; }
	};

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = true);

		void OnUpdate(Time frameTime);
		void OnEvent(Event& event);

		inline OrthographicCamera& GetCamera() { return m_Camera; };
		inline const OrthographicCamera& GetCamera() const { return m_Camera; };

		inline void SetZoomLevel(float level) { m_ZoomLevel = level; }
		inline float GetZoomLevel() const { return m_ZoomLevel; }

		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; };
	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizedEvent& event);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.f;
		float m_Rotation;

		OrthographicCameraBounds m_Bounds;
		OrthographicCamera m_Camera;

		Vector3 m_CameraPosition = { 0.f, 0.f, 0.f };
		float m_CameraRotation = 0.f;

		float m_CameraSpeed = 3.f;
		float m_CameraRotationSpeed = 1.f;
	};
}
