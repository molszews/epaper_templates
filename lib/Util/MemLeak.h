#pragma once

#ifndef _MEM_LEAK_H
#define _MEM_LEAK_H

static const char* fmtMemCk = "Free: %d\tMaxAlloc: %d\t PSFree: %d\n";
#define MEMCK Serial.printf(fmtMemCk,ESP.getFreeHeap(),ESP.getMaxAllocHeap(),ESP.getFreePsram())

#endif