#include <Extender/TrampolineGenerator.h>
#include <Extender/CodeInjectionStream.h>
#include <Extender/LDE64.h>

namespace
{
	const size_t JumpSize = 5;
}

namespace CodeInjection
{
	/// <summary>
	/// Creates a trampoline function for a block of code.
	/// The trampoline will include all instructions found within a given range of bytes.
	/// </summary>
	/// <param name="src">The start of the block of code to create a trampoline for.</param>
	/// <param name="minSize">The number of bytes to copy instructions within.</param>
	/// <returns>A pointer to the generated trampoline function, or <c>NULL</c> on failure.</returns>
	void* TrampolineGenerator::createTrampoline(void *src, size_t minSize)
	{
		// Need to allocate space for overwritten instructions + a jump
		size_t codeSize = getCodeSize(src, minSize);
		size_t trampolineSize = codeSize + JumpSize;

		// Allocate code for the trampoline
		void *trampoline = allocator->allocate(trampolineSize);
		if (trampoline == NULL)
			return NULL;

		// Copy overwritten instructions from the source function to the trampoline
		CodeInjectionStream stream(trampoline, trampolineSize);
		stream.write(src, codeSize);
		// TODO: Might want to integrate a proper disassembler here so that relative addresses can be corrected
		// e.g. if there's a relative call in the first five bytes, then it won't work properly when run from the trampoline

		// Write a jump back to the code following the overwritten instructions
		void *originalCode = static_cast<uint8_t*>(src) + codeSize;
		stream.writeRel32Jump(originalCode);

		return trampoline;
	}

	/// <summary>
	/// Gets the size of a block of code after decoding the instructions within a given range of bytes.
	/// </summary>
	/// <param name="src">The start of the block of code.</param>
	/// <param name="minSize">The number of bytes to decode instructions within.</param>
	/// <returns>The number of bytes that the instructions actually span.</returns>
	size_t TrampolineGenerator::getCodeSize(void *src, size_t minSize)
	{
		// Add up instruction sizes until the code size is at least minSize
		size_t codeSize = 0;
		uint8_t *ptr = static_cast<uint8_t*>(src);
		while (codeSize < minSize)
		{
			size_t instrSize = LDE::LDE(ptr, LDE::Bits32);
			codeSize += instrSize;
			ptr += instrSize;
		}
		return codeSize;
	}
}
