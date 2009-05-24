#ifndef ltask_h
#define ltask_h

#include "engines/grim/lua/lua.h"
#include "engines/grim/lua/lstate.h"

extern int32 task_tag;

void start_script();
void stop_script();
void next_script();
void identify_script();
void pause_scripts();
void unpause_scripts();
void find_script();
void break_here();

#endif