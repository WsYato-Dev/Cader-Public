#pragma once

#include "Cader/Types/Common.h"

#include <map>
#include <vector>

namespace CDR {

	class Engine;
	class Scene;

	class SceneManager final
	{
		friend Engine;

		static std::map<u8, Scene*> sScenes;
		static u8 sActiveSceneIndex;

		static Scene* SetActiveScene(u8 pSceneIndex);
		static void DestroyAll();

	public:
		static u8 Create(Text pSceneName);
		static void Destroy(u8 pSceneIndex);

		static bool Exists(u8 pSceneIndex);
		static Scene* Get(u8 pSceneIndex);
		static u8 Get(Text pSceneName);

		static std::vector<u8> GetAllSceneIndicies();
		static std::vector<Text> GetAllSceneNames();

		static inline u8 Count() { return (u8)sScenes.size(); }
	};

}