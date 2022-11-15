#ifndef __UTIL_H_
#define __UTIL_H_

#include <string>

#define NAKEDTYPE __declspec(naked) void
#define NAKEDDEF(name) \
    NAKEDTYPE name()

extern bool test_string_pointer(const char *testPointer, const char *testStr);

extern void inject_jmp(int address, void(*func));
extern void inject_nops(int address, int count);
extern void inject_byte(int address, int byte);


extern int random(int min, int max);

extern std::string lastError;
extern void setLastError(std::string error);

extern bool fileExists(std::string path);

#endif /* __UTIL_H_ */
