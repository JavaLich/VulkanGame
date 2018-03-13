#include "Material.h"





Material::~Material()
{
	
}

void Material::destroy(VmaAllocator * allocator, VkDevice * device)
{
	vmaDestroyImage(*allocator, image, imageMemory);
	vkDestroyImageView(*device, imageView, nullptr);
	destroyed = true;
}

