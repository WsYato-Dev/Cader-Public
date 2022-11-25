#include "Cader/ECS/Scene.h"

namespace CDR {

	Scene::Scene(const Text pSceneName, const u8 pSceneIndex)
		: sceneName{pSceneName}
		, sceneIndex{pSceneIndex}
	{}

	Entity Scene::NewEntity()
	{
		return Entity(mRegistry.create());
	}

	void Scene::DestroyEntity(const Entity pEntity)
	{
		mRegistry.destroy(pEntity);
	}

}