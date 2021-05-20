#pragma once

#include <cstddef>
#include <queue>

struct Event {

		enum class EventType { Pause, ScrollUp, ScrollDown, MouseDrag };

		EventType Type;
		std::byte  Parameters[16];

};

class EventQueue {

public:

	void Clear();
	bool Empty();
	
	void  AddEvent(Event e);
	Event Pop();
		
	//void AddEvent(Event&& e);


private:
	
	std::queue<Event> m_Queue;
};