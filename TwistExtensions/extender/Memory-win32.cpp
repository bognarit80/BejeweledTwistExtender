#include "Memory.h"
#include <Windows.h>

namespace Memory
{
	/// <summary>
	/// Allocates a block of readable, writable, and executable memory.
	/// </summary>
	/// <param name="minSize">The minimum amount of data to allocate.</param>
	/// <param name="actualSize">Variable to store the actual allocated size to.</param>
	/// <returns>The pointer to the allocated data if successful, or <c>NULL</c> otherwise.</returns>
	void *allocateCode(size_t minSize, size_t *actualSize)
	{
		// Allocate pages
		void *buffer = VirtualAlloc(NULL, minSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (!buffer)
			return nullptr;

		// Query the actual size of it
		MEMORY_BASIC_INFORMATION info;
		if (VirtualQuery(buffer, &info, sizeof(MEMORY_BASIC_INFORMATION)) != sizeof(MEMORY_BASIC_INFORMATION))
		{
			VirtualFree(buffer, 0, MEM_RELEASE);
			return nullptr;
		}
		*actualSize = info.RegionSize;
		return buffer;
	}
	
	/// <summary>
	/// Frees a block of code allocated with <see cref="allocateCode"/>.
	/// </summary>
	/// <param name="code">Pointer to the code to free. It must have been allocated with <see cref="allocateCode"/>.
	/// <param name="size">Size of the block to free.</param>
	/// <returns><c>true</c> if successful.</returns>
	bool freeCode(void *code, size_t size)
	{
		return (VirtualFree(code, 0, MEM_RELEASE) != 0); // Note: the != 0 is not redundant here
	}
	
	/// <summary>
	/// Flushes the instruction cache for a block of code.
	/// </summary>
	/// <param name="start">Start of the block of code to flush.</param>
	/// <param name="size">Size of the block of code to flush.</param>
	void flushCode(void *start, size_t size)
	{
		FlushInstructionCache(GetCurrentProcess(), start, size);
	}
	
	/// <summary>
	/// Unprotects a block of code so that it can be written to.
	/// </summary>
	/// <param name="code">Start of the region of code to unprotect.</param>
	/// <param name="size">Size of the region of code to unprotect.</param>
	/// <param name="oldProtection">Variable to receive the old protection state. The meaning of this value is platform-dependant.</param>
	/// <returns><c>true</c> if successful.</returns>
	bool unprotectCode(void *code, size_t size, int *oldProtection)
	{
		return (VirtualProtect(code, size, PAGE_EXECUTE_READWRITE, reinterpret_cast<DWORD*>(oldProtection)) != 0);
	}
	
	/// <summary>
	/// Protects a block of code that was previously unprotected with <see cref="unprotectCode"/>.
	/// </summary>
	/// <param name="code">Start of the region of code to protect.</param>
	/// <param name="size">Size of the region of code to protect.</param>
	/// <param name="protection">The oldProtection value received from <see cref="unprotectCode"/>.
	/// <returns><c>true</c> if successful.</returns>
	bool protectCode(void *code, size_t size, int oldProtection)
	{
		DWORD temp;
		return (VirtualProtect(code, size, oldProtection, &temp) != 0);
	}
}
