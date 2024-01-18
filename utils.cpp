typedef unsigned short u16; //упрощение написания
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

#define global_variable static
#define internal static

inline int //сжимание числа
clamp(int min, int val, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}