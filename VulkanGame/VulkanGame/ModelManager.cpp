#include "ModelManager.h"
#include "Renderer.h"

Renderer* ModelManager::renderer;

ModelManager::ModelManager(Renderer* rend)
{
	renderer = rend;
	bufferSize = 0;
	allocInfo = {};
}


ModelManager::~ModelManager()
{
}

void ModelManager::addModel(const std::string modelPath)
{
	models.push_back(Model(bufferSize, modelPath));
	bufferSize += models.at(models.size()-1).modelSizeBytes;
}

void ModelManager::init()
{
	VkBuffer stagingBuffer;
	VmaAllocation stagingBufferMemory;
	VmaAllocationInfo stagingAllocInfo = {};

	renderer->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, stagingBuffer, stagingBufferMemory, VMA_MEMORY_USAGE_CPU_ONLY, stagingAllocInfo);
	for (Model model : models) {
		memcpy(static_cast<char*>(stagingAllocInfo.pMappedData) + static_cast<size_t>(model.vertexOffset), model.vertices.data(), static_cast<size_t>(model.vertexSizeBytes));
		memcpy(static_cast<char*>(stagingAllocInfo.pMappedData) + static_cast<size_t>(model.indexOffset), model.indices.data(), static_cast<size_t>(model.indexSizeBytes));
	}
	renderer->createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, buffer, bufferMemory, VMA_MEMORY_USAGE_CPU_TO_GPU, allocInfo);
	renderer->copyBuffer(stagingBuffer, buffer, bufferSize);
	vmaDestroyBuffer(renderer->allocator, stagingBuffer, stagingBufferMemory);
}

void ModelManager::cleanup()
{
	vmaDestroyBuffer(renderer->allocator, buffer, bufferMemory);
}
