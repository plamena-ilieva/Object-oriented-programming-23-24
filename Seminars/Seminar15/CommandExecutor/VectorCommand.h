#pragma once
#include "Vector.hpp"

class VectorCommand
{
protected:
	Vector<int>& data;
public:
	VectorCommand(Vector<int>& data) : data(data) {}

	virtual void execute() = 0;
	virtual void undo() = 0;

	virtual ~VectorCommand() = default;
	virtual VectorCommand* clone() const = 0;

};

