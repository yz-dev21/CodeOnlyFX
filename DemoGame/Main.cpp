#include "cofx/cofx.hpp"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

class DemoGame : public co::App
{
private:
	co::SpriteBatch* m_Batch = nullptr;
	co::Shader* m_DefaultShader = nullptr;
	co::Texture* m_SoldierTex = nullptr;
	co::Texture* m_RedSoldierTex = nullptr;
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
		m_SoldierTex = co::Assets::Get<co::Texture>("soldier");
		m_RedSoldierTex = co::Assets::Get<co::Texture>("redSoldier");

		m_SoldierTex->GenerateMipmap();

		m_Batch = new co::SpriteBatch(m_Window.get());
		m_DefaultShader->Bind().SetUniform("image", 0);

		glm::mat4 projection = glm::ortho<float>(0.f, m_Window->GetSize().x, m_Window->GetSize().y, 0.f, -1.f, 1.f);
		m_DefaultShader->SetUniform("projection", projection);
	}
	void Update(float dt) override
	{
	}
	void Render(float dt) override
	{
		m_Window->Clear(co::Color{ 79, 98, 128 });

		m_Batch->Begin(m_DefaultShader);
		m_Batch->Draw(m_SoldierTex, { 200.f, 200.f }, { 240.f, 48.f }, co::Color::White, 0.f);
		m_Batch->Draw(m_RedSoldierTex, { 200.f, 250.f }, { 240.f, 48.f }, co::Color::White, 0.f);
		m_Batch->End();
	}
	void Cleanup() override
	{
	}
};
int main()
{
	DemoGame().Run();
}