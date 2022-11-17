#pragma once

#include "Cader/Types/Common.h"

#include <vulkan/vulkan.h>

namespace CDR::VK {

	class Buffer
	{
	protected:
		VkBuffer mBuffer;
		VkDeviceMemory mMemory;

	public:
		const u32 size;

		Buffer(u32 pSize, VkBufferUsageFlags pUsage, VkMemoryPropertyFlags pProperties);
		~Buffer();

		inline const VkBuffer& GetBuffer() const noexcept { return mBuffer; }
		inline const VkDeviceMemory& GetMemory() const noexcept { return mMemory; }
	};

	class BufferHost: public Buffer
	{
	public:
		BufferHost(u32 pSize, VkBufferUsageFlags pUsage, VkMemoryPropertyFlags pProperties);

		void Update(const void* pData);
		void Update(u32 pSize, u32 pOffset, const void* pData);
	};

	// Staging Buffer
	class StagingBuffer final: public BufferHost
	{
	public:
		StagingBuffer(u32 pSize);

		void CopyToBuffer(const VkBuffer pDst, u32 pSize);
	};

	// Vertex Buffer
	class VertexBuffer final: public Buffer
	{
	public:
		VertexBuffer(u32 pSize);
	};

	class VertexBufferHost final: public BufferHost
	{
	public:
		VertexBufferHost(u32 pSize);
	};

	// Index Buffer
	class IndexBuffer final: public Buffer
	{
	public:
		IndexBuffer(u32 pSize);
	};

	class IndexBufferHost final: public BufferHost
	{
	public:
		IndexBufferHost(u32 pSize);
	};

	// Uniform Buffer
	class UniformBuffer final: public BufferHost
	{
	public:
		UniformBuffer(u32 pSize);
	};

	// Storage Buffer
	class StorageBuffer final: public BufferHost
	{
	public:
		StorageBuffer(u32 pSize);
	};

}