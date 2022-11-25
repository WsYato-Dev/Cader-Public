#include <Cader/Core/Engine.h>
#include <Cader/Core/Project.h>
#include <Cader/Core/PersistentSettings.h>
#include <Cader/Core/StartupSettings.h>
#include <Cader/Core/Time.h>
#include <Cader/ECS/Components.h>
#include <Cader/ECS/Entity.h>
#include <Cader/ECS/Scene.h>
#include <Cader/Window/Input.h>

#include <glm/vec2.hpp>

using namespace CDR;

constexpr u32 QuadsCountSquared{20};
constexpr glm::vec2 QuadSize{1.9f / QuadsCountSquared};
constexpr float QuadStep{2.0f / QuadsCountSquared};
constexpr float QuadsStartPoint{-1.0f + QuadStep / 2.0f};
constexpr Milliseconds QuadsRandomColorInterval{100};

Timer quadsRandomColorTimer;

void Project::Setup(PersistentSettings* pPersistentSettings, StartupSettings* pStartupSettings)
{
	pPersistentSettings->projectTitle = "Playground";
}

void Project::Init(Scene& pScene)
{
	for(u32 y = 0; y < QuadsCountSquared; y++)
	{
		for(u32 x = 0; x < QuadsCountSquared; x++)
		{
			Entity entity = pScene.NewEntity();

			pScene.AddComponent<ColorComponent>(entity).color = Color::Random();
			pScene.AddComponent<Position2DComponent>(entity).position = glm::vec2(QuadsStartPoint + x * QuadStep, QuadsStartPoint + y * QuadStep);
			pScene.AddComponent<Size2DComponent>(entity).size = QuadSize;
		}
	}

	quadsRandomColorTimer.Start(QuadsRandomColorInterval);
}

void Project::Update(Scene& pScene)
{
	if(Input::GetKeyDown(EKeyCode::Escape))
		Engine::Get().Quit();

	if(quadsRandomColorTimer.Check())
	{
		const auto& view = pScene.GetAllEntitiesWith<ColorComponent>();

		for(entt::entity entity : view)
			view.get<ColorComponent>(entity).color = Color::Random();

		quadsRandomColorTimer.Start(QuadsRandomColorInterval);
	}
}

void Project::Cleanup(Scene& pScene)
{}