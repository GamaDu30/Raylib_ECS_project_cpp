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
#include "components/Renderer/UI/TextComponent.hpp"
#include "components/RigidBodyComponent.hpp"
#include "components/Renderer/SpriteRenderer.hpp"
#include "components/Collider/RectCollider.hpp"

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

	// GameObject *camera = scene->CreateGameObject<GameObject>("Camera");
	// camera->AddComponent<CameraComponent>()->SetBgColor(raylib::Color(135, 206, 235));
	// // camera->GetComponent<CameraComponent>()->SetTarget(bird->GetTransform());

	// Bird *bird = scene->CreateGameObject<Bird>("Player");
	// PipeManager *pipe = scene->CreateGameObject<PipeManager>("PipeManager");

	// UI *ui = scene->CreateGameObject<UI>("UI");

	GameObject *object1 = scene->CreateGameObject();
	object1->GetTransform()->GetPos() = raylib::Vector3(SCREEN_W * 0.25f, SCREEN_H * 0.4f, 0.f);
	object1->AddComponent<RectCollider>(raylib::Vector2(100, 100));
	object1->AddComponent<RigidBodyComponent>();
	object1->GetComponent<TransformComponent>()->GetRotation() = PI * 0.2f;

	GameObject *object2 = scene->CreateGameObject();
	object2->GetTransform()->GetPos() = raylib::Vector3(SCREEN_W * 0.5f, SCREEN_H * 0.75f, 0.f);
	object2->AddComponent<RectCollider>(raylib::Vector2(750, 100));
	object2->GetComponent<TransformComponent>()->GetRotation() = PI * 0.1f;

	// game loop
	Scene::GetScene()
		->Start();

	float t = 0.01f;
	bool pause = false;

	while (!shouldExit)
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			pause = !pause;
		}

		t += GetFrameTime() * (pause ? 0.f : 1.f);

		if (t >= 0.01f)
		{
			Scene::GetScene()->Update();
			t = 0;
		}

		Scene::GetScene()->Render();
	}

	CloseWindow();
	return 0;
}

// TODO:
// Physics system x)

// Make generalized asset manager like in Sprite for every type of asset (texture, audio, font, etc...)
// ColliderComponent: Optimize collision by doing a AABB of each collider before doing a precise check
// Scene: Load / Unload and persistent GameObjects between scenes
// TransformComponent pos/scale/rotation: if there are performance issues -> change with getter/setter

// Prefab System
// Make visual editor