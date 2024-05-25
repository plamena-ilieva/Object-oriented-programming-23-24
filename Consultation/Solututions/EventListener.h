#pragma once
class EventListener
{
public:
	virtual const char* check() = 0;
	virtual EventListener* clone() const = 0;
	virtual ~EventListener() = default;
};

