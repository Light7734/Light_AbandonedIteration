#pragma once

#include "Base.h"

#include "Layer.h"

#include "Events/Event.h"

#include <vector>

namespace Light {

	class LayerStack
	{
	private:
		static LayerStack* s_Context;

		std::vector<Layer*> m_Layers;

		std::vector<Layer*>::iterator m_Begin;
		std::vector<Layer*>::iterator m_End;
		
	public:
		LayerStack();
		~LayerStack();

		static inline void AttachLayer(Layer* layer) { s_Context->AttachLayerImpl(layer); }
		static inline void DetatchLayer(Layer* layer) { s_Context->DetatchLayerImpl(layer); }

		void OnUpdate(float deltaTime);
		void OnUserInterfaceUpdate();

		void OnEvent(const Event& event);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		void AttachLayerImpl(Layer* layer);
		void DetatchLayerImpl(Layer* layer);

	};

}