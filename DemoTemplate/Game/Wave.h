#pragma once
class Wave : public IGameObject
{
public:
	Wave() {}
	~Wave() {}
	/// <summary>
	/// �g�̏ڍ�
	/// </summary>
	struct WaveDetail
	{
		float	m_length = 0.0f;				// ����(���f���̃T�C�Y�ɂ���ĕϓ�)		
		float	m_sharpness = 0.0f;				// �s��(0.0�`1.0)		
		float	m_height = 0.0f;				// ����(0.0�`1.0)
		float	m_pad1;
		Vector2	m_direction = Vector2::Zero;	// ����
		float	m_pad2;
		float	m_pad3;
	};
	/// <summary>
	/// �g�̒萔�o�b�t�@�p�\����
	/// </summary>
	struct WaveCb
	{
		float		m_deltaTime = 0.0f;		// �o�ߎ���
		Vector3		m_pad;
		WaveDetail	m_waveDetail[4];		// �g�̏ڍ�
		int			m_isGenerateRipple = 0;	// �g��𐶐����邩
		Vector3		m_ripplePos = Vector3::Zero;	// �g��̍��W
	};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	nsDemoEngine::ModelRender		m_modelRender;					// ���f�������_�[�B
	Vector3							m_pos = Vector3::Zero;			// ���W�B
	Vector3							m_sca = Vector3::One;			// �g�嗦�B
	Quaternion						m_rot = Quaternion::Identity;	// ��]�B
	WaveCb							m_waveCb;
	float							m_timerToRippleGenerate = 0.0f;
};

