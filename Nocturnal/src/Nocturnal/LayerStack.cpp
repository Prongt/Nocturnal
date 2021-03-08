#include "NocturnalPrecompiledHeaders.h"
#include "LayerStack.h"

namespace Nocturnal
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : mLayers)
			delete layer;
	}

	/**
	 * \brief Pushes the layer to the middle of the layer stack between the last layer and the first overlay
	 */
	void LayerStack::PushLayer(Layer* layer)
	{
		mLayers.emplace(mLayers.begin()+ mLayerInsertIndex, layer);
		mLayerInsertIndex++;
		layer->OnAttach();
	}

	/**
	 * \brief Pushes the overlay to the end of the layer stack
	 */
	void LayerStack::PushOverlay(Layer* overlay)
	{
		mLayers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		const auto layerToRemove = std::find(mLayers.begin(), mLayers.begin() + mLayerInsertIndex, layer);
		if (layerToRemove != mLayers.end())
		{
			layer->OnDetach();
			mLayers.erase(layerToRemove);
			mLayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		const auto layerToRemove = std::find(mLayers.begin(), mLayers.begin() + mLayerInsertIndex, overlay);
		if (layerToRemove != mLayers.end())
		{
			overlay->OnDetach();
			mLayers.erase(layerToRemove);
		}
	}

	

}