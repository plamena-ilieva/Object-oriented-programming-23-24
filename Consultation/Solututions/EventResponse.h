#pragma once
class EventResponse
{
public:
	virtual void respond(const char* message) const = 0;
	virtual EventResponse* clone() const = 0;
	virtual ~EventResponse() = default;
};

