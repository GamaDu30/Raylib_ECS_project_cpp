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
#include "components/Renderer/UI/ImageRenderer.hpp"

#include "gameSample/Bird.hpp"
#include "gameSample/PipeManager.hpp"

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

		Scene::GetScene()->FindGameObject("UI")->GetComponent<RectTransformComponent>()->DebugRender();
	}

	EndDrawing();
}

int main()
{
	Init();

	Scene *scene = new Scene("Game");

	//  GameObject *cam = scene->CreateGameObject("Cam");
	//  cam->AddComponent<CameraComponent>(raylib::Color(0, 93, 191, 255));

	// Bird *bird = scene->CreateGameObject<Bird>("Player");
	// PipeManager *pipe = scene->CreateGameObject<PipeManager>("PipeManager");

	GameObject *ui = scene->CreateGameObject("UI");
	ui->AddComponent<CanvasComponent>();

	GameObject *rect1 = scene->CreateGameObject("Rect");
	rect1->GetTransform()->SetParent(ui->GetTransform());
	rect1->GetComponent<RectTransformComponent>()->GetAnchorMin() = raylib::Vector2(0.f, 0.f);
	rect1->GetComponent<RectTransformComponent>()->GetAnchorMax() = raylib::Vector2(0.f, 0.5f);
	rect1->GetComponent<RectTransformComponent>()->SetFixed(true, false, raylib::Vector2(200, 100), raylib::Vector2(0.5f, 0.25f));
	rect1->AddComponent<ImageRenderer>("bird.png");

	GameObject *rect2 = scene->CreateGameObject("Rect");
	rect2->GetTransform()->SetParent(ui->GetTransform());
	rect2->GetComponent<RectTransformComponent>()->GetAnchorMin() = raylib::Vector2(0.5f, 0.5f);
	rect2->GetComponent<RectTransformComponent>()->GetAnchorMax() = raylib::Vector2(1.0f, 1.0f);
	rect2->AddComponent<ImageRenderer>("bird.png");

	// game loop
	while (!shouldExit)
	{
		Update();
		Render();

		SetWindowSize(SCREEN_W * (sinf(GetTime()) * 0.25f + 1.f), SCREEN_H * (sinf(GetTime() * 0.75f) * 0.25f + 1.f));
	}

	CloseWindow();
	return 0;
}

// TODO:
// Separate debug render into its own class (ex: GameObject gizmo / visible collider)
// Opti collision by doing a AABB of each collider before doing a precise check

// UI:
// Make RectTransformComponent
// Make CanvasComponent
// Make UI Components