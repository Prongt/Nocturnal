#include "NocturnalPrecompiledHeaders.h"
#include "LayerStack.h"

namespace Nocturnal
{
	LayerStack::LayerStack()
	{
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
		Layers.emplace(Layers.begin()+ LayerInsertIndex, layer);
		LayerInsertIndex++;
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
			LayerInsertIndex--;
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