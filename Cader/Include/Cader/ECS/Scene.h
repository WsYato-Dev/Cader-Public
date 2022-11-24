#pragma once

#include "Cader/ECS/Entity.h"
#include "Cader/Types/Common.h"
#include "Cader/Utility/Assert.h"

#include <entt/entt.hpp>

namespace CDR {

	class SceneManager;

	class Scene final
	{
		friend SceneManager;

		entt::registry mRegistry;

	public:
		const u8 sceneIndex;

	private:
		Scene(u8 pSceneIndex);
		~Scene() = default;

	public:
		Entity NewEntity();
		void DestroyEntity(Entity pEntity);

		template<typename _T>
		inline bool HasComponent(Entity pEntity)
		{
			return mRegistry.try_get<_T>(pEntity) != nullptr;
		}

		template<typename _T, typename ..._Args>
		inline _T& AddComponent(Entity pEntity, _Args&& ...pArgs)
		{
			CDR_ASSERT(!HasComponent<_T>(pEntity));
			return mRegistry.emplace<_T>(pEntity, std::forward<_Args>(pArgs)...);
		}

		template<typename _T>
		inline void RemoveComponent(Entity pEntity)
		{
			CDR_ASSERT(HasComponent<_T>(pEntity));
			mRegistry.remove<_T>(pEntity);
		}

		template<typename _T>
		inline _T& GetComponent(Entity pEntity)
		{
			CDR_ASSERT(HasComponent<_T>(pEntity));
			return mRegistry.get<_T>(pEntity);
		}

		template<typename ..._Components>
		inline auto GetAllEntitiesWith()
		{
			return mRegistry.view<_Components...>();
		}
	};

}