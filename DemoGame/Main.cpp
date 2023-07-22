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
	auto flappyBird = co::Texture(flappyBirdSheet);

	auto& reversed = co::Assets::Get<co::Shader>("reversed");
	reversed.Bind().SetUniform("image", 0);

	glm::vec2 pos = { 0.f, 0.f };

	// Game loop
	while (window.IsRunning())
	{
		// Clear graphics and fills screen with given color.
		window.Clear({ 79, 98, 128 });

		//co::Renderer::Begin(&reversed);
		co::Renderer::Begin(&reversed);

		/* method 1: */ //co::Renderer::Draw(flappyBird, pos, flappyBird.GetImage().Size, co::Color::White, 0.f);
		/* method 2: */ flappyBird.Draw(pos);

		co::Renderer::End();

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
Move glm to external.
Think more about custom shaders.
*/