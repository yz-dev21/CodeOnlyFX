#include "cofx/cofx.hpp"

class DemoGame : public co::App
{
private:
	co::SpriteBatch* m_Batch = nullptr;
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
		co::Assets::Load("Assets/assets.json");

		m_DefaultShader = co::Assets::Get<co::Shader>("default");
		m_SoldierTex = co::Assets::Get<co::Texture>("soldier");
		m_SoldierTex->GenerateMipmap();

		m_Batch = new co::SpriteBatch();
		m_DefaultShader->Bind().SetUniform("image", 0);

		co::Matrix projection;
		projection.Orthographic(0.f, m_Window->GetSize().X, m_Window->GetSize().Y, 0.f, -1.f, 1.f);
		m_DefaultShader->SetUniform("projection", projection);
	}
	void Update(float dt) override
	{
	}
	void Render(float dt) override
	{
		m_Window->Clear(co::Color{ 79, 98, 128 });

		m_Batch->Begin(m_DefaultShader);
		m_Batch->Draw(m_SoldierTex, { 300, 200 }, { 200, 48 }, co::Color::Green, 0.f);
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