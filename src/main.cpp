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
#include "components/Renderer/UI/ImageComponent.hpp"

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
	ClearBackground(BLACK);

	Scene::GetScene()->Render();

	if (DRAW_DEBUG)
	{
		ColliderComponent::DrawAllDebug();

		// TODO: Change method to get the CanvasComp
		// Scene::GetScene()->FindGameObject("UI")->GetComponent<RectTransformComponent>()->DebugRender();
	}

	EndDrawing();
}

int main()
{
	Init();

	Scene *scene = new Scene("Game");

	Bird *bird = scene->CreateGameObject<Bird>("Player");
	bird->AddComponent<CameraComponent>();
	PipeManager *pipe = scene->CreateGameObject<PipeManager>("PipeManager");

	// GameObject *ui = scene->CreateGameObject("UI");
	// ui->AddComponent<CanvasComponent>();

	// GameObject *rect2 = scene->CreateGameObject("Rect");
	// rect2->GetTransform()->SetParent(ui->GetTransform());
	// rect2->GetComponent<RectTransformComponent>()->GetAnchorMin() = raylib::Vector2(0.25f, 0.5f);
	// rect2->GetComponent<RectTransformComponent>()->GetAnchorMax() = raylib::Vector2(0.75f, 0.5f);
	// rect2->GetComponent<RectTransformComponent>()->SetSize(raylib::Vector2(1000.f, 200.f));
	// ImageComponent *imgRenderer = rect2->AddComponent<ImageComponent>("testSprite.png");
	// imgRenderer->SetImageType(ImageType::Filled);
	// imgRenderer->SetImageFillData({.method = FillMethod::Horizontal, .inverseFillDirection = true});
	// imgRenderer->SetColor(raylib::Color(127, 255, 255, 255));

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
// Separate debug render into its own class (ex: GameObject gizmo / visible collider)
// Opti collision by doing a AABB of each collider before doing a precise check