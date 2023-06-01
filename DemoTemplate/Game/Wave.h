#pragma once
class Wave : public IGameObject
{
public:
	Wave() {}
	~Wave() {}
	/// <summary>
	/// 波の詳細
	/// </summary>
	struct WaveDetail
	{
		float	m_length = 0.0f;				// 長さ(モデルのサイズによって変動)		
		float	m_sharpness = 0.0f;				// 鋭さ(0.0～1.0)		
		float	m_height = 0.0f;				// 高さ(0.0～1.0)
		float	m_pad1;
		Vector2	m_direction = Vector2::Zero;	// 方向
		float	m_pad2;
		float	m_pad3;
	};
	/// <summary>
	/// 波の定数バッファ用構造体
	/// </summary>
	struct WaveCb
	{
		float		m_deltaTime = 0.0f;		// 経過時間
		Vector3		m_pad;
		WaveDetail	m_waveDetail[4];		// 波の詳細
		int			m_isGenerateRipple = 0;	// 波紋を生成するか
		Vector3		m_ripplePos = Vector3::Zero;	// 波紋の座標
	};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	nsDemoEngine::ModelRender		m_modelRender;					// モデルレンダー。
	Vector3							m_pos = Vector3::Zero;			// 座標。
	Vector3							m_sca = Vector3::One;			// 拡大率。
	Quaternion						m_rot = Quaternion::Identity;	// 回転。
	WaveCb							m_waveCb;
	float							m_timerToRippleGenerate = 0.0f;
};

