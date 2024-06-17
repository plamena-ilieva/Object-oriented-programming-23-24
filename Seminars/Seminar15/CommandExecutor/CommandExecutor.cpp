#include "CommandExecutor.h"

void CommandExecutor::add(VectorCommand* c)
{
	toBeExecuted.push(c);
}

void CommandExecutor::execute()
{
	if (!toBeExecuted.isEmpty()) {
		Polymorphic_Ptr<VectorCommand> temp = toBeExecuted.peek();
		temp->execute();
		toBeExecuted.pop();

		history.push(temp);
	}
}

void CommandExecutor::executeAll()
{
	while (!toBeExecuted.isEmpty()) {
		execute();
	}
}

void CommandExecutor::undo()
{
	if (!history.isEmpty()) {
		Polymorphic_Ptr<VectorCommand> temp = history.peek();
		temp->undo();

		history.pop();
	}
}
