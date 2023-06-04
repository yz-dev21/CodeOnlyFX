#include "cofx/cofx.hpp"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

int main()
{
	auto window = co::Window(800, 600, "FlappyBird");
	// Set window vsync
	window.SetVsync(true);

	// Load assets from json data.
	co::Assets::Load("../../DemoGame/Assets/assets.json");
	// Get flappy bird spritesheet.
	auto& flappyBirdSheet = co::Assets::Get<co::Texture>("flappyBird");
	flappyBirdSheet.GenerateMipmap();

	// Get first sprite of the spritesheet.
	auto flappyBird = co::Texture(flappyBirdSheet, { 16, 16 }, { 0, 0 });

	auto renderer = co::Renderer(window);

	// For deltatime.
	co::Timer timer;
	// Game loop
	while (window.IsRunning())
	{
		timer.Tick();

		// Clear graphics and fills screen with given color.
		window.Clear({ 79, 98, 128 });

		renderer.Draw(flappyBird, { 200.f, 200.f }, { 96.f, 96.f }, co::Color::White, 0.f);

		// Get events & swap buffers
		window.Update();

		timer.Reset();
	}
}

/*
TODO
- Change design more library-like.
*/