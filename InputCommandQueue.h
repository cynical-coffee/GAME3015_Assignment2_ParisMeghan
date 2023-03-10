#pragma once
#include <queue>
#include "Command.h"

class InputCommandQueue
{
public:

	void push(const Command& command);
	Command pop();
	bool isEmpty() const;

private:
	std::queue<Command> mQueue;
};

