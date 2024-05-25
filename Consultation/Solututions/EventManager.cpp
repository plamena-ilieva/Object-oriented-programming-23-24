#include "EventManager.h"
#include "TimeEventListener.h"
#include "FileEventListener.h"
#include "ConsoleResponse.h"
#include "FileEventResponse.h"

void EventManager::addEventResponse(const char* str)
{
	responses.add(str);
}

void EventManager::addEventListener(const char* str)
{
	events.add(str);
}

void EventManager::run()
{
	while (true)
	{
		for (size_t i = 0; i < events.getSize(); i++)
		{
			const char* message = events[i]->check();
			if (message)
			{
				for (size_t j = 0; j < responses.getSize(); j++)
				{
					responses[j]->respond(message);
				}
			}
			delete[] message;
		}
	}
}

EventListener* EventListenerFactory::create(EventListenerFactory::RecordType str)
{
	if (str == nullptr)
		return nullptr;

	if (str[0] == 'f')
	{
		++str;
		return new FileEventListener(str);
	}
	else if (str[0] == 't')
	{
		++str;
		unsigned seconds = atoi(str);
		return new TimeEventListener(seconds);
	}

	return nullptr;
}

EventResponse* EventResponseFactory::create(EventResponseFactory::RecordType str)
{
	if (str == nullptr) return nullptr;

	if (str[0] == 's')
	{
		return new ConsoleResponse();
	}
	else if (str[0] == 'f')
	{
		++str;
		return new FileEventResponse(str);
	}
	return nullptr;
}
