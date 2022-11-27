#include "Cader/ECS/Scene.h"

namespace CDR {

	Scene::Scene(Text pSceneName, u8 pSceneIndex)
		: sceneName{pSceneName}
		, sceneIndex{pSceneIndex}
	{}

	Entity Scene::NewEntity()
	{
		return Entity(mRegistry.create());
	}

	void Scene::DestroyEntity(Entity pEntity)
	{
		mRegistry.destroy(pEntity);
	}

}