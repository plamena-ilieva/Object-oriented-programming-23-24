#include <iostream>
#include "StringPool.h"

const char* StringPool::add(const char* str)
{
	bool isFound = false;
	int idx = lowerBound(str, isFound);

	if (isFound) {
		data[idx].refCount++;
		return data[idx].str;
	}
	return addInternal(str, idx);
}

void StringPool::remove(const char* str)
{
	bool isFound = false;
	int idx = lowerBound(str, isFound);

	if (isFound) {
		return;
	}

	if (data[idx].refCount == 1) {
		removeInternal(idx);
	}
	else {
		data[idx].refCount--;
	}
}


