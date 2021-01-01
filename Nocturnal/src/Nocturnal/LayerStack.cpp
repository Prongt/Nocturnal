#include "NocturnalPrecompiledHeaders.h"
#include "LayerStack.h"

namespace Nocturnal
{
	LayerStack::LayerStack()
	{
		LayerInsert = Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : Layers)
			delete layer;
	}

	/**
	 * \brief Pushes the layer to the middle of the layerstack between the last layer and the first overlay
	 */
	void LayerStack::PushLayer(Layer* layer)
	{
		LayerInsert = Layers.emplace(LayerInsert, layer);
	}

	/**
	 * \brief Pushes the overlay to the end of the layer stack
	 */
	void LayerStack::PushOverlay(Layer* overlay)
	{
		Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		const auto layerToRemove = std::find(Layers.begin(), Layers.end(), layer);
		if (layerToRemove != Layers.end())
		{
			Layers.erase(layerToRemove);
			--LayerInsert;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		const auto layerToRemove = std::find(Layers.begin(), Layers.end(), overlay);
		if (layerToRemove != Layers.end())
		{
			Layers.erase(layerToRemove);
		}
	}

	

}