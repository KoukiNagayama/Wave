#pragma once

using namespace nsK2EngineLow;

/// <summary>
/// 技術デモ用エンジンの名前空間。
/// </summary>
namespace nsDemoEngine
{
	/// <summary>
	/// レンダリングエンジンクラス。
	/// </summary>
	class RenderingEngine
	{
	private:
		/// <summary>
		/// コンストラクタ。
		/// </summary>
		RenderingEngine();
		/// <summary>
		/// デストラクタ。
		/// </summary>
		~RenderingEngine();
	public:
		/// <summary>
		/// 実行。
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト。</param>
		void Execute(RenderContext& rc);
		/// <summary>
		/// フォワードレンダリングの描画パスにモデルを追加。
		/// </summary>
		/// <param name="model"></param>
		void Add3DModelToForwardRenderPass(Model& model)
		{
			m_forwardRenderingModels.push_back(&model);
		}

	public:
		/// <summary>
		/// インスタンスを生成。
		/// </summary>
		static void CreateInstance()
		{
			m_instance = new RenderingEngine;
		};
		/// <summary>
		/// インスタンスを破棄。
		/// </summary>
		static void DeleteInstance()
		{
			if (m_instance) {
				delete m_instance;
			}
		}
		/// <summary>
		/// インスタンスを参照。
		/// </summary>
		static RenderingEngine* GetInstance()
		{
			return m_instance;
		}

	private:
		/// <summary>
		/// メインレンダリングターゲットを初期化。
		/// </summary>
		void InitMainRenderTarget();
		/// <summary>
		/// メインレンダリングターゲットの内容をフレームバッファにコピーするためのスプライトを初期化。
		/// </summary>
		void InitCopyMainRenderTargetToFrameBufferSprite();
		/// <summary>
		/// フォワードレンダリング。
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト。</param>
		void ForwardRendering(RenderContext& rc);
		/// <summary>
		/// メインレンダリングターゲットの内容をフレームバッファにコピーする。
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト。</param>
		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);
	private:
		RenderTarget				m_mainRenderTarget;					// メインレンダリングターゲット。
		Sprite						m_copyMainRtToFrameBufferSprite;	// メインレンダリングターゲットの内容をフレームバッファにコピーするためのスプライト。
		std::vector<Model*>			m_forwardRenderingModels;			// フォワードレンダリングをするモデル。
	private:
		static RenderingEngine*		m_instance;							// 唯一のインスタンス。

	};
}


