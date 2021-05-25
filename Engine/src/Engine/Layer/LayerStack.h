#pragma once

#include "Base.h"

#include "Layer.h"

#include "Events/Event.h"

#include <vector>

namespace Light {

	class LayerStack
	{
	private:
		std::vector<Layer*> m_Layers;

		std::vector<Layer*>::iterator m_Begin;
		std::vector<Layer*>::iterator m_End;

		
	public:
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void OnEvent(const Event& event);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	};

}