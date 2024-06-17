#pragma once
#include "VectorCommand.h"

class SortCommand : public VectorCommand
{
	Vector<int>* snapshot = nullptr;

public:
	SortCommand(Vector<int>& data);
	void execute() override;

	void undo() override;

	VectorCommand* clone() const override;
};

