#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include <map>
#include <unordered_map>

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef unsigned __int16 uint16;
typedef unsigned __int8 uint8;
typedef __int64 int64;
typedef __int32 int32;
typedef __int16 int16;
typedef __int8 int8;

#ifdef ECS_MAX_COMPONENT_COUNT
static const uint kMaxComponentCount = ECS_MAX_COMPONENT_COUNT;
#else
static const uint kMaxComponentCount = 32;
#endif

#ifdef ECS_CHUNK_SIZE
static const uint kChunkSize = ECS_CHUNK_SIZE;
#else
static const uint kChunkSize = 16 * 1024;
#endif

typedef std::bitset<kMaxComponentCount> Bittype;

struct array { uint16* ptr; uint16 count; };