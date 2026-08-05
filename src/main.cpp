#include "global/definitions.hpp"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "components/Renderer/UI/CanvasComponent.hpp"
#include "global/gameObject.hpp"
#include "global/Scene.hpp"
#include "global/Inputs.hpp"

#include "components/CameraComponent.hpp"

#include "gameSample/Bird.hpp"
#include "gameSample/PipeManager.hpp"
#include "components/Collider/CircleCollider.hpp"
#include "components/Collider/RectCollider.hpp"
#include "components/Renderer/UI/ButtonComponent.hpp"

void Init()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
	SetTraceLogLevel(LOG_DEBUG);
	// Create the window and OpenGL context
	InitWindow(1280, 720, "ECS");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// const char *cwd = GetWorkingDirectory();
	// TraceLog(LOG_INFO, "Current working directory: %s", cwd);

	Inputs::Init();
}

int main()
{
	Init();

	Scene *scene = new Scene("Game");

	Bird *bird = scene->CreateGameObject<Bird>("Player");
	bird->AddComponent<CameraComponent>();
	PipeManager *pipe = scene->CreateGameObject<PipeManager>("PipeManager");

	// game loop
	while (!shouldExit)
	{
		Scene::GetScene()->Update();
		Scene::GetScene()->Render();
	}

	CloseWindow();
	return 0;
}

// TODO:
// Opti collision by doing a AABB of each collider before doing a precise check