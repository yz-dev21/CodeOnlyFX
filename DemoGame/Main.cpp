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
	auto& flappyBirdSheet = co::Assets::Get<co::Image>("flappyBird");

	auto renderer = co::Renderer(window.GetSize());

	std::vector<co::Texture> flappyBirdAnimation =
	{
		co::Texture(flappyBirdSheet, 16, { 0, 0 }),
		co::Texture(flappyBirdSheet, 16, { 1, 0 }),
		co::Texture(flappyBirdSheet, 16, { 2, 0 }),
		co::Texture(flappyBirdSheet, 16, { 3, 0 }),
	};

	// For deltatime.
	co::Timer timer;

	int i = 0;
	// Game loop
	while (window.IsRunning())
	{
		timer.Tick();

		// Clear graphics and fills screen with given color.
		window.Clear({ 79, 98, 128 });

		renderer.Draw(flappyBirdAnimation[i], { 200.f, 200.f }, flappyBirdAnimation[i].GetImage().Size, co::Color::White, 0.f);

		// Get events & swap buffers
		window.Update();

		timer.Reset();
	}
}

/*
TODO
- Change design more library-like.
*/