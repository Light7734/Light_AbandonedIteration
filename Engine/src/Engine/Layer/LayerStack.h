#pragma once

#include "Base.h"

#include "Layer.h"

#include <vector>

namespace Light {

	class LayerStack
	{
	private:
		std::vector<Layer*> m_Layers;

	public:
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	};

}