#include "LayerStack.h"

#include "Layer.h"

#include "Events/Event.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/WindowEvents.h"

namespace Light {

	LayerStack* LayerStack::s_Context = nullptr;

	Scope<LayerStack> LayerStack::Create()
	{
		return MakeScope<LayerStack>(new LayerStack());
	}

	LayerStack::LayerStack()
		: m_Layers{},
		  m_Begin(),
		  m_End()
	{
		LT_ENGINE_ASSERT(!s_Context, "LayerStack::LayerStack: an instance of 'LayerStack' already exists, do not construct this class!")
		s_Context = this;
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::AttachLayerImpl(Layer* layer)
	{
		// #todo: handle attaching layer inside a for loop
		m_Layers.push_back(layer);
		m_Begin = m_Layers.begin();
		m_End = m_Layers.end();

		LT_ENGINE_TRACE("LayerStack::PushLayer: Attached [{}]", layer->GetName());
	}

	void LayerStack::DetachLayerImpl(Layer* layer)
	{
		// #todo: handle detaching layer inside a for loop
		m_Layers.erase(std::find(m_Layers.begin(), m_Layers.end(), layer));
		m_Begin = m_Layers.begin();
		m_End = m_Layers.end();

		LT_ENGINE_TRACE("LayerStack::PushLayer: Detached[{}]", layer->GetName());
	}

}