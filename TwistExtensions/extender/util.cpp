#include <Extender/util.h>

#include <Windows.h>
#include <Extender/CodeInjectionStream.h>

#include <ctime>
#include <fstream>

bool test_string_pointer(const char *testPointer, const char *testStr)
{
	// Make sure we can actually read from the test memory location
	MEMORY_BASIC_INFORMATION memInfo;
	if (VirtualQuery(testPointer, &memInfo, sizeof(memInfo)) != sizeof(memInfo))
		return false;
	if (memInfo.Protect == 0 || (memInfo.Protect & PAGE_NOACCESS) || (memInfo.Protect & PAGE_EXECUTE))
		return false;

	// Check if the string matches
	if (memcmp(testPointer, testStr, strlen(testStr)) != 0)
		return false;
	return true;
}

void inject_jmp(int address, void(*func))
{
	void* initPtr = reinterpret_cast<void*>(address);
	CodeInjection::CodeInjectionStream stream(initPtr, 6);
	stream.writeRel32Jump(func);
	stream.flush();
}

void inject_nops(int address, int count)
{
    void* initPtr = reinterpret_cast<void*>(address);
    CodeInjection::CodeInjectionStream stream(initPtr, count + 1); // <-- this part
    stream.writeNops(count);
    stream.flush();
}

void inject_byte(int address, int byte)
{
    void* initPtr = reinterpret_cast<void*>(address);
    CodeInjection::CodeInjectionStream stream(initPtr, 1); // <-- this part
    char byteArray[1] = { byte };
    stream.write(byteArray, 1);
    stream.flush();
}

int random(int min, int max) //range : [min, max)
{
    static bool first = true;
    if (first)
    {
        srand(static_cast<int>(time(nullptr))); //seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

std::string lastError = "";

void setLastError(std::string error)
{
    if (lastError.length() > 0)
        lastError += "\n";
    lastError += "> " + error;
    printf_s("%s", (error + "\n").c_str());
}


bool fileExists(std::string path)
{
    std::ifstream f(path.c_str());
    return f.good();
}
