#include "SortCommand.h"

SortCommand::SortCommand(Vector<int>& data) : VectorCommand(data)
{
}

void SortCommand::execute()
{
    if (snapshot) {
        delete snapshot;
    }
    snapshot = new Vector<int>(data);

    for (size_t i = 0; i < data.getSize() - 1; i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < data.getSize(); j++) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(data[i], data[minIndex]);
        }
    }
}

void SortCommand::undo()
{
    if (snapshot) {
        for (size_t i = 0; i < snapshot->getSize(); i++)
        {
            data[i] = (*snapshot)[i];
        }
    }
    delete snapshot;
    snapshot = nullptr;
}

VectorCommand* SortCommand::clone() const
{
    return new SortCommand(*this);
}
