#pragma once

#include <cstddef>
#include <queue>

struct Event {

		enum class EventType { Pause, Scroll, MouseDrag };

		EventType Type;
		float p1;
		float p2;

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