#include "definitions.hpp"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "gameObject.hpp"
#include "components/TransformComponent.hpp"
#include "components/RenderComponent.hpp"
#include "components/CircleRenderer.hpp"
#include "components/SpriteRenderer.hpp"

main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTraceLogLevel(LOG_DEBUG);

	// Create the window and OpenGL context
	InitWindow(1280, 720, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	GameObject *bunny = new GameObject("RABBIT");
	bunny->AddComponent<SpriteRenderer>("wabbit_alpha.png", Anchor::Center);
	bunny->GetTransform()->GetPos() = raylib::Vector3(SCREEN_W * 0.5f, SCREEN_H * 0.5f);
	bunny->GetTransform()->GetScale() = raylib::Vector2(10, 10);

	GameObject *centerPoint = new GameObject("Point Central");
	centerPoint->AddComponent<CircleRenderer>(raylib::Vector2(), 5, WHITE);
	centerPoint->GetTransform()->GetPos() = raylib::Vector3(SCREEN_W * 0.5f, SCREEN_H * 0.5f);

	// game loop
	while (!WindowShouldClose()) // run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// Update

		// IMPORTANT: Keep at the end of the update
		GameObject::UpdateAll();

		// Draw
		BeginDrawing();
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		GameObject::RenderAll();

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

// TODO:
// Make collision component
// Manage scene