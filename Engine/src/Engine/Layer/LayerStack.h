#pragma once

#include "Base.h"

namespace Light {

	class Layer;
	class Event;

	class LayerStack
	{
	private:
		static LayerStack* s_Context;

		std::vector<Layer*> m_Layers;

		std::vector<Layer*>::iterator m_Begin;
		std::vector<Layer*>::iterator m_End;
		
	public:
		static Scope<LayerStack> Create();

		~LayerStack();

		// #todo: should we keep this?
		template<typename T, typename... Args>
		static inline void EmplaceLayer(Args&&... args) { s_Context->AttachLayerImpl(new T((args)...)); }

		static inline void AttachLayer(Layer* layer) { s_Context->AttachLayerImpl(layer); }
		static inline void DetachLayer(Layer* layer) { s_Context->DetachLayerImpl(layer); }

		inline bool IsEmpty() { return m_Layers.empty(); }

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

	private:
		LayerStack();

		void AttachLayerImpl(Layer* layer);
		void DetachLayerImpl(Layer* layer);
	};

}