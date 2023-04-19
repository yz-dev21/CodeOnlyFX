#include "cofx/cofx.hpp"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

class DemoGame : public co::App
{
private:
	co::Shader* m_DefaultShader = nullptr;
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

		m_DefaultShader = co::Assets::Get<co::Shader>("default");
		m_DefaultShader->Bind().SetUniform("image", 0);

		glm::mat4 projection = glm::ortho<float>(0.f, m_Window->GetSize().x, m_Window->GetSize().y, 0.f, -1.f, 1.f);
		m_DefaultShader->SetUniform("projection", projection);

		m_SpriteSheet = co::Assets::Get<co::Texture>("flappyBird");
		m_FlappyBird = new co::Texture(m_SpriteSheet, { 16, 16 }, { 1, 0 });
		m_FlappyBird->GenerateMipmap();

		//co::Renderer::Initialize();
	}
	void Update(float dt) override
	{
	}
	void Render(float dt) override
	{
		m_Window->Clear(co::Color{ 79, 98, 128 });

		co::Renderer::Begin(m_DefaultShader);

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