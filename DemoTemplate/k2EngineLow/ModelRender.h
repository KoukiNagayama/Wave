#pragma once

using namespace nsK2EngineLow;

/// <summary>
/// 技術デモ用エンジンの名前空間。
/// </summary>
namespace nsDemoEngine
{

	/// <summary>
	/// モデルレンダークラス。
	/// </summary>
	class ModelRender
	{
	public:
		/// <summary>
		/// コンストラクタ。
		/// </summary>
		ModelRender() {}
		/// <summary>
		/// デストラクタ。
		/// </summary>
		~ModelRender() {}

	public:
		/// <summary>
		/// モデルの初期化。
		/// </summary>
		/// <param name="filePath">tkmファイルパス。</param>
		/// <param name="animationClips">アニメーションクリップのアドレス。</param>
		/// <param name="numAnimationClips">アニメーションクリップの数。</param>
		/// <param name="enModelUpAxis">モデルの上方向。</param>
		void Init(const char* filePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ
		);
		/// <summary>
		/// 特殊なフォワードレンダリング用モデルの初期化関数。
		/// </summary>
		/// <param name="modelInitData"></param>
		void InitDirectlyNotifyForwardRendering(ModelInitData modelInitData);
		/// <summary>
		/// モデルの更新。
		/// </summary>
		void Update();
		/// <summary>
		/// モデルの描画。
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト。</param>
		void Draw(RenderContext& rc);
		/// <summary>
		/// アニメーション再生。
		/// </summary>
		/// <param name="animNo">アニメーションの番号。</param>
		/// <param name="interpolateTime">補間時間。</param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}
		/// <summary>
		/// アニメーションが再生中かどうか
		/// </summary>
		/// <returns>trueが返れば再生中。</returns>
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}
		/// <summary>
		/// アニメーションの再生速度を設定。
		/// </summary>
		/// <param name="animationSpeed">アニメーションの再生速度。</param>
		void SetAnimaitonSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}
		/// <summary>
		/// 座標、回転、拡大率を設定。
		/// </summary>
		/// <param name="pos">座標。</param>
		/// <param name="rot">回転。</param>
		/// <param name="sca">拡大率。</param>
		void SetTRS(const Vector3& pos, const Quaternion& rot, const Vector3& sca)
		{
			SetPosition(pos);
		}
		/// <summary>
		/// 座標を設定。
		/// </summary>
		/// <param name="pos">座標。</param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// 座標を設定。
		/// </summary>
		/// <param name="x">X座標。</param>
		/// <param name="y">Y座標。</param>
		/// <param name="z">Z座標。</param>
		void SetPosition(const float& x, const float& y, const float& z)
		{
			SetPosition({ x, y, z });
		}
		/// <summary>
		/// 回転を設定。
		/// </summary>
		/// <param name="rot">回転。</param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// 拡大率を設定。
		/// </summary>
		/// <param name="sca">拡大率。</param>
		void SetScale(const Vector3& sca)
		{
			m_scale = sca;
		}
		/// <summary>
		/// 拡大率を設定。
		/// </summary>
		/// <param name="x">X方向への拡大率。</param>
		/// <param name="y">Y方向への拡大率。</param>
		/// <param name="z">Z方向への拡大率。</param>
		void SetScale(const float& x, const float& y, const float& z)
		{
			SetScale({ x, y, z });
		}

	private:
		/// <summary>
		/// スケルトンを初期化。
		/// </summary>
		/// <param name="filePath">tkmファイルパス。</param>
		void InitSkeleton(const char* filePath);
		/// <summary>
		/// アニメーションを初期化。
		/// </summary>
		/// <param name="animationClips">アニメーションクリップのアドレス。</param>
		/// <param name="numAnimationClips">アニメーションクリップの数。</param>
		void InitAnimation(AnimationClip* animationClips, int numAnimationClips);
	private:
		Model					m_model;									// フォワードで描画されるモデル。
		Skeleton				m_skeleton;									// スケルトン。
		Animation				m_animation;								// アニメーション。
		AnimationClip*			m_animationClips = nullptr;					// アニメーションクリップ。
		int						m_numAnimationClips = 0;
		Vector3					m_position = Vector3::Zero;					// 座標。
		Quaternion				m_rotation = Quaternion::Identity;			// 回転。
		Vector3					m_scale = Vector3::One;						// 拡大率。
		float					m_animationSpeed = 1.0f;					// アニメーションの再生速度倍率。
	};
}


