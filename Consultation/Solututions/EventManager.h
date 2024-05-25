#pragma once
#include "Container.hpp"
#include "EventListener.h"
#include "EventResponse.h"

struct EventListenerFactory
{
	using RecordType = const char*;
	static EventListener* create(RecordType str);
};

struct EventResponseFactory
{
	using RecordType = const char*;
	static EventResponse* create(RecordType str);
};

class EventManager
{
private:
	Container<EventListener, EventListenerFactory> events;
	Container<EventResponse, EventResponseFactory> responses;
public:

	void addEventResponse(const char*);
	void addEventListener(const char*);
	void run();
};

