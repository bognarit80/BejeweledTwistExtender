#include <Extender/FuncInterceptor.h>
#include <string.h>

namespace
{
	// Size of a 32-bit relative jump
	const size_t JumpSize = 5;

	// Code for a thunk function which creates and destroys a stack frame
	const uint8_t ThunkCode[4] = {0x55, 0x89, 0xE5, 0x5D};
}

namespace CodeInjection
{
	FuncInterceptor::~FuncInterceptor()
	{
		if (stream)
			restoreAll();
	}

	/// <summary>
	/// Implementation of <see cref="intercept"/>.
	/// </summary>
	/// <param name="func">The function to intercept.</param>
	/// <param name="newFunc">The new function to redirect callers to.</param>
	/// <returns>A pointer which can be used to call the original function, or <c>NULL</c> on failure.</returns>
	void *FuncInterceptor::interceptImpl(void *func, void *newFunc)
	{
		if (stream == NULL || func == NULL || newFunc == NULL)
			return NULL;
		if (!stream->seekTo(func))
			return NULL;

		// As an optimization, if the function is a thunk (it only does a relative jump),
		// then a trampoline isn't necessary
		void *originalFunc = stream->peekRel32Jump();
		if (originalFunc == NULL)
		{
			// Check if it creates and destroys a stack frame first before jumping
			uint8_t thunkTest[sizeof(ThunkCode)];
			if (stream->read(thunkTest, sizeof(thunkTest)) && memcmp(thunkTest, ThunkCode, sizeof(thunkTest)) == 0)
				originalFunc = stream->peekRel32Jump();
		}
		if (originalFunc == NULL)
		{
			// Not a thunk - create a trampoline
			originalFunc = trampolineGen.createTrampoline(func, JumpSize);
			if (originalFunc == NULL)
				return NULL;
		}
		
		// Write a jump to the new function and store the original function pointer
		if (!stream->seekTo(func))
			return NULL;
		if (!stream->writeRel32Jump(newFunc))
			return NULL;
		originalFunctions[func] = originalFunc;
		return originalFunc;
	}

	/// <summary>
	/// Restores a function to point to its old code.
	/// </summary>
	/// <param name="func">The function to restore.</param>
	/// <param name="oldFunc">The old code pointer.</param>
	void FuncInterceptor::restore(void *func, void *oldFunc)
	{
		if (stream == NULL)
			return;
		if (!stream->seekTo(func))
			return;
		stream->writeRel32Jump(oldFunc);
	}

	/// <summary>
	/// Restores the specified function.
	/// </summary>
	/// <param name="func">The function to restore.</param>
	void FuncInterceptor::restore(void *func)
	{
		if (stream == NULL)
			return;
		std::unordered_map<void*, void*>::iterator it = originalFunctions.find(func);
		if (it == originalFunctions.end())
			return;
		restore(func, it->second);
		originalFunctions.erase(it);
	}

	/// <summary>
	/// Restores all intercepted functions.
	/// </summary>
	void FuncInterceptor::restoreAll()
	{
		for (std::unordered_map<void*, void*>::iterator it = originalFunctions.begin(); it != originalFunctions.end(); ++it)
			restore(it->first, it->second);
		originalFunctions.clear();
	}
}
