#pragma once

#include "ServiceProvider/Service.h"

#include <unordered_map>
#include <vector>
#include <queue>
#include <typeindex>

#include "Event.h"

using namespace std;

namespace WaveEngine
{
	class EventSystem : public Service
	{
	private:

		struct Subscriber
		{
			void* instance = nullptr;
			void* method = nullptr;
			void (*invoke)(void*, void*, const void*);
		};

		unordered_map<type_index, vector<Subscriber>> subscribers;
		unordered_map<type_index, queue<Event*>> events;

	public:

		inline EventSystem() : Service()
		{
		}

		inline ~EventSystem()
		{
		}

		template<typename TEvent>
		void Subscribe(void(*func)(const TEvent&))
		{
			type_index eventType = typeid(TEvent);

			events[eventType];

			Subscriber sub;

			sub.instance = nullptr;
			sub.method = reinterpret_cast<void*>(func);

			sub.invoke =
				[](void*, void* m, const void* event)
				{
					void(*funcPtr)(const TEvent&) = reinterpret_cast<void(*)(const TEvent&)>(m);

					const TEvent* e = static_cast<const TEvent*>(event);

					funcPtr(*e);
				};

			subscribers[eventType].push_back(sub);
		}

		template<typename TObject, typename TEvent>
		void Subscribe(TObject* instance, void(TObject::* method)(const TEvent&))
		{
			type_index eventType = typeid(TEvent);

			events[eventType];

			Subscriber sub;

			sub.instance = instance;
			sub.method = *(void**)&method;

			sub.invoke =
				[](void* obj, void* m, const void* event)
				{
					TObject* o = static_cast<TObject*>(obj);

					void(TObject:: * methodPtr)(const TEvent&) = *(void(TObject::**)(const TEvent&)) & m;

					const TEvent* e = static_cast<const TEvent*>(event);

					(o->*methodPtr)(*e);
				};

			subscribers[eventType].push_back(sub);
		}

		template<typename TObject, typename TEvent>
		void Unsubscribe(void(*func)(const TEvent&))
		{
			vector<Subscriber>& vec = subscribers[typeid(TEvent)];

			void* m = *(void**)&func;

			vec.erase(
				remove_if(vec.begin(), vec.end(),
					[&](const Subscriber& s)
					{
						return s.instance == nullptr && s.method == m;
					}),
				vec.end()
			);
		}

		template<typename TObject, typename TEvent>
		void Unsubscribe(TObject* instance, void(TObject::* method)(const TEvent&))
		{
			vector<Subscriber>& vec = subscribers[typeid(TEvent)];

			void* m = *(void**)&method;

			vec.erase(
				remove_if(vec.begin(), vec.end(),
					[&](const Subscriber& s)
					{
						return s.instance == instance && s.method == m;
					}),
				vec.end()
			);
		}

		template<typename TEvent, typename... T>
		void Invoke(T... data)
		{
			type_index eventType = typeid(TEvent);

			queue<Event*>& queue = events.at(eventType);

			TEvent* event;

			if (!queue.empty())
			{
				event = static_cast<TEvent*>(queue.front());
				queue.pop();
			}
			else
			{
				event = new TEvent();
			}

			*event = TEvent{ data... };

			for (Subscriber& s : subscribers[eventType])
				s.invoke(s.instance, s.method, event);

			event->Reset();

			queue.push(event);
		}
	};
}