#pragma once

#include "Cader/Types/Common.h"

#include <map>
#include <vector>

namespace CDR {

	class Engine;
	class Scene;

	class SceneManager final
	{
		static void DestroyAll();
		static Scene* SetActiveScene(const u8 pSceneIndex);

	public:
		static u8 Create(const Text pSceneName);
		static void Destroy(const u8 pSceneIndex);

		static bool Exists(const u8 pSceneIndex);
		static Scene* Get(const u8 pSceneIndex);
		static u8 Get(const Text pSceneName);

		static std::vector<u8> GetAllSceneIndicies();
		static std::vector<Text> GetAllSceneNames();

		static u8 Count() { return (u8)sScenes.size(); }

	private:
		static std::map<u8, Scene*> sScenes;
		static u8 sActiveSceneIndex;

		friend Engine;
	};

}