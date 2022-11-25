#pragma once

#include "Cader/Types/Common.h"

#include <vulkan/vulkan.h>

namespace CDR::VK {

	class Buffer
	{
	public:
		Buffer(const u32 pSize, const VkBufferUsageFlags pUsage, const VkMemoryPropertyFlags pProperties);
		~Buffer();

		const VkBuffer GetBuffer() const noexcept { return mBuffer; }
		const VkDeviceMemory GetMemory() const noexcept { return mMemory; }

		const u32 size;

	protected:
		VkBuffer mBuffer;
		VkDeviceMemory mMemory;
	};

	class BufferHost: public Buffer
	{
	public:
		BufferHost(const u32 pSize, const VkBufferUsageFlags pUsage, const VkMemoryPropertyFlags pProperties);

		void Update(const void* pData);
		void Update(const u32 pSize, const u32 pOffset, const void* pData);
	};

	// Staging Buffer
	class StagingBuffer final: public BufferHost
	{
	public:
		StagingBuffer(u32 pSize);

		void CopyToBuffer(const VkBuffer pDst, const u32 pSize);
	};

	// Vertex Buffer
	class VertexBuffer final: public Buffer
	{
	public:
		VertexBuffer(const u32 pSize);
	};

	class VertexBufferHost final: public BufferHost
	{
	public:
		VertexBufferHost(const u32 pSize);
	};

	// Index Buffer
	class IndexBuffer final: public Buffer
	{
	public:
		IndexBuffer(const u32 pSize);
	};

	class IndexBufferHost final: public BufferHost
	{
	public:
		IndexBufferHost(const u32 pSize);
	};

	// Uniform Buffer
	class UniformBuffer final: public BufferHost
	{
	public:
		UniformBuffer(const u32 pSize);
	};

	// Storage Buffer
	class StorageBuffer final: public BufferHost
	{
	public:
		StorageBuffer(const u32 pSize);
	};

}