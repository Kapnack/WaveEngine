#pragma once

#include "ServiceProvider/Service.h"

#include <unordered_map>
#include <vector>
#include <functional>
#include <typeindex>

#include "Export.h"

using namespace std;

namespace WaveEngine
{
	struct Event
	{

	};

	struct Subscriber
	{
		void* instance = nullptr;
		void* method = nullptr;
		function<void(const void*)> callback;
	};

	class EventSystem : public Service
	{
	private:

		unordered_map<type_index, vector<Subscriber>> subscribers;

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
			Subscriber sub;

			sub.instance = nullptr;
			sub.method = reinterpret_cast<void*>(func);

			sub.callback =
				[func](const void* event)
				{
					const TEvent* e = static_cast<const TEvent*>(event);
					func(*e);
				};

			subscribers[typeid(TEvent)].push_back(sub);
		}

		template<typename TObject, typename TEvent>
		void Subscribe(TObject* instance, void(TObject::* method)(const TEvent&))
		{
			Subscriber sub;

			sub.instance = instance;
			sub.method = *(void**)&method;

			sub.callback =
				[instance, method](const void* event)
				{
					const TEvent* e = static_cast<const TEvent*>(event);
					(instance->*method)(*e);
				};

			subscribers[typeid(TEvent)].push_back(sub);
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

		template<typename TEvent>
		void Invoke(const TEvent& event)
		{
			for (Subscriber& s : subscribers[typeid(TEvent)])
				s.callback(&event);
		}
	};
}