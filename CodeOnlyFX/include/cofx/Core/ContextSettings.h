#pragma once

namespace co
{
	struct ContextSettings
	{
		unsigned int OpenGLMajorVersion = 3;
		unsigned int OpenGLMinorVersion = 3;
		unsigned int FrameRate = 30;
		bool Debug = true;
	};
}