#ifndef LDE64_H
#define LDE64_H

#ifndef _MSC_VER
#ifndef __stdcall
#define __stdcall __attribute__((stdcall))
#endif
#endif

namespace LDE
{
	/// <summary>
	/// Address sizes supported by LDE64.
	/// </summary>
	enum LDEAddrSize
	{
		Bits32 = 0,
		Bits64 = 64
	};

	/// <summary>
	/// Computes the length of an instruction at an address.
	/// </summary>
	/// <param name="address">The address of the instruction to decode.</param>
	/// <param name="size">The address size to decode the instruction with.</param>
#ifndef __GNUC__
	extern "C" int __stdcall LDE(void *address, LDEAddrSize size);
#else
	int __stdcall LDE(void *address, LDEAddrSize size) asm("_LDE");
#endif
}

#endif
