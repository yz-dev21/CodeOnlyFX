#pragma once

#include "../glm/vec2.hpp"
#include <vector>
#include <span>

namespace co
{
	// Simple struct containing size and data of an image.
	struct Image
	{
		glm::uvec2 Size = { 0, 0 };
		std::vector<uint32_t> Data;

		inline Image() { }
		inline Image(uint32_t width, uint32_t height, std::span<uint32_t> rawImage) : Size(width, height)
		{
			Data.assign(rawImage.begin(), rawImage.end());
		}
	};
}