#include "Renderer2D.h"

#include "Cader/ECS/Components.h"
#include "Cader/ECS/Scene.h"

#include <entt/entt.hpp>

namespace CDR {

	Renderer2D::Renderer2D(const u32 pMaxQuads)
	{
		mRenderTargets.resize(pMaxQuads);

		constexpr u16 quadIndicies[6]
		{
			0, 1, 2,
			2, 3, 0
		};

		mIndexBuffer = new VK::IndexBuffer(sizeof(u16) * 6);

		VK::StagingBuffer stagingBuffer(sizeof(u16) * 6);
		stagingBuffer.Update(&quadIndicies[0]);
		stagingBuffer.CopyToBuffer(mIndexBuffer->GetBuffer(), sizeof(u16) * 6);

		mDefault2D = new VK::Default2D(sizeof(RenderTarget) * pMaxQuads);
	}

	Renderer2D::~Renderer2D()
	{
		delete mDefault2D;
		delete mIndexBuffer;
	}

	void Renderer2D::Render(Scene& pScene, const VkCommandBuffer pCommandBuffer)
	{
		const auto& view = pScene.GetAllEntitiesWith<ColorComponent, Position2DComponent, Size2DComponent>();

		u32 targetCount = 0;

		for(entt::entity entity : view)
		{
			if(mRenderTargets.size() <= targetCount)
				break;

			const auto& [color, position, size] = view.get<ColorComponent, Position2DComponent, Size2DComponent>(entity);

			mRenderTargets[targetCount].color = color.color;
			mRenderTargets[targetCount].position = position.position;
			mRenderTargets[targetCount].size = size.size;

			targetCount++;
		}

		mDefault2D->Bind(pCommandBuffer);
		mDefault2D->GetStorageBuffer().Update((sizeof(RenderTarget) * targetCount), 0, &mRenderTargets[0]);

		vkCmdBindIndexBuffer(pCommandBuffer, mIndexBuffer->GetBuffer(), 0, VK_INDEX_TYPE_UINT16);
		vkCmdDrawIndexed(pCommandBuffer, 6, targetCount, 0, 0, 0);
	}

}