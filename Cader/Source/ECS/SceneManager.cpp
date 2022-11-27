#include "Cader/ECS/SceneManager.h"

#include "Cader/ECS/Scene.h"
#include "Cader/Utility/Assert.h"
#include "Cader/Utility/Random.h"

namespace CDR {

	std::map<u8, Scene*> SceneManager::sScenes;
	u8 SceneManager::sActiveSceneIndex{0};

	void SceneManager::DestroyAll()
	{
		for(const auto& scene : sScenes)
			delete scene.second;
	}

	Scene* SceneManager::SetActiveScene(u8 pSceneIndex)
	{
		CDR_ASSERT(Exists(pSceneIndex));

		sActiveSceneIndex = pSceneIndex;
		return sScenes[pSceneIndex];
	}

	u8 SceneManager::Create(Text pSceneName)
	{
		u8 sceneIndex = Get(pSceneName);

		if(sceneIndex)
			return sceneIndex;

		sceneIndex = (u8)Random::UInt16();

		while(Exists(sceneIndex) || sceneIndex == 0)
			sceneIndex = (u8)Random::UInt16();

		sScenes[sceneIndex] = new Scene(pSceneName, sceneIndex);
		return sceneIndex;
	}

	void SceneManager::Destroy(u8 pSceneIndex)
	{
		CDR_ASSERT(pSceneIndex != sActiveSceneIndex && Exists(pSceneIndex));

		delete sScenes[pSceneIndex];
		sScenes.erase(pSceneIndex);
	}

	bool SceneManager::Exists(u8 pSceneIndex)
	{
		return sScenes.find(pSceneIndex) != sScenes.end();
	}

	Scene* SceneManager::Get(u8 pSceneIndex)
	{
		CDR_ASSERT(Exists(pSceneIndex));
		return sScenes[pSceneIndex];
	}

	u8 SceneManager::Get(Text pSceneName)
	{
		for(const auto& scene : sScenes)
			if(scene.second->sceneName == pSceneName)
				return scene.first;

		return 0;
	}

	std::vector<u8> SceneManager::GetAllSceneIndicies()
	{
		std::vector<u8> indicies(sScenes.size());

		u8 index = 0;
		for(const auto& scene : sScenes)
			indicies[index++] = scene.first;

		return indicies;
	}

	std::vector<Text> SceneManager::GetAllSceneNames()
	{
		std::vector<Text> names(sScenes.size());

		u8 index = 0;
		for(const auto& scene : sScenes)
			names[index++] = scene.second->sceneName;

		return names;
	}

}