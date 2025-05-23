#pragma once
#include <exception>
#include <string>
enum except_type { MemoryAllocateError, IndexOutOfRange, SizeBelowZero, NegativeRange };
#include<iostream>

class SetException {
private:
	except_type id;
public:
	SetException(except_type id) { this->id = id; }
	const char* message() {
		if (id == MemoryAllocateError) return "Cannot allocate memory.";
		if (id == IndexOutOfRange) return "Subscirpt index out of range.";
		if (id == SizeBelowZero) return "Size below zero.";
		if (id == NegativeRange) return "Range is less than zero.";
	}
};