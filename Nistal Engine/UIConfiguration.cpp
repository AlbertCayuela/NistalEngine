#include "Application.h"
#include "UIConfiguration.h"
#include "UIWindow.h"
#include "ImGui/imgui.h"

#include <gl/GL.h>
#include <gl/GLU.h>


using namespace ImGui;

UIConfiguration::UIConfiguration() : UIWindow()
{
	is_on = false;
}

UIConfiguration::~UIConfiguration()
{}

bool UIConfiguration::Start()
{
	bool ret = true;

	SDL_VERSION(&version);
	cpu_cache = SDL_GetCPUCacheLineSize();
	cpu_count = SDL_GetCPUCount();
	ram = SDL_GetSystemRAM() / 1000;

	return ret;
}

bool UIConfiguration::CleanUp()
{

	return true;
}

void UIConfiguration::Draw()
{
	GLint total_memory = 0;
	GLint memory_usage = 0;
	GLint dedicated_memory = 0;
	GLint available_memory = 0;

	//hardaware
	glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &total_memory);
	glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &available_memory);
	glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &dedicated_memory);
	memory_usage = total_memory - available_memory;


	Begin("Configuration", &is_on);
	SetNextWindowSize(ImVec2(370, 795), ImGuiCond_Once);
	SetWindowPos(ImVec2(0, 20), ImGuiCond_Once);
	
		if (TreeNode("Options"))
		{
			TreePop();
		}

		if (CollapsingHeader("Application"))
		{
			static char name[30] = "Nistal Engine";
			InputText("App Name",  name, ARRAYSIZE(name));
			App->window->SetTitle(name);
			static char organization[30] = "UPC CITM";
			InputText("Organization", organization, ARRAYSIZE(organization));

			if (vector_fps.size() != 100)
			{
				vector_fps.push_back(App->GetFPS());
				vector_ms.push_back(App->GetMS());
			}
			else
			{
				vector_fps.erase(vector_fps.begin());
				vector_fps.push_back(App->GetFPS());

				vector_ms.erase(vector_ms.begin());
				vector_ms.push_back(App->GetMS());
			}


			int zero = 0;
			Text("Framerate %.1f", vector_fps[vector_fps.size() - 1]);
			PlotHistogram("##framerate", &vector_fps[0], vector_fps.size(), 0, NULL, 0.0f, 100.0f, ImVec2(310, 100));
			Text("Milliseconds %.1f", vector_ms[vector_ms.size() - 1]);
			PlotHistogram("##milliseconds", &vector_ms[0], vector_ms.size(), 0, NULL, 0.0f, 40.0f, ImVec2(310, 100));
		}

		if (CollapsingHeader("3D Renderer"))
		{
			if (Checkbox("Depth test", &depth_test))
			{
				if (depth_test)
					glDisable(GL_DEPTH_TEST);
				else
					glEnable(GL_DEPTH_TEST);
			}
			if (Checkbox("Backface culling", &cull_face))
			{
				if (cull_face)
					glDisable(GL_CULL_FACE);
				else
					glEnable(GL_CULL_FACE);
			}
			if (Checkbox("Lightning", &lightning))
			{
				if (lightning)
					glDisable(GL_LIGHTING);
				else
					glEnable(GL_LIGHTING);
			}
			/*if (Checkbox("Color material", &color_material))
			{
				if (color_material)
					glDisable(GL_COLOR_MATERIAL);
				else
					glEnable(GL_COLOR_MATERIAL);
			}
			if (Checkbox("Texture 2D", &texture2D))
			{
				if (texture2D)
					glDisable(GL_TEXTURE_2D);					
				else
					glEnable(GL_TEXTURE_2D);
			}*/
			if (Checkbox("Wireframe", &wireframe)) 
			{
				if (wireframe)
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				else
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			//TODO: View Wireframe + Mesh
		}

		if (CollapsingHeader("Window"))
		{
			int values = 1.000;

			Text("Icon: *default*");

			if (SliderFloat("Brightness", &App->window->brightness, 0.0f, 1.0f))
			{
				SDL_SetWindowBrightness(App->window->window, App->window->brightness);
				SDL_UpdateWindowSurface(App->window->window);
			}


			if (SliderInt("Width", &App->window->width, 1, 2000) || SliderInt("Height", &App->window->height, 1, 2000))
			{
				SDL_SetWindowSize(App->window->window, App->window->width, App->window->height);
				SDL_UpdateWindowSurface(App->window->window);
			}

			if (Checkbox("Fullscreen", &App->window->fullscreen))
			{
				if (App->window->fullscreen)
					SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN);
				else
					SDL_SetWindowFullscreen(App->window->window, App->window->flags);
			}
			if (Checkbox("Borderless", &App->window->borderless))
			{
				SDL_SetWindowBordered(App->window->window, (SDL_bool)!App->window->borderless);
			}
			SameLine();
			if (Checkbox("Fullscreen Desktop", &App->window->fullscreen_desktop))
			{
				if (App->window->fullscreen_desktop)
					SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				else
					SDL_SetWindowFullscreen(App->window->window, App->window->flags);
			}
		}

		if (CollapsingHeader("File System"))
		{
			Text("Base Path:");
			TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "%s", SDL_GetBasePath());
			Text("Read Paths:");
			TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), ".");
			Text("Write Paths:");
			TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), ".");
		}

		if (CollapsingHeader("Input"))
		{
			Text("Mouse Position:");
			SameLine();
			TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "%i,%i", App->input->GetMouseX(), App->input->GetMouseY());
			Text("Mouse Motion:");
			SameLine();
			TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "%i,%i", App->input->GetMouseXMotion(), App->input->GetMouseYMotion());
			Text("Mouse Wheel:");
			SameLine();
			TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "%i", App->input->GetMouseZ());
			Separator();
			Text("Show Mouse Historial");
		}

		if (CollapsingHeader("Hardware"))
		{
			Text("SDL Version:");
			SameLine();
			TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "%d.%d.%d", version.major, version.minor, version.patch);
			Text("OpenGL version supported:");
			SameLine();
			TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "%s", glGetString(GL_VERSION));
			Text("GLSL:");
			SameLine();
			TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "%s", glGetString(GL_SHADING_LANGUAGE_VERSION));

			Separator();
			Text("CPUs:");
			SameLine();
			TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "%i (Cache:%ikb)", cpu_count, cpu_cache);
			Text("System RAM:");
			SameLine();
			TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "%iGb", ram);
			Text("Caps: ");
			SameLine();
			if (SDL_HasAVX)
				TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "AVX");
			SameLine();
			if (SDL_HasMMX)
				TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "MMX");
			SameLine();
			if (SDL_HasSSE)
				TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "SSE");
			SameLine();
			if (SDL_HasSSE2)
				TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "SSE2");
			SameLine();
			if (SDL_HasSSE3)
				TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "SSE3");
			SameLine();
			if (SDL_HasSSE41)
				TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "SSE4");
			SameLine();
			if (SDL_HasSSE42)
				TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "SSE42");
			SameLine();
			if (SDL_HasRDTSC)
				TextColored(ImVec4(1.0f, 1.0f, 0.5f, 1.0f), "RDTSC");

			Separator();
			Text("GPU:");
			SameLine();
			TextColored(ImVec4(1.0, 1.0f, 0.5f, 1.0f), "%s", glGetString(GL_VENDOR));
			Text("Brand:");
			SameLine();
			TextColored(ImVec4(1.0, 1.0f, 0.5f, 1.0f), "%s", glGetString(GL_RENDERER));
			Text("VRAM Budget:");
			SameLine();
			TextColored(ImVec4(1.0, 1.0f, 0.5f, 1.0f), "%.1f Mb", (total_memory * 0.001));
			Text("VRAM Usage:");
			SameLine();
			TextColored(ImVec4(1.0, 1.0f, 0.5f, 1.0f), "%.1f Mb", (memory_usage * 0.001));
			Text("VRAM Available:");
			SameLine();
			TextColored(ImVec4(1.0, 1.0f, 0.5f, 1.0f), "%.1f Mb", (available_memory * 0.001));
			Text("GPU:");
			SameLine();
			TextColored(ImVec4(1.0, 1.0f, 0.5f, 1.0f), "%.1f Mb", (dedicated_memory * 0.001));
		}

	ImGui::End();
}
	


