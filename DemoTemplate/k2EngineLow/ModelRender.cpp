#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"


namespace nsDemoEngine
{
	void ModelRender::InitDirectlyNotifyForwardRendering(ModelInitData modelInitData)
	{
		// スケルトンを初期化。
		InitSkeleton(modelInitData.m_tkmFilePath);
		// カラーバッファのフォーマットを指定。
		modelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R16G16B16A16_FLOAT;
		// モデルの初期化。
		m_model.Init(modelInitData);
	}

	void ModelRender::Init(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis
	)
	{
		// スケルトンを初期化。
		InitSkeleton(filePath);
		// アニメーションを初期化。
		InitAnimation(animationClips, numAnimationClips);

		// モデルの初期化データ。
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = filePath;					// tkmファイルパス。
		modelInitData.m_fxFilePath = "Assets/shader/model.fx";	// fxファイルパス。
		modelInitData.m_modelUpAxis = enModelUpAxis;			// 上方向。
		if (m_animationClips != nullptr) {
			modelInitData.m_skeleton = &m_skeleton;				// スケルトン。
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		modelInitData.m_vsEntryPointFunc = "VSMain";
		modelInitData.m_psEntryPointFunc = "PSMain";
		
		// 初期化データを基にしてモデルを初期化。
		m_model.Init(modelInitData);

	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		// スケルトンのファイルパス(文字列)
		std::string skeletonFilePath = filePath;

		// tkmのファイルパスをtksのファイルパスに変換。
		// ファイルパス中で.tkmとなっている部分までの文字数を検索。
		int pos = (int)skeletonFilePath.find(".tkm");
		// 取得した文字数から4文字を.tksに変換。
		skeletonFilePath.replace(pos, 4, ".tks");
		// char*に変換したファイルパスを使ってスケルトンを初期化。
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips,
		int numAnimationClips
	)
	{
		// 引数で持ってきたデータをメンバ変数に登録する。
		m_numAnimationClips = numAnimationClips;
		m_animationClips = animationClips;

		// アニメーションクリップのデータがあった場合はそれを基にアニメーションを初期化する。
		if (m_animationClips != nullptr) {
			m_animation.Init(
				m_skeleton,				// アニメーションを適用するスケルトン
				m_animationClips,		// アニメーションクリップ
				m_numAnimationClips		// アニメーションの数
			);
		}
	}

	void ModelRender::Update()
	{
		// モデルのワールド行列の更新。
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		// スケルトンのワールド行列の更新。
		if (m_skeleton.IsInited()) {
			m_skeleton.Update(m_model.GetWorldMatrix());
		}

		// アニメーションを更新。
		//m_animation.Progress(g_gameTime->GetFrameDeltaTime());
	
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		// レンダリングエンジン内のフォワードレンダリング用描画パスにモデルを登録。
		RenderingEngine::GetInstance()->Add3DModelToForwardRenderPass(m_model);
	}
}
