#include "global/definitions.hpp"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "components/Renderer/UI/CanvasComponent.hpp"
#include "global/gameObject.hpp"
#include "global/Scene.hpp"
#include "global/Inputs.hpp"

#include "components/CameraComponent.hpp"
#include "gameSample/Bird.hpp"
#include "gameSample/PipeManager.hpp"
#include "gameSample/UI.hpp"
#include "gameSample/GameManager.hpp"

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

	GameObject *camera = scene->CreateGameObject<GameObject>("Camera");
	camera->AddComponent<CameraComponent>()->SetBgColor(raylib::Color(135, 206, 235));

	Bird *bird = scene->CreateGameObject<Bird>("Player");
	PipeManager *pipe = scene->CreateGameObject<PipeManager>("PipeManager");

	camera->GetComponent<CameraComponent>()->SetTarget(bird->GetTransform());

	UI *ui = scene->CreateGameObject<UI>("UI");

	// game loop
	Scene::GetScene()->Start();

	while (!shouldExit)
	{
		Scene::GetScene()->Update();
		Scene::GetScene()->Render();
	}

	CloseWindow();
	return 0;
}

// TODO:
// CameraComponent: Finish target system

// GameObject: refacto Update like Component to block update when not active (OnUpdate)
//  Make generalized asset manager like in Sprite for every type of asset (texture, audio, font, etc...)
//  ColliderComponent: Optimize collision by doing a AABB of each collider before doing a precise check
//  GameObject: FixedUpdate() for physics
//  Scene: Load / Unload and persistent GameObjects between scenes
//  TextComponent: Manage text overflow with height
//  TransformComponent pos/scale/rotation: if there are performance issues -> change with getter/setter

// Prefab System
// Make visual editor