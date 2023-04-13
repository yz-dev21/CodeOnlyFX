#include "Core/Assets.h"
#include "Core/Debug.h"
#include "Graphics/Texture.h"
#include "Graphics/Shader.h"
#include <rapidjson/document.h>
#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace rapidjson;

static std::string GetText(std::string_view file)
{
	std::string text;
	try
	{
		std::ifstream f(file.data());

		std::stringstream stream;
		stream << f.rdbuf();

		f.close();

		text = stream.str();
	}
	catch (std::ifstream::failure e)
	{
		CO_ERROR("cofx::Core::Assets; Failed to read text: {}", e.what());
		return nullptr;
	}
	return text;
}
static void GetImage(std::string_view file, int& width, int& height, std::vector<unsigned char>& image)
{
	int nrChannels;

	unsigned char* data = stbi_load(file.data(), &width, &height, &nrChannels, STBI_rgb_alpha);
	if (!data)
		return;
	image.assign(data, data + width * height * STBI_rgb_alpha);

	stbi_image_free(data);
}

namespace co
{
	void Assets::Load(std::string_view assetsPath)
	{
		Document doc;
		doc.Parse(GetText(assetsPath).c_str());

		for (auto& object : doc["assets"].GetArray())
		{
			int type = object["type"].GetInt();

			switch (type)
			{
			case 1:
			{
				m_Assets<Shader>[object["name"].GetString()] = std::make_unique<Shader>();
				auto& shader = *m_Assets<Shader>[object["name"].GetString()];

				std::string shaderCode;

				if (object.HasMember("vertex"))
				{
					shaderCode = GetText(object["vertex"].GetString());
					shader.Attach(shaderCode, ShaderType::Vertex);
				}
				if (object.HasMember("fragment"))
				{
					shaderCode = GetText(object["fragment"].GetString());
					shader.Attach(shaderCode, ShaderType::Fragment);
				}
				if (object.HasMember("geometry"))
				{
					shaderCode = GetText(object["geometry"].GetString());
					shader.Attach(shaderCode, ShaderType::Geometry);
				}
				break;
			}
			case 2:
			{
				int width, height;
				std::vector<unsigned char> image;

				GetImage(object["file"].GetString(), width, height, image);

				m_Assets<Texture>[object["name"].GetString()] = std::make_unique<Texture>(width, height, image);
				break;
			}
			}
		}
	}
}