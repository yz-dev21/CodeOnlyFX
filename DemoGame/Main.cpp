#include "cofx/cofx.hpp"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

int main()
{
	auto window = co::Window(800, 600, "FlappyBird");
	// Set target frame rate
	window.SetFrameRate(60);

	// Load assets from json data.
	co::Assets::Load("../../DemoGame/Assets/assets.json");
	// Get flappy bird spritesheet.
	auto flappyBirdSheet = co::Assets::Get<co::Texture>("flappyBird");

	// Get first sprite of the spritesheet.
	auto flappyBird = co::Texture(*flappyBirdSheet, glm::vec2{ 16, 16 }, glm::vec2{ 0, 0 });
	flappyBird.GenerateMipmap();

	auto renderer = co::Renderer(window);

	// For deltatime.
	co::Timer timer;
	while (window.IsRunning())
	{
		timer.Tick();
		window.Clear(co::Color{ 79, 98, 128 });

		renderer.Draw(flappyBird, { 200.f, 200.f }, { 96.f, 96.f }, co::Color::White, 0.f);

		window.Update();
		timer.Reset();
	}
}

/*
TODO
- Change design more library-like.
- Implement math library for glm.
*/