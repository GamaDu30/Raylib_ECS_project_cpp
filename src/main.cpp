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
public:
	Player(std::string name = "") {}
	~Player() {}

	float velocity = 0.f;

	void Update() override
	{
		GameObject::Update();
		GetTransform()->GetPos().y += velocity;
		velocity += 0.5f * GetFrameTime();
		TraceLog(LOG_DEBUG, "PLAYER UPDATE %f", GetTransform()->GetPos().y);
	}
	void OnJump() { velocity -= 1.f; }
};

main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTraceLogLevel(LOG_DEBUG);
	// Create the window and OpenGL context
	InitWindow(1280, 720, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	Scene *scene = new Scene("Game");

	GameObject *cam = scene->CreateGameObject();
	cam->GetTransform()->GetPos() = raylib::Vector3(0, 0);
	cam->AddComponent<CameraComponent>();

	GameObject *center = scene->CreateGameObject();

	Inputs::Init();

	Player *player = scene->CreateGameObject<Player>();
	player->AddComponent<RectRenderer>(raylib::Vector2(100, 100));
	Inputs::RegisterInput(KeyboardKey::KEY_SPACE, KeyState::DOWN, player, &Player::OnJump);

	// const char *cwd = GetWorkingDirectory();
	// TraceLog(LOG_INFO, "Current working directory: %s", cwd);

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
// Make more collision component
// Opti collision by doing a AABB of each collider before doing a precise check
// Fix update override not working on child of gameObject