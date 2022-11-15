#include <Extender/CodeAllocator.h>
#include <Extender/Memory.h>

namespace CodeInjection
{
	CodeAllocator::CodeAllocator()
		: ptr(NULL), sizeRemaining(0)
	{
	}

	CodeAllocator::~CodeAllocator()
	{
		releaseAllBuffers();
	}

	/// <summary>
	/// Allocates a block of code.
	/// </summary>
	/// <param name="size">The size of the block to allocate.</param>
	/// <returns>The allocated block if successful, or <c>NULL</c> on failure.</returns>
	void* CodeAllocator::allocate(size_t size)
	{
		if (!ensureAvailable(size))
			return NULL;

		// Simple push-back-the-pointer allocation
		uint8_t *result = ptr;
		ptr += size;
		sizeRemaining -= size;
		return result;
	}

	/// <summary>
	/// Ensures that a number of bytes is available in the buffer.
	/// If the buffer is too small, a new one will be allocated.
	/// </summary>
	/// <param name="size">The number of bytes requested.</param>
	/// <returns><c>true</c> on success.</returns>
	bool CodeAllocator::ensureAvailable(size_t size)
	{
		if (size > sizeRemaining)
			return newBuffer(size);
		return true;
	}

	/// <summary>
	/// Allocates a new buffer.
	/// </summary>
	/// <param name="minSize">The minimum size that the buffer should be.</param>
	/// <returns><c>true</c> on success.</returns>
	bool CodeAllocator::newBuffer(size_t minSize)
	{
		size_t actualSize;
		void *buffer = Memory::allocateCode(minSize, &actualSize);
		if (!buffer)
			return false;

		// Set the current pointer, set the size remaining, and save the buffer so it can be freed
		ptr = static_cast<uint8_t*>(buffer);
		sizeRemaining = actualSize;
		BufferInfo info = { ptr, actualSize };
		buffers.push(info);
		return true;
	}

	/// <summary>
	/// Frees the memory occupied by a buffer.
	/// It must have been allocated with <see cref="newBuffer"/>.
	/// </summary>
	/// <param name="buffer">The buffer to release.</param>
	void CodeAllocator::releaseBuffer(BufferInfo buffer)
	{
		Memory::freeCode(buffer.pointer, buffer.size);
	}

	/// <summary>
	/// Frees the memory occupied by all allocated buffers.
	/// </summary>
	void CodeAllocator::releaseAllBuffers()
	{
		while (!buffers.empty())
		{
			releaseBuffer(buffers.top());
			buffers.pop();
		}
		ptr = NULL;
		sizeRemaining = 0;
	}
}
