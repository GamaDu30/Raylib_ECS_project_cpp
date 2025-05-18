#include "definitions.hpp"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "gameObject.hpp"
#include "components/TransformComponent.hpp"
#include "components/RenderComponent.hpp"
#include "components/CircleRenderer.hpp"

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
	base->AddComponent<CircleRenderer>(raylib::Vector2(0, 0), 10, WHITE);
	base->GetTransform()->GetPos() = raylib::Vector2(50, SCREEN_H * 0.5f);

	GameObject *parent = base;
	GameObject *child;

	for (int i = 0; i < 20; i++)
	{
		child = new GameObject();
		child->GetTransform()->GetPos() = raylib::Vector2(50, 0);
		child->AddComponent<CircleRenderer>(raylib::Vector2(), 20, raylib::Color(raylib::Vector3((360 / 20) * i, 1.f, 1.f)));

		parent->GetTransform()->AddChild(child->GetTransform());
		parent = child;
	}

	// game loop
	while (!WindowShouldClose()) // run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// Update
		TransformComponent *curTransform = base->GetTransform()->GetChild(0);
		int id = 1;

		while (curTransform != nullptr)
		{
			curTransform->GetPos().y = sin(GetTime() * id * 0.5f) * id * 2;
			curTransform = curTransform->GetChild(0);
			id++;
		}

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
