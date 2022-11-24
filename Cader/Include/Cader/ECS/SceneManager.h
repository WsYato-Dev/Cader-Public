#pragma once

#include "Cader/Types/Common.h"

#include <map>

namespace CDR {

	class Engine;
	class Scene;

	class SceneManager final
	{
		friend Engine;

		static std::map<u8, Scene*> sScenes;
		static Scene* sActiveScene;

	public:
		static u8 Create();
		static void Destroy(u8 pSceneIndex);

		static inline Scene* GetScene(u8 pSceneIndex) noexcept { return sScenes[pSceneIndex]; }

		static inline Scene* GetActive() noexcept { return sActiveScene; }
		static Scene* SetActive(u8 pSceneIndex);

		static inline u8 Count() { return (u8)sScenes.size(); }
	};

}