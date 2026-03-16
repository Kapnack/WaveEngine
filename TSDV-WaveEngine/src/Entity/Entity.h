#pragma once

#include "Export.h"
#include "Renderer/Renderer.h"
#include "Component/Component.h"
#include "WaveMath/Vector3/Vector3.h"

#include <concepts>

#include <vector>
#include <unordered_map>

using namespace std;

namespace WaveEngine
{
	class EntityFactory;
	class EntityManager;
	class EntitiesImGui;
	class MeshImGui;
	class BaseGame;

	template<typename T>
	concept ComoponentConcept = derived_from<T, Component>;

	WAVEEXPORT class Entity
	{
	private:

		unsigned int ID = 0;

		bool isActive = true;
		bool shouldUpdateTRS = false;

		vector<Component*> components;
		unordered_map<type_index, unsigned int> componentsIndexByType;

		void Update();

		friend class EntityFactory;
		friend class EntityManager;
		friend class EntitiesImGui;
		friend class MeshImGui;
		friend class BaseGame;

	protected:

		Vector3 previousPosition;
		Vector3 position;

		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 rotation;

		glm::mat4 model;

		virtual void CalculateTRS();

		virtual void UpdateCollider() = 0;

		Entity(const unsigned int& ID);
		virtual ~Entity();

	public:

		static const unsigned int NULL_ENTITY = 0;

		WAVEEXPORT unsigned int GetID() const;

		WAVEEXPORT void SetIsActive(const bool& setActive);
		WAVEEXPORT bool GetIsActive() const;

		WAVEEXPORT Vector3 GetPosition() const;
		WAVEEXPORT Vector3 GetScale() const;
		WAVEEXPORT Vector3 GetRotation() const;

		WAVEEXPORT Vector3 GetPreviousPos() const;
		WAVEEXPORT void GoToPreviousPos();

		WAVEEXPORT void SetPosition(const Vector3& vector);
		WAVEEXPORT void SetPosition(const Vector2& translation);
		WAVEEXPORT void SetPosition(const float& x, const float& y);
		WAVEEXPORT virtual void SetPosition(const float& x, const float& y, const float& z);

		WAVEEXPORT void Translate(const Vector3& translation);
		WAVEEXPORT void Translate(const Vector2& translation);
		WAVEEXPORT void Translate(const float& x, const float& y);
		WAVEEXPORT virtual void Translate(const float& x, const float& y, const float& z);

		WAVEEXPORT void SetScale(const Vector3& vector);
		WAVEEXPORT void SetScale(const Vector2& translation);
		WAVEEXPORT void SetScale(const float& x, const float& y);
		WAVEEXPORT virtual void SetScale(const float& x, const float& y, const float& z);

		WAVEEXPORT void Scale(const Vector3& vector);
		WAVEEXPORT void Scale(const Vector2& translation);
		WAVEEXPORT void Scale(const float& x, const float& y);
		WAVEEXPORT virtual void Scale(const float& x, const float& y, const float& z);

		WAVEEXPORT void SetRotation(const Vector3& vector);
		WAVEEXPORT void SetRotation(const Vector2& vector);
		WAVEEXPORT void SetRotation(const float& x, const float& y);
		WAVEEXPORT virtual void SetRotation(const float& x, const float& y, const float& z);

		WAVEEXPORT void Rotate(const Vector3& vector);
		WAVEEXPORT void Rotate(const Vector2& vector);
		WAVEEXPORT void Rotate(const float& x, const float& y);
		WAVEEXPORT virtual void Rotate(const float& x, const float& y, const float& z);

		WAVEEXPORT void FlipX();
		WAVEEXPORT void FlipY();
		WAVEEXPORT void FlipZ();

		WAVEEXPORT virtual void Destroy();

		template<ComoponentConcept T>
		void AddComponent()
		{
			type_index type = typeid(T);

			if (componentsIndexByType.contains(type))
				return;

			T* newComponent = new T();

			newComponent->entity = this;

			components.push_back(newComponent);
			componentsIndexByType[type] = components.size() - 1;
		}

		template<ComoponentConcept T>
		void AddComponent(T* newComponent)
		{
			type_index type = typeid(T);

			if (componentsIndexByType.contains(type))
				return;

			T* newComponent = new T();

			newComponent->entity = this;

			components.push_back(newComponent);
			componentsIndexByType[type] = components.size() - 1;
		}

		template<ComoponentConcept T>
		T& GetComponent()
		{
			return components.at(componentsIndexByType.at(typeid(T)));
		}

		template<ComoponentConcept T>
		T* TryGetComponent()
		{
			unordered_map<type_index, unsigned int>::iterator it = componentsIndexByType.find(typeid(T));

			if (it == componentsIndexByType.end())
				return nullptr;

			return components.at(it->second);
		}

		template<ComoponentConcept T>
		bool TryGetComponent(T*& reference)
		{
			unordered_map<type_index, unsigned int>::iterator it = componentsIndexByType.find(typeid(T));

			if (it == componentsIndexByType.end())
				return false;

			reference = components.at(it->second);
			return true;
		}

		template<ComoponentConcept T>
		T& GetComponentAtIndex(const unsigned int& index)
		{
			return static_cast<T*>(components.at(index));
		}

		template<ComoponentConcept T>
		T* TryGetComponentAtIndex(const unsigned int& index)
		{
			if (index >= components.size())
				return nullptr;

			return static_cast<T*>(components.at(index));
		}

		int GetComponentsAmount()
		{
			return components.size();
		}

		template<ComoponentConcept T>
		void RemoveComponent()
		{
			type_index type = typeid(T);

			if (!componentsIndexByType.contains(type))
				return;

			const unsigned int index = componentsIndexByType.at(type);
			const unsigned int lastIndex = components.size() - 1;

			swap(components.at(index), components.at(lastIndex));

			componentsIndexByType.erase(type);

			delete components.at(lastIndex);
			components.pop_back();
		}
	};
}
