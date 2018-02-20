#pragma once
#include <glm\glm.hpp>
#include "Renderer.h"
class Renderer;



class Helper
{
public:
	Helper();
	~Helper();
	static std::vector<char> readFile(const std::string& filename);
	
};

