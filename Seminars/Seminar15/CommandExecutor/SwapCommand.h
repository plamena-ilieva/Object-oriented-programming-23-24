#pragma once
#include "VectorCommand.h"

class SwapCommand : public VectorCommand
{
	size_t from;
	size_t to;
	bool isExecuted;

public:
	SwapCommand(Vector<int>& data, size_t form, size_t to);

	void execute() override;

	void undo() override;

	VectorCommand* clone() const override;

};

