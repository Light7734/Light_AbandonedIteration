#pragma once

#include "Base/Base.hpp"
#include "Scene/Entity.hpp"

namespace Light {

class NativeScript
{
	friend class Scene;

private:
	Entity m_Entity;
	unsigned int m_UniqueIdentifier = 0; // :#todo

public:
	NativeScript()          = default;
	virtual ~NativeScript() = default;

	inline unsigned int GetUID() const { return m_UniqueIdentifier; }

	template<typename T>
	T& GetComponent()
	{
		return m_Entity.GetComponent<T>();
	}

protected:
	virtual void OnCreate() {}
	virtual void OnDestroy() {}
	virtual void OnUpdate(float ts) {}
};

} // namespace Light
