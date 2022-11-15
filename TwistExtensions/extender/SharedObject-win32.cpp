#include <Extender/SharedObject.h>
#include <Windows.h>

const char *SharedObject::DefaultExtension = ".dll";

SharedObject::SharedObject()
	: handle(NULL)
{
}

SharedObject::SharedObject(const char *path)
	: handle(NULL)
{
	load(path);
}

SharedObject::~SharedObject()
{
	unload();
}

bool SharedObject::load(const char *path)
{
	unload();
	handle = LoadLibrary(path);
	return (handle != NULL);
}

bool SharedObject::loaded() const
{
	return (handle != NULL);
}

bool SharedObject::unload()
{
	if (handle && CloseHandle(static_cast<HMODULE>(handle)) != 0)
	{
		handle = NULL;
		return true;
	}
	return false;
}

void *SharedObject::getSymbol(const char *name) const
{
	if (handle)
		return GetProcAddress(static_cast<HMODULE>(handle), name);
	return NULL;
}
