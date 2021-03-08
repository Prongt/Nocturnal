#pragma once

#include "Nocturnal/Core.h"
#include "Layer.h"
#include <vector>

namespace Nocturnal
{
	class NOCTURNAL_API LayerStack
	{
	private:
		std::vector<Layer*> mLayers;
		unsigned int mLayerInsertIndex = 0;
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() {return mLayers.begin(); }
		std::vector<Layer*>::iterator end() {return mLayers.end(); }
	};
}
