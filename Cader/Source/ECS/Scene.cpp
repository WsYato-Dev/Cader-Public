#include "Cader/ECS/Scene.h"

namespace CDR {

	Scene::Scene(u8 pSceneIndex)
		: sceneIndex{pSceneIndex}
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