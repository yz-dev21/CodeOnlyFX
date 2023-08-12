#include <cofx/cofx.hpp>

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
	auto flappyBird = co::Texture(flappyBirdSheet, 16, { 0, 0 });

	//auto& reversed = co::Assets::Get<co::Shader>("reversed");

	glm::vec2 pos = { 0.f, 0.f };

	auto sprite = co::SpriteRenderer();

	// Game loop
	while (window.IsRunning())
	{
		window.Clear({ 79, 98, 128 });

		sprite.Draw(flappyBird, pos);

		if (co::Keyboard::IsKeyPressed(co::Key::Escape))
			window.Close();

		if (co::Keyboard::IsKeyDown(co::Key::A))
			pos.x -= 5.f;
		if (co::Keyboard::IsKeyDown(co::Key::D))
			pos.x += 5.f;
		if (co::Keyboard::IsKeyDown(co::Key::W))
			pos.y -= 5.f;
		if (co::Keyboard::IsKeyDown(co::Key::S))
			pos.y += 5.f;

		// Get events & swap buffers
		window.Update();
	}
}
/*
DrawString
MouseInput
ImGUI
Physics
*/