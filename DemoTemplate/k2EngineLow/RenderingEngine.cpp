#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsDemoEngine
{
	RenderingEngine* RenderingEngine::m_instance = nullptr;
	
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	RenderingEngine::RenderingEngine()
	{

		// メインレンダリングターゲットを初期化。
		InitMainRenderTarget();

		// メインレンダリングターゲットの内容をフレームバッファにコピーするスプライトを初期化。
		InitCopyMainRenderTargetToFrameBufferSprite();

	}

	/// <summary>
	/// デストラクタ。
	/// </summary>
	RenderingEngine::~RenderingEngine()
	{

	}

	/// <summary>
	/// メインレンダリングターゲットを初期化。
	/// </summary>
	void RenderingEngine::InitMainRenderTarget()
	{
		// メインレンダリングターゲットを作成。
		m_mainRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),	// 縦幅はフレームバッファと同じ
			g_graphicsEngine->GetFrameBufferHeight(),	// 横幅はフレームバッファと同じ
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,				// カラーバッファはRGBA32bit浮動小数点型
			DXGI_FORMAT_D32_FLOAT						// デプスステンシルバッファはD32bit浮動小数点型						
		);
	}

	/// <summary>
	/// メインレンダリングターゲットの内容をフレームバッファにコピーするためのスプライトを初期化。
	/// </summary>
	void RenderingEngine::InitCopyMainRenderTargetToFrameBufferSprite()
	{
		// スプライトの初期化オブジェクト。
		SpriteInitData spriteInitData;

		// テクスチャはメインレンダリングターゲットのテクスチャ。
		spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();

		// 解像度はフレームバッファと同じ
		spriteInitData.m_width = g_graphicsEngine->GetFrameBufferWidth();
		spriteInitData.m_height = g_graphicsEngine->GetFrameBufferHeight();
	
		// シェーダーのファイルパスは基本的なスプライトのシェーダーのものを使用。
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
	
		// 初期化オブジェクトをもとにスプライトを初期化。
		m_copyMainRtToFrameBufferSprite.Init(spriteInitData);
	}

	/// <summary>
	/// 実行。
	/// </summary>
	/// <param name="rc">レンダリングコンテキスト。</param>
	void RenderingEngine::Execute(RenderContext& rc)
	{
		// フォワードレンダリング。
		ForwardRendering(rc);

		// メインレンダリングターゲットの内容をフレームバッファにコピーする。
		CopyMainRenderTargetToFrameBuffer(rc);

		// 登録していたモデルをクリアする。
		m_forwardRenderingModels.clear();
	}

	/// <summary>
	/// フォワードレンダリング。
	/// </summary>
	/// <param name="rc">レンダリングコンテキスト。</param>
	void RenderingEngine::ForwardRendering(RenderContext& rc)
	{
		// レンダリングターゲットとして利用可能になるまで待つ。
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);

		// レンダリングターゲットを設定する。
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);

		// レンダリングターゲットをクリアする。
		rc.ClearRenderTargetView(m_mainRenderTarget);

		// 描画
		for (auto& model : m_forwardRenderingModels) {
			model->Draw(rc);
		}

		// レンダリングターゲットへの書き込み終了を待つ。
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
	}

	void RenderingEngine::CopyMainRenderTargetToFrameBuffer(RenderContext& rc)
	{
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		// ビューポートを指定する
		D3D12_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<FLOAT>(g_graphicsEngine->GetFrameBufferWidth());
		viewport.Height = static_cast<FLOAT>(g_graphicsEngine->GetFrameBufferHeight());
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		rc.SetViewportAndScissor(viewport);
		m_copyMainRtToFrameBufferSprite.Draw(rc);
	}
}
