#include "LayerStack.h"

namespace Light {

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
		LT_ENGINE_TRACE("LayerStack::PushLayer: Attached [{}]", layer->GetName());
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		m_Layers.erase(std::find(m_Layers.begin(), m_Layers.end(), layer));
		LT_ENGINE_TRACE("LayerStack::PushLayer: Detatched[{}]", layer->GetName());
	}

}