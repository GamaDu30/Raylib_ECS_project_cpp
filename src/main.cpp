#include "global/definitions.hpp"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "global/gameObject.hpp"
#include "components/Renderer/CircleRenderer.hpp"
#include "components/TransformComponent.hpp"
#include "components/CameraComponent.hpp"
#include "global/Scene.hpp"
#include "components/Collider/CircleCollider.hpp"

main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTraceLogLevel(LOG_DEBUG);
	// Create the window and OpenGL context
	InitWindow(1280, 720, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	Scene *scene = new Scene("Game");

	GameObject *cam = scene->CreateGameObject();
	cam->GetTransform()->GetPos() = raylib::Vector3(0, 0);
	cam->AddComponent<CameraComponent>();

	GameObject *circle1 = scene->CreateGameObject();
	circle1->GetTransform()->GetPos().x = -150;
	circle1->AddComponent<CircleRenderer>(raylib::Vector2(), 100);
	circle1->AddComponent<CircleCollider>(raylib::Vector2(), 100);

	GameObject *circle2 = scene->CreateGameObject();
	circle2->GetTransform()->GetPos().x = 150;
	circle2->AddComponent<CircleRenderer>(raylib::Vector2(), 100);
	circle2->AddComponent<CircleCollider>(raylib::Vector2(), 100);

	// const char *cwd = GetWorkingDirectory();
	// TraceLog(LOG_INFO, "Current working directory: %s", cwd);

	// game loop
	while (!WindowShouldClose())
	{
		// Update
		ColliderComponent::CheckCollisions();

		if (IsMouseButtonDown(0))
		{
			circle1->GetTransform()->GetPos().x = scene->GetMainCam()->GetMousePos().x;
			circle1->GetTransform()->GetPos().y = scene->GetMainCam()->GetMousePos().y;
		}

		// IMPORTANT: Keep at the end of the update
		scene->Update();

		// Draw
		BeginDrawing();

		scene->Render();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

// TODO:
// Make collision component