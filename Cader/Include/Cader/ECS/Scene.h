#pragma once

#include "Cader/ECS/Entity.h"
#include "Cader/Types/Common.h"
#include "Cader/Utility/Assert.h"

#include <entt/entt.hpp>

namespace CDR {

	class SceneManager;

	class Scene final
	{
		Scene(const Text pSceneName, const u8 pSceneIndex);
		~Scene() = default;

	public:
		Entity NewEntity();
		void DestroyEntity(const Entity pEntity);

		template<typename _T>
		bool HasComponent(const Entity pEntity)
		{
			return mRegistry.try_get<_T>(pEntity) != nullptr;
		}

		template<typename _T, typename ..._Args>
		_T& AddComponent(const Entity pEntity, const _Args&& ...pArgs)
		{
			CDR_ASSERT(!HasComponent<_T>(pEntity));
			return mRegistry.emplace<_T>(pEntity, std::forward<_Args>(pArgs)...);
		}

		template<typename _T>
		void RemoveComponent(const Entity pEntity)
		{
			CDR_ASSERT(HasComponent<_T>(pEntity));
			mRegistry.remove<_T>(pEntity);
		}

		template<typename _T>
		_T& GetComponent(const Entity pEntity)
		{
			CDR_ASSERT(HasComponent<_T>(pEntity));
			return mRegistry.get<_T>(pEntity);
		}

		template<typename ..._Components>
		auto GetAllEntitiesWith()
		{
			return mRegistry.view<_Components...>();
		}

		const Text sceneName;
		const u8 sceneIndex;

	private:
		entt::registry mRegistry;

		friend SceneManager;
	};

}