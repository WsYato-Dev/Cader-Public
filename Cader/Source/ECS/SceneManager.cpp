#include "Cader/ECS/SceneManager.h"

#include "Cader/ECS/Scene.h"
#include "Cader/Maths/Random.h"
#include "Cader/Utility/Assert.h"

namespace CDR {

	Scene* SceneManager::sActiveScene{nullptr};
	std::map<u8, Scene*> SceneManager::sScenes;

	u8 SceneManager::Create()
	{
		u8 sceneIndex = (u8)Random::UInt16();

		while(sScenes.find(sceneIndex) != sScenes.end())
			sceneIndex = (u8)Random::UInt16();

		sScenes[sceneIndex] = new Scene(sceneIndex);
		return sceneIndex;
	}

	void SceneManager::Destroy(u8 pSceneIndex)
	{
		CDR_ASSERT(sScenes.find(pSceneIndex) != sScenes.end());

		delete sScenes[pSceneIndex];
		sScenes.erase(pSceneIndex);
	}

	Scene* SceneManager::SetActive(u8 pSceneIndex)
	{
		CDR_ASSERT(sScenes.find(pSceneIndex) != sScenes.end());

		sActiveScene = sScenes[pSceneIndex];
		return sActiveScene;
	}

}