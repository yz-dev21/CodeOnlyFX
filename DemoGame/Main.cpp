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
		m_Batch = new co::SpriteBatch();

		m_DefaultShader->Bind().SetUniform("image", 0);
	}
	void Update(float dt) override
	{
	}
	void Render(float dt) override
	{
		m_GraphicsDevice->Clear(co::Color::White);

		m_Batch->Begin(m_DefaultShader);
		m_Batch->Draw(m_SoldierTex, { 300, 200 }, co::Vec2f::Zero, co::Color::Black, 0.f);
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