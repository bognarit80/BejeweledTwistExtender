#ifndef PLUGINLOADER_TRAMPOLINEGENERATOR_H
#define PLUGINLOADER_TRAMPOLINEGENERATOR_H

#include "CodeAllocator.h"

namespace CodeInjection
{
	/// <summary>
	/// Generates trampoline functions for code blocks.
	/// </summary>
	class TrampolineGenerator
	{
	public:
		explicit TrampolineGenerator(CodeAllocator *allocator)
			: allocator(allocator)
		{
		}

		/// <summary>
		/// Creates a trampoline function for a block of code.
		/// The trampoline will include all instructions found within a given range of bytes.
		/// </summary>
		/// <param name="src">The start of the block of code to create a trampoline for.</param>
		/// <param name="minSize">The number of bytes to copy instructions within.</param>
		/// <returns>A pointer to the generated trampoline function, or <c>NULL</c> on failure.</returns>
		void* createTrampoline(void *src, size_t minSize);

	private:
		/// <summary>
		/// Gets the size of a block of code after decoding the instructions within a given range of bytes.
		/// </summary>
		/// <param name="src">The start of the block of code.</param>
		/// <param name="minSize">The number of bytes to decode instructions within.</param>
		/// <returns>The number of bytes that the instructions actually span.</returns>
		size_t getCodeSize(void *src, size_t minSize);

		CodeAllocator *allocator;
	};
}

#endif
