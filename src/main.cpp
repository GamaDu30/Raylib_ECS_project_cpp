#include "global/definitions.hpp"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "global/gameObject.hpp"
#include "components/TransformComponent.hpp"
#include "components/RenderComponent.hpp"
#include "components/CircleRenderer.hpp"
#include "components/SpriteRenderer.hpp"
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

	GameObject *circle = new GameObject();
	circle->AddComponent<CircleRenderer>(raylib::Vector2(50, 50), 25, WHITE);

	Scene *scene = new Scene("Game");
	scene->AddGameObject(circle);

	// const char *cwd = GetWorkingDirectory();
	// TraceLog(LOG_INFO, "Current working directory: %s", cwd);

	// game loop
	while (!WindowShouldClose())
	{
		// Update

		// IMPORTANT: Keep at the end of the update
		scene->Update();

		// Draw
		BeginDrawing();
		ClearBackground(BLACK);

		scene->Render();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

// TODO:
// Make collision component
// Manage scene
// Make camera