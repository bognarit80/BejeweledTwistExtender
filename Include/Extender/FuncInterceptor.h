#ifndef PLUGINLOADER_FUNCINTERCEPTOR_H
#define PLUGINLOADER_FUNCINTERCEPTOR_H

#include <unordered_map>
#include "CodeInjectionStream.h"
#include "TrampolineGenerator.h"

namespace CodeInjection
{
	/// <summary>
	/// Provides facilities for intercepting functions.
	/// </summary>
	class FuncInterceptor
	{
	public:
		FuncInterceptor(CodeInjectionStream *stream, CodeAllocator *allocator)
			: stream(stream), trampolineGen(allocator)
		{
		}

		~FuncInterceptor();

		/// <summary>
		/// Intercepts a function, routing all calls to it to another function and returning a pointer which can be used to call the original code.
		/// </summary>
		/// <param name="func">The function to intercept.</param>
		/// <param name="newFunc">The new function to redirect callers to.</param>
		/// <returns>A pointer which can be used to call the original function, or <c>NULL</c> on failure.</returns>
		template<class T>
		T intercept(T func, T newFunc)
		{
			return reinterpret_cast<T>(interceptImpl(reinterpret_cast<void*>(func), reinterpret_cast<void*>(newFunc)));
		}

		/// <summary>
		/// Restores the specified function.
		/// </summary>
		/// <param name="func">The function to restore.</param>
		void restore(void *func);

		/// <summary>
		/// Restores all intercepted functions.
		/// </summary>
		void restoreAll();

	private:
		/// <summary>
		/// Implementation of <see cref="intercept"/>.
		/// </summary>
		/// <param name="func">The function to intercept.</param>
		/// <param name="newFunc">The new function to redirect callers to.</param>
		/// <returns>A pointer which can be used to call the original function, or <c>NULL</c> on failure.</returns>
		void* interceptImpl(void *func, void *newFunc);

		/// <summary>
		/// Restores a function to point to its old code.
		/// </summary>
		/// <param name="func">The function to restore.</param>
		/// <param name="oldFunc">The old code pointer.</param>
		void restore(void *func, void *oldFunc);

		CodeInjectionStream *stream;                        // Stream used to write code
		TrampolineGenerator trampolineGen;                  // Function trampoline generator
		std::unordered_map<void*, void*> originalFunctions; // Maps functions to their original code pointers
	};
}

#endif
