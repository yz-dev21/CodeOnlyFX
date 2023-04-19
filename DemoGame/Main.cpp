#include "cofx/cofx.hpp"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

class DemoGame : public co::App
{
private:
	co::Texture* m_SpriteSheet = nullptr;
	co::Texture* m_FlappyBird = nullptr;
protected:
	//Femto::ContextSettings SetupContext() override
	//{
	//	Femto::ContextSettings context;
	//	context.Debug = true;

	//	return context;
	//}
	void Initialize() override
	{
		m_Window->SetTitle("FlappyBird");

		co::Assets::Load("../../DemoGame/Assets/assets.json");

		m_SpriteSheet = co::Assets::Get<co::Texture>("flappyBird");

		m_FlappyBird = new co::Texture(m_SpriteSheet, { 16, 16 }, { 0, 0 });
		m_FlappyBird->GenerateMipmap();

		co::Renderer::Initialize(*m_Window);
	}
	void Update(float dt) override
	{
	}
	void Render(float dt) override
	{
		m_Window->Clear(co::Color{ 79, 98, 128 });

		co::Renderer::Begin();

		co::Renderer::Draw(m_FlappyBird, { 200.f, 200.f }, { 96.f, 96.f }, co::Color::White, 0.f);

		co::Renderer::End();
	}
	void Cleanup() override
	{
	}
};
int main()
{
	DemoGame().Run();
}