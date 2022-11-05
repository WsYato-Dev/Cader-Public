#include <Cader/Core/Engine.h>
#include <Cader/Core/Project.h>
#include <Cader/Core/ProjectSettings.h>
#include <Cader/Core/StartupSettings.h>
#include <Cader/Window/Input.h>

using namespace CDR;

void Project::Setup(ProjectSettings& pProjectSettings, StartupSettings& pStartupSettings)
{
	pProjectSettings.title = "Playground";
}

void Project::Init()
{}

void Project::Update()
{
	if(Input::GetKeyDown(EKeyCode::Escape))
		Engine::Get().Quit();
}

void Project::PreCleanup()
{}

void Project::Cleanup()
{}