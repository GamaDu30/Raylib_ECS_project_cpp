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
#include "global/Inputs.hpp"
#include <charconv>
#include "global/Sprites.hpp"
#include "components/Renderer/UI/CanvasComponent.hpp"

#include "gameSample/Bird.hpp"
#include "gameSample/PipeManager.hpp"

void Init()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTraceLogLevel(LOG_DEBUG);
	// Create the window and OpenGL context
	InitWindow(1280, 720, "ECS");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// const char *cwd = GetWorkingDirectory();
	// TraceLog(LOG_INFO, "Current working directory: %s", cwd);

	Inputs::Init();
}

void Update()
{
	// Update
	ColliderComponent::CheckCollisions();
	Inputs::Update();

	Scene::GetScene()->Update();
}

void Render()
{
	// Draw
	BeginDrawing();

	Scene::GetScene()->Render();

	if (DRAW_DEBUG)
	{
		ColliderComponent::DrawAllDebug();
	}

	EndDrawing();
}

main()
{
	Init();

	Scene *scene = new Scene("Game");

	GameObject *cam = scene->CreateGameObject("Cam");
	cam->AddComponent<CameraComponent>(raylib::Color(0, 93, 191, 255));

	Bird *bird = scene->CreateGameObject<Bird>("Player");
	PipeManager *pipe = scene->CreateGameObject<PipeManager>("PipeManager");


	// game loop
	while (!shouldExit)
	{
		Update();
		Render();
	}

	CloseWindow();
	return 0;
}

// TODO:
// Separate debug render into its own class
// Find a way to code a clean getter/setter for property of TransformComponent
// Opti collision by doing a AABB of each collider before doing a precise check

// UI:
// Make RectTransformComponent
// Make CanvasComponent
// Make UI Components