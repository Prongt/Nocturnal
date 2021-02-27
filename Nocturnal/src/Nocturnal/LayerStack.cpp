#include "NocturnalPrecompiledHeaders.h"
#include "LayerStack.h"

namespace Nocturnal
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : _Layers)
			delete layer;
	}

	/**
	 * \brief Pushes the layer to the middle of the layerstack between the last layer and the first overlay
	 */
	void LayerStack::PushLayer(Layer* layer)
	{
		_Layers.emplace(_Layers.begin()+ _LayerInsertIndex, layer);
		_LayerInsertIndex++;
		layer->OnAttach();
	}

	/**
	 * \brief Pushes the overlay to the end of the layer stack
	 */
	void LayerStack::PushOverlay(Layer* overlay)
	{
		_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		const auto layerToRemove = std::find(_Layers.begin(), _Layers.begin() + _LayerInsertIndex, layer);
		if (layerToRemove != _Layers.end())
		{
			layer->OnDetach();
			_Layers.erase(layerToRemove);
			_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		const auto layerToRemove = std::find(_Layers.begin(), _Layers.begin() + _LayerInsertIndex, overlay);
		if (layerToRemove != _Layers.end())
		{
			overlay->OnDetach();
			_Layers.erase(layerToRemove);
		}
	}

	

}