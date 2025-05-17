#include "definitions.hpp"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "components/TransformComponent.hpp"
#include "components/RenderComponent.hpp"
#include "gameObject.hpp"

main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTraceLogLevel(LOG_DEBUG);

	// Create the window and OpenGL context
	InitWindow(1280, 720, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	GameObject *base = new GameObject("Player");
	base->AddComponent<RenderComponent>();
	base->GetTransform()->GetPos() = raylib::Vector2(200, 200);

	GameObject *child = new GameObject("Orbit");
	child->AddComponent<RenderComponent>();
	child->GetTransform()->GetPos() = raylib::Vector2(100, 0);

	base->GetTransform()->AddChild(child->GetTransform());

	// game loop
	while (!WindowShouldClose()) // run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// Update
		child->GetTransform()->GetPos() = raylib::Vector2(cos(GetTime()) * 100, sin(GetTime()) * 100);

		// IMPORTANT: Keep at the end of the update
		GameObject::UpdateAll();

		// Draw
		BeginDrawing();
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		GameObject::RenderAll();

		DrawLineEx(raylib::Vector2(50, 600), raylib::Vector2(500, 600), 10, RED);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
