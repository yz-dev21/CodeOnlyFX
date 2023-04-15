#include "cofx/cofx.hpp"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

class DemoGame : public co::App
{
private:
	co::Shader* m_DefaultShader = nullptr;
	co::Texture* m_SoldierTex = nullptr;
protected:
	//Femto::ContextSettings SetupContext() override
	//{
	//	Femto::ContextSettings context;
	//	context.Debug = true;

	//	return context;
	//}
	void Initialize() override
	{
		co::Assets::Load("../../DemoGame/Assets/assets.json");

		m_DefaultShader = co::Assets::Get<co::Shader>("default");
		m_DefaultShader->Bind().SetUniform("image", 0);

		glm::mat4 projection = glm::ortho<float>(0.f, m_Window->GetSize().x, m_Window->GetSize().y, 0.f, -1.f, 1.f);
		m_DefaultShader->SetUniform("projection", projection);

		m_SoldierTex = new co::Texture(co::Assets::Get<co::Texture>("soldierSpriteSheet"), 48, 0, 0);
		m_SoldierTex->GenerateMipmap();

		co::Renderer::Initialize();
	}
	void Update(float dt) override
	{
	}
	void Render(float dt) override
	{
		m_Window->Clear(co::Color{ 79, 98, 128 });

		co::Renderer::Begin(m_DefaultShader);

		co::Renderer::Draw(m_SoldierTex, { 400.f - 24.f, 300.f - 24.f }, m_SoldierTex->GetSize(), co::Color::White, 0.f);
		co::Renderer::Draw({ 0.f, 0.f }, { 50.f, 50.f }, co::Color::Green, 0.f);

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