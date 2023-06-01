#pragma once
class EngineTest : public IGameObject
{
public:
	EngineTest() {}
	~EngineTest() {}

	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	nsDemoEngine::ModelRender		m_modelRender;					// モデルレンダー。
	Vector3							m_pos = Vector3::Zero;			// 座標。
	Vector3							m_sca = Vector3::One;			// 拡大率。
	Quaternion						m_rot = Quaternion::Identity;	// 回転。
};

