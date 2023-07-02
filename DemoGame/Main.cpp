#include "cofx/cofx.hpp"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

int main()
{
	co::Debug::Active = true;

	auto window = co::Window(800, 600, "FlappyBird");
	// Set window vsync
	window.SetVsync(true);

	// Load assets from json data.
	co::Assets::Load("../../DemoGame/Assets/assets.json");
	// Get flappy bird spritesheet.
	auto& flappyBirdSheet = co::Assets::Get<co::Image>("flappyBird");
	auto flappyBird = co::Texture(flappyBirdSheet);

	auto renderer = co::Renderer();

	// Game loop
	while (window.IsRunning())
	{
		// Clear graphics and fills screen with given color.
		window.Clear({ 79, 98, 128 });

		renderer.Draw(flappyBird, { 200.f, 200.f }, flappyBird.GetImage().Size, co::Color::White, 0.f);

		// Get events & swap buffers
		window.Update();
	}
}