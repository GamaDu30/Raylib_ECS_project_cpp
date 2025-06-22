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

class Player : public GameObject
{
	bool isColliding = false;

public:
	Player(std::string name = "") : GameObject(name) {}

	~Player() {}

	void Start() override
	{
		GameObject::Start();

		this->AddComponent<RectRenderer>(raylib::Vector2(100, 100));
		this->AddComponent<RectCollider>(raylib::Vector2(100, 100));
	}

	void Update() override
	{
		GameObject::Update();

		GetTransform()->GetPos().x = CameraComponent::GetMainCam()->GetMousePos().x;
		GetTransform()->GetPos().y = CameraComponent::GetMainCam()->GetMousePos().y;
		GetTransform()->GetRotation() += 0.5f * GetFrameTime();

		if (isColliding)
		{
			GetTransform()->GetScale().x = 2 + cos(GetTime());
			GetTransform()->GetScale().y = 2 + sin(GetTime() * 2);
		}
	}

	void OnCollisionEnter(ColliderComponent *collider) override
	{
		GameObject::OnCollisionEnter(collider);

		isColliding = true;
	}

	void OnCollisionExit(ColliderComponent *collider) override
	{
		GameObject::OnCollisionExit(collider);

		isColliding = false;
	}
};

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

main()
{
	Init();

	Scene *scene = new Scene("Game");

	GameObject *cam = scene->CreateGameObject();
	cam->GetTransform()->GetPos() = raylib::Vector3(0, 0);
	cam->AddComponent<CameraComponent>();

	Player *player = scene->CreateGameObject<Player>("Player");

	GameObject *shape = scene->CreateGameObject("Shape");
	shape->AddComponent<CircleCollider>(50.f);
	shape->AddComponent<CircleRenderer>(50.f);
	shape->GetTransform()->GetPos().x = -SCREEN_W * 0.25f;

	// game loop
	while (!WindowShouldClose())
	{
		// Update
		ColliderComponent::CheckCollisions();
		Inputs::Update();

		// IMPORTANT: Keep at the end of the update
		scene->Update();

		// Draw
		BeginDrawing();

		scene->Render();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

// TODO:
// Opti collision by doing a AABB of each collider before doing a precise check