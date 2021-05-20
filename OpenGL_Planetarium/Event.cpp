#include "Event.h"

void EventQueue::Clear()
{
	while (!m_Queue.empty())
		m_Queue.pop();
}

void EventQueue::AddEvent(Event e)
{
	m_Queue.push(e);
}

bool EventQueue::Empty()
{
	return m_Queue.empty();
}

Event EventQueue::Pop()
{
	Event e = m_Queue.front();
	m_Queue.pop();

	return e;
}

/*
void EventQueue::AddEvent(Event&& e)
{
	
}
*/