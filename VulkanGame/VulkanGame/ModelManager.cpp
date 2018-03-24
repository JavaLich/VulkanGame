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

void ModelManager::addModel(const std::string modelPath, const std::string texturePath, uint32_t instanceCount)
{
	VmaAllocation imageMemory;
	VkImage image = renderer->createTextureImage(texturePath, &imageMemory);
	VkImageView imageView = renderer->createImageView(image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT);
	Material *mat = new Material(image, imageView);
	mat->imageMemory = imageMemory;
	models.push_back(Model(bufferSize, modelPath, mat, instanceCount));
	bufferSize += models.at(models.size()-1).modelSizeBytes;
}

void ModelManager::addModel(const std::string modelPath, Material * mat, uint32_t instanceCount)
{
	models.push_back(Model(bufferSize, modelPath, mat, instanceCount));
	bufferSize += models.at(models.size() - 1).modelSizeBytes;
}


void ModelManager::init(uint32_t numOfActors)
{
	if (bufferSize%Renderer::minUniformBufferOffsetAlignment==0) {
		firstUniformOffset = bufferSize;
		bufferSize += sizeof(UniformBufferObject);
	}
	else {
		firstUniformOffset = bufferSize + ((Renderer::minUniformBufferOffsetAlignment - (bufferSize) % Renderer::minUniformBufferOffsetAlignment));
		bufferSize = firstUniformOffset + sizeof(UniformBufferObject);
	}

	VkBuffer stagingBuffer;
	VmaAllocation stagingBufferMemory;
	VmaAllocationInfo stagingAllocInfo = {};
	std::vector<InstanceData> instanceData;

	renderer->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, stagingBuffer, stagingBufferMemory, VMA_MEMORY_USAGE_CPU_ONLY, stagingAllocInfo);
	for (Model model : models) {
		instanceData.resize(model.instanceCount);
		for (unsigned int i = 0; i < instanceData.size(); i++) {
			instanceData[i] = { {glm::mat4(1.0f)} };
		}
		memcpy(static_cast<char*>(stagingAllocInfo.pMappedData) + static_cast<size_t>(model.vertexOffset), model.vertices.data(), static_cast<size_t>(model.vertexSizeBytes));
		memcpy(static_cast<char*>(stagingAllocInfo.pMappedData) + static_cast<size_t>(model.indexOffset), model.indices.data(), static_cast<size_t>(model.indexSizeBytes));
		std::cout << "Buffer Size: " << bufferSize << ", Instance end: " << model.instanceDataOffset + sizeof(instanceData[0])*instanceData.size() << std::endl;
		memcpy(static_cast<char*>(stagingAllocInfo.pMappedData) + static_cast<size_t>(model.instanceDataOffset), instanceData.data(), sizeof(instanceData[0])*instanceData.size());
	}
	renderer->createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, buffer, bufferMemory, VMA_MEMORY_USAGE_CPU_TO_GPU, allocInfo);
	renderer->copyBuffer(stagingBuffer, buffer, bufferSize);
	vmaDestroyBuffer(renderer->allocator, stagingBuffer, stagingBufferMemory);
}

void ModelManager::updateInstances(VkDeviceSize offset, std::vector<InstanceData> instanceData)
{
	memcpy(static_cast<char*>(allocInfo.pMappedData) + static_cast<size_t>(offset), instanceData.data(), sizeof(instanceData[0])*instanceData.size());
}

void ModelManager::cleanup()
{
	vmaDestroyBuffer(renderer->allocator, buffer, bufferMemory);
	for (Model model : models) {
		if (!model.material->destroyed) {
			model.material->destroy(&renderer->allocator, &renderer->device);
		}
	}
	std::cout << "Cleaned up model manager" << std::endl;
}
