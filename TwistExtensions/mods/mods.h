#ifndef __MODS_H_
#define __MODS_H_

#include "Extender/FuncInterceptor.h"

extern bool isMultiTwistEnabled;
extern bool isCCWEnabled;
extern bool isMouseInverted;
extern int altSound;
extern int aspectRatio;

extern bool initMods(CodeInjection::FuncInterceptor* hook);

#endif /* __MODS_H_ */
