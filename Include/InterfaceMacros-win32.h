#pragma once

// Utility macros
#define EXPAND(...) __VA_ARGS__

// Macro for quickly declaring a function pointer that points to a static address
#define FN(rettype, name, args, addr) \
	namespace { rettype (*const name) args = reinterpret_cast<rettype (*) args>(addr); }

#define FNSTDCALL(rettype, name, args, addr) \
	namespace { rettype (__stdcall *const name) args = reinterpret_cast<rettype (__stdcall *) args>(addr); }

#define FN2(rettype, name, args, addr) \
	rettype (*const name) args = reinterpret_cast<rettype (*) args>(addr);

// Macros for declaring overloaded function pointers
//
// Usage example:
// OVERLOAD_PTR {
//     OVERLOAD_FN(int, (int x, int y), 0x12345);
//     OVERLOAD_FN(int, (int z), 0x23456);
// } foo;
#define OVERLOAD_PTR static struct

// Huge hack to make this work with Intellisense
// If Intellisense is parsing the file, we show it that a () operator exists so that it can help with parameters
// However, when the compiler actually reads it, it'll only see a typecast operator
#ifndef __INTELLISENSE__
// This is what the compiler will see
#define OVERLOAD_FN(rettype, args, addr)                \
	private:                                            \
		typedef rettype (*t_##addr##_) args;            \
	public:                                             \
		inline operator t_##addr##_ () const            \
		{                                               \
			return reinterpret_cast<t_##addr##_>(addr); \
		}
#else
// This is what intellisense will see
#define OVERLOAD_FN(rettype, args, addr)                \
	private:                                            \
		typedef rettype (*t_##addr##_) args;            \
	public:                                             \
		inline rettype operator () args const           \
		{                                               \
		}                                               \
		inline operator t_##addr##_() const             \
		{                                               \
			return reinterpret_cast<t_##addr##_>(addr); \
		}
#endif

// Defines the offset of a class's vtable pointer. Required in order to use VIRTFN and VIRTFNSIMP.	
#define VTABLE(offset) \
	uint32_t z_vtableLookup_(int index) \
	{ \
		return (*reinterpret_cast<uint32_t**>(reinterpret_cast<uint32_t>(this) + offset))[index]; \
	} \
	virtual void z_foo_() = 0
		
// Defines a virtual function wrapper
#define VIRTFN(rettype, name, args, argnames, index) \
	MEMBERFN(rettype, name, args, argnames, z_vtableLookup_(index))

#define VIRTFNF(rettype, name, args, argnames, index) \
	MEMBERFNF(rettype, name, args, argnames, z_vtableLookup_(index))

// Same as VIRTFN, but defines a "simple" virtual function with no arguments
#define VIRTFNSIMP(rettype, name, index) \
	MEMBERFNSIMP(rettype, name, z_vtableLookup_(index))
	
// Defines a virtual destructor wrapper
#define VIRTDTOR(name, index) \
	MEMBERDTOR(name, z_vtableLookup_(index))

// Defines an unnamed pure virtual function
#define UNKVIRT(x) virtual void z_unk##x##_() = 0

// Defines an undefined pure virtual function
#define UNDEFVIRT(name) virtual void z_undef_##name##_() = 0

// Defines a "raw" member function pointer
#define RAWMEMBERFN(clazz, rettype, name, args, addr) \
	namespace { rettype (__thiscall *const name) (EXPAND(clazz *thisobj, EXPAND args)) = reinterpret_cast<rettype (__thiscall *) (EXPAND(clazz *thisobj, EXPAND args))>(addr); }

// Same as RAWMEMBERFN, but defines a "simple" pointer with no arguments
#define RAWMEMBERFNSIMP(clazz, rettype, name, addr) \
	namespace { rettype (__thiscall *const name) (clazz *thisobj) = reinterpret_cast<rettype (__thiscall *) (clazz *thisobj)>(addr); }

// Defines a wrapper which calls a member function on a class
// Yes, argument names need to be repeated, but there's not much I can do about that AFAIK
#define MEMBERFN(rettype, name, args, argnames, addr)                                                                       \
	rettype name args                                                                                                       \
	{                                                                                                                       \
		return reinterpret_cast<rettype (__thiscall *) (EXPAND(void*, EXPAND args))>(addr) (EXPAND(this, EXPAND argnames)); \
	}

#define MEMBERFNF(rettype, name, args, argnames, addr)                                                                       \
	rettype name args                                                                                                       \
	{                                                                                                                       \
		return reinterpret_cast<rettype (__stdcall *) (EXPAND(void*, EXPAND args))>(addr) (EXPAND(this, EXPAND argnames)); \
	}

// Same as MEMBERFN, but defines a "simple" wrapper with no arguments
#define MEMBERFNSIMP(rettype, name, addr)                                     \
	rettype name()                                                            \
	{                                                                         \
		return reinterpret_cast<rettype (__thiscall *) (void*)>(addr) (this); \
	}

/*#define MEMBERFNSTATIC(rettype, name, args, argnames, addr)                                                                       \
	static rettype name args                                                                                                       \
	{                                                                                                                       \
		return reinterpret_cast<rettype (EXPAND(*, EXPAND args))>(addr)); \
	}*/

#define MEMBERFNSTATICSIMP(rettype, name, addr)                               \
	static rettype name()                                                     \
	{                                                                         \
		return reinterpret_cast<rettype>(addr); \
	}
	
// Defines a destructor wrapper
#define MEMBERDTOR(name, addr)                                      \
	name()                                                          \
	{                                                               \
		reinterpret_cast<void (__thiscall *) (void*)>(addr) (this); \
	}

// Defines a global variable
#define GLOBALVAR(type, name, addr) namespace { type &name = *reinterpret_cast<type*>(addr); }

#define GLOBALVAR2(type, name, addr) namespace { type *name = *reinterpret_cast<type*>(addr); }

// Defines a member variable
//#define MEMBERVAR(type, name, addr) type &name = *reinterpret_cast<type*>(reinterpret_cast<uint32_t>(this) + addr);

#define MEMBERVAR(type, name, addr) \
	type *name = reinterpret_cast<type*>(this + addr);

// Defines a function which uses the thiscall convention
#define THISFN(rettype, name, args)                                                               \
	rettype __fastcall z_thisfn_impl_##name (EXPAND(void*, EXPAND args));                         \
	namespace                                                                                     \
	{                                                                                             \
		__declspec(naked) void z_thisfn_jmp_##name args                                           \
		{                                                                                         \
			__asm mov edx, ecx                                                                    \
			__asm xor ecx, ecx                                                                    \
			__asm jmp z_thisfn_impl_##name                                                        \
		}                                                                                         \
	}                                                                                             \
	typedef rettype (__thiscall* z_thisfn_ptr_##name) args;                                       \
	const z_thisfn_ptr_##name name = reinterpret_cast<z_thisfn_ptr_##name>(z_thisfn_jmp_##name);  \
	rettype __fastcall z_thisfn_impl_##name (EXPAND(void*, EXPAND args))

// Defines a getter for a class field
#define GETTERFN(rettype, internaltype, name, offset)                                    \
	rettype name()                                                                       \
	{                                                                                    \
		return *reinterpret_cast<internaltype*>(reinterpret_cast<char*>(this) + offset); \
	}

// Defines a getter for a class field where the return type and internal type are the same
#define GETTERFNSIMP(type, name, offset) GETTERFN(type, type, name, offset)

// Defines a setter for a class field
#define SETTERFN(type, name, offset)                                                    \
	void name(type newValue)                                                            \
	{                                                                                   \
		*reinterpret_cast<type*>(reinterpret_cast<uint32_t>(this) + offset) = newValue; \
	}

#define JMP(addr) \
	void *a = reinterpret_cast<void*>(addr); \
	__asm { \
		mov dword ptr [address], a \
		jmp far ptr [address] \
	}

#define INSERTFN(fn, addr) \
	void * theAddr = reinterpret_cast<void *>(addr); \
	