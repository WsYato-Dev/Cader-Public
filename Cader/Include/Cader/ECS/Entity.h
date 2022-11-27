#pragma once

#include "Cader/Types/Common.h"

#include <entt/entt.hpp>

namespace CDR {

	class Scene;

	struct Entity final
	{
		Entity() = default;

		explicit Entity(entt::entity pHandle)
			: mHandle{pHandle}
		{}

		operator entt::entity() const noexcept { return mHandle; }

	private:
		entt::entity mHandle{entt::null};

		friend Scene;
	};

}