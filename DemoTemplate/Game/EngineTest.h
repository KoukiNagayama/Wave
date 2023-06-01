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
	nsDemoEngine::ModelRender		m_modelRender;					// ���f�������_�[�B
	Vector3							m_pos = Vector3::Zero;			// ���W�B
	Vector3							m_sca = Vector3::One;			// �g�嗦�B
	Quaternion						m_rot = Quaternion::Identity;	// ��]�B
};

