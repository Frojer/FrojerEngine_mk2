#pragma once

#include <memory>

class FEObject
{
public:
	FEObject() = delete;
	FEObject(const FEObject& other) = delete;
	FEObject& operator=(const FEObject& rhs) = delete;
};