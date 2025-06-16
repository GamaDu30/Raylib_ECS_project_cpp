#include "global/definitions.hpp"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "global/gameObject.hpp"
#include "components/Renderer/CircleRenderer.hpp"
#include "components/Renderer/RectRenderer.hpp"
#include "components/TransformComponent.hpp"
#include "components/CameraComponent.hpp"
#include "global/Scene.hpp"
#include "components/Collider/CircleCollider.hpp"
#include "components/Collider/RectCollider.hpp"

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

	GameObject *rect1 = scene->CreateGameObject();
	rect1->GetTransform()->GetPos().x = -150;
	rect1->AddComponent<RectRenderer>(raylib::Vector2(100, 100), raylib::Vector2(300, 0));
	rect1->AddComponent<RectCollider>(raylib::Vector2(100, 100), raylib::Vector2(300, 0));

	GameObject *rect2 = scene->CreateGameObject();
	rect2->GetTransform()->GetPos().x = 150;
	rect2->AddComponent<RectRenderer>(raylib::Vector2(100, 100));
	rect2->AddComponent<RectCollider>(raylib::Vector2(100, 100));

	GameObject *center = scene->CreateGameObject();

	// const char *cwd = GetWorkingDirectory();
	// TraceLog(LOG_INFO, "Current working directory: %s", cwd);

	// game loop
	while (!WindowShouldClose())
	{
		// Update
		ColliderComponent::CheckCollisions();

		if (IsMouseButtonDown(0))
		{
			rect1->GetTransform()->GetPos().x = scene->GetMainCam()->GetMousePos().x;
			rect1->GetTransform()->GetPos().y = scene->GetMainCam()->GetMousePos().y;
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
// Make InputManager
// Make more collision component
// Opti collision by doing a AABB of each collider before doing a precise check