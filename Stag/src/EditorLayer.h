#pragma once
#include "Beetle.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"
#include "Beetle/Renderer/EditorCamera.h"


namespace Beetle
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(TimeStamp ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& event) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveScene();
		void SaveSceneAs();
		
		void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);
		void OnScreenPlay();
		void OnScreenStop();

		void OnDuplicateEntity();
		void UI_Toolbar();

	private:
		OrthographicCameraController m_CameraController;

		//temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_flatColorShader;
		Ref<FrameBuffer> m_FrameBuffer;

		Entity m_HoveredEntity;

		Ref<Scene> m_ActiveScene;
		Ref<Scene> m_EditorScene;
		std::filesystem::path m_EditorScenePath;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

		EditorCamera m_EditorCamera;

		Ref<Texture2D> m_CheckerBoard;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.f, 0.f };

		glm::vec2 m_ViewportBounds[2];

		glm::vec4 m_SquareColor = { .2f, .3f, .8f, 1.f };

		int m_GizmoType = -1;

		//Scene State
		enum class SceneState
		{
			Edit = 0,
			Play = 1,
			Stop = 2
		};
		SceneState m_SceneState = SceneState::Edit;

		//panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;

		Ref<Texture2D> m_IconPlay, m_IconStop;
	};
}
