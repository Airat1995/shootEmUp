#pragma once
#include "IWindow.h"
#include <SDL2/SDL.h>


namespace Engine::Window
{

	using namespace Engine::Render;

	class SDLWindow : public IWindow
	{
	public:	
		SDLWindow(int width, int height, const string& name, WindowType windowType, IRender* render);

		~SDLWindow() override;
		
		void SetWidth(int width) override;
		
		void SetHeight(int height) override;
		
		void SetName(string name) override;

		void UpdateWindow() const;

		SDL_Window* Window();

		void Update() override;

	protected:

		SDL_Window* _window;

		SDL_Surface* _surface;

		vector<const char*> GetExtensions() const;

	private:
		static Uint32 WindowTypeToSDLWindowFlags(WindowType windowType);
	};
}