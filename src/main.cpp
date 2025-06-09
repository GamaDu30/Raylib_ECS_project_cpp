#include "global/definitions.hpp"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "global/gameObject.hpp"
#include "components/CircleRenderer.hpp"
#include "components/TransformComponent.hpp"
#include "components/CameraComponent.hpp"
#include "global/Scene.hpp"

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
	cam->GetTransform()->GetPos() = raylib::Vector3(100, 100);
	cam->AddComponent<CameraComponent>();

	GameObject *ball = scene->CreateGameObject();
	ball->GetTransform()->GetPos() = raylib::Vector3(0, 0);
	ball->AddComponent<CircleRenderer>(raylib::Vector2(0, 0), 50, WHITE);

	GameObject *center = scene->CreateGameObject();
	center->GetTransform()->GetPos() = raylib::Vector3(0, 0, 1);
	center->AddComponent<CircleRenderer>(raylib::Vector2(0, 0), 5, raylib::Color(255, 0, 0, 100));

	// const char *cwd = GetWorkingDirectory();
	// TraceLog(LOG_INFO, "Current working directory: %s", cwd);

	// game loop
	while (!WindowShouldClose())
	{
		// Update
		float t = GetTime();
		cam->GetTransform()->GetPos() = raylib::Vector3(cos(t) * 50, sin(t) * 50);
		center->GetTransform()->GetPos() = cam->GetTransform()->GetPos();

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