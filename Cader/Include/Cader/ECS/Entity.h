#pragma once

#include "Cader/Types/Common.h"

#include <entt/entt.hpp>

namespace CDR {

	class Scene;

	struct Entity final
	{
		friend Scene;

	private:
		const entt::entity mHandle{entt::null};

	public:
		constexpr Entity() = default;

		constexpr Entity(entt::entity pHandle)
			: mHandle{pHandle}
		{}

	public:
		constexpr operator u32() const noexcept { return (u32)mHandle; }
		constexpr operator entt::entity() const noexcept { return mHandle; }
	};

}