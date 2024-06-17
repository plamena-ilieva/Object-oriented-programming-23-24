#pragma once
#include "VectorCommand.h"
#include "MyQueue.hpp"
#include "MyStack.hpp"
#include "Polymorphic_Ptr.hpp"
#include "SwapCommand.h"
#include "SortCommand.h"

class CommandExecutor
{
	MyQueue< Polymorphic_Ptr<VectorCommand>> toBeExecuted;
	MyStack< Polymorphic_Ptr<VectorCommand>, 64> history;

	CommandExecutor() = default;
	~CommandExecutor() = default;
public:
	void add(VectorCommand* c);

	void execute();
	void executeAll();

	void undo();

	static CommandExecutor& getInstance() {
		static CommandExecutor executor;
		return executor;
	}

	CommandExecutor(const CommandExecutor&) = delete;
	CommandExecutor& operator=(const CommandExecutor&) = delete;
};

class Factory {
	static Polymorphic_Ptr<VectorCommand> create(Vector<int>& v) {
		int commandNumber;
		std::cin >> commandNumber;
		if (commandNumber == 1) {
			size_t from, to;
			std::cin >> from >> to;
			return new SwapCommand(v, from, to);
		}
		else if (commandNumber == 2) {
			return new SortCommand(v);
		}

		throw std::invalid_argument("Invalid command number");
	}
};
