#include "Buffers.h"

#include "Cader/Utility/Assert.h"
#include "../Utility.h"
#include "Objects.h"

#include <cstring>

namespace CDR::VK {

	Buffer::Buffer(u32 pSize, VkBufferUsageFlags pUsage, VkMemoryPropertyFlags pProperties)
		: size{pSize}
	{
		VkBufferCreateInfo bufferInfo = {VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO};
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		bufferInfo.usage = pUsage;
		bufferInfo.size = pSize;

		VK_VERIFY(Objects::CreateBuffer(bufferInfo, &mBuffer));

		VkMemoryRequirements memoryRequirements;
		Objects::GetBufferMemoryRequirements(mBuffer, &memoryRequirements);

		VkMemoryAllocateInfo memoryInfo = {VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO};
		memoryInfo.allocationSize = memoryRequirements.size;
		memoryInfo.memoryTypeIndex = Objects::FindMemoryType(memoryRequirements.memoryTypeBits, pProperties);

		VK_VERIFY(Objects::AllocateMemory(memoryInfo, &mMemory));
		VK_VERIFY(Objects::BindBufferMemory(mBuffer, mMemory));
	}

	Buffer::~Buffer()
	{
		Objects::FreeMemory(mMemory);
		Objects::DestroyBuffer(mBuffer);
	}

	BufferHost::BufferHost(u32 pSize, VkBufferUsageFlags pUsage, VkMemoryPropertyFlags pProperties)
		: Buffer{pSize, pUsage, pProperties}
	{}

	void BufferHost::Update(const void* pData)
	{
		void* data;
		VK_VERIFY(Objects::MapMemory(mMemory, 0, size, 0, &data));
		memcpy(data, pData, size);
		Objects::UnMapMemory(mMemory);
	}

	void BufferHost::Update(u32 pSize, u32 pOffset, const void* pData)
	{
		CDR_ASSERT(pSize + pOffset <= size);

		void* data;
		VK_VERIFY(Objects::MapMemory(mMemory, pOffset, pSize, 0, &data));
		memcpy(data, pData, pSize);
		Objects::UnMapMemory(mMemory);
	}

	StagingBuffer::StagingBuffer(u32 pSize)
		: BufferHost{pSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT}
	{}

	void StagingBuffer::CopyToBuffer(const VkBuffer pDst, u32 pSize)
	{
		VkBufferCopy copyRegion = {};
		copyRegion.srcOffset = 0;
		copyRegion.dstOffset = 0;
		copyRegion.size = pSize;

		VkCommandBuffer commandBuffer;
		Objects::AllocateDirectTransferCommand(&commandBuffer);

		VkCommandBufferBeginInfo beginInfo = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		VK_VERIFY(vkBeginCommandBuffer(commandBuffer, &beginInfo));
		vkCmdCopyBuffer(commandBuffer, mBuffer, pDst, 1, &copyRegion);
		VK_VERIFY(vkEndCommandBuffer(commandBuffer));

		Objects::SubmitAndFreeDirectTransferCommand(commandBuffer);
	}

	VertexBuffer::VertexBuffer(u32 pSize)
		: Buffer{pSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT}
	{}

	VertexBufferHost::VertexBufferHost(u32 pSize)
		: BufferHost{pSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT}
	{}

	IndexBuffer::IndexBuffer(u32 pSize)
		: Buffer{pSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT}
	{}

	IndexBufferHost::IndexBufferHost(u32 pSize)
		: BufferHost{pSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT}
	{}

	UniformBuffer::UniformBuffer(u32 pSize)
		: BufferHost{pSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT}
	{}

	StorageBuffer::StorageBuffer(u32 pSize)
		: BufferHost{pSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT}
	{}

}