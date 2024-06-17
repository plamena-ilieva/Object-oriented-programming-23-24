#include "SwapCommand.h"

SwapCommand::SwapCommand(Vector<int>& data, size_t from, size_t to) :
        VectorCommand(data),
    from(from), to(to), isExecuted(false) {}

void SwapCommand::execute()
{
    std::swap(data[from], data[to]);
    isExecuted = true;
}

void SwapCommand::undo()
{
    if (isExecuted) {
        std::swap(data[from], data[to]);
    }
    isExecuted = false;
}

VectorCommand* SwapCommand::clone() const
{
    return new SwapCommand(*this);
}
