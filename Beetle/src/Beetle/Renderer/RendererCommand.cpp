#include "btpch.h"
#include "RendererCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Beetle {

	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;
}