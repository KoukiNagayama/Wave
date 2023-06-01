#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsDemoEngine
{
	RenderingEngine* RenderingEngine::m_instance = nullptr;
	
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	RenderingEngine::RenderingEngine()
	{

		// ���C�������_�����O�^�[�Q�b�g���������B
		InitMainRenderTarget();

		// ���C�������_�����O�^�[�Q�b�g�̓��e���t���[���o�b�t�@�ɃR�s�[����X�v���C�g���������B
		InitCopyMainRenderTargetToFrameBufferSprite();

	}

	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	RenderingEngine::~RenderingEngine()
	{

	}

	/// <summary>
	/// ���C�������_�����O�^�[�Q�b�g���������B
	/// </summary>
	void RenderingEngine::InitMainRenderTarget()
	{
		// ���C�������_�����O�^�[�Q�b�g���쐬�B
		m_mainRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),	// �c���̓t���[���o�b�t�@�Ɠ���
			g_graphicsEngine->GetFrameBufferHeight(),	// �����̓t���[���o�b�t�@�Ɠ���
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,				// �J���[�o�b�t�@��RGBA32bit���������_�^
			DXGI_FORMAT_D32_FLOAT						// �f�v�X�X�e���V���o�b�t�@��D32bit���������_�^						
		);
	}

	/// <summary>
	/// ���C�������_�����O�^�[�Q�b�g�̓��e���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g���������B
	/// </summary>
	void RenderingEngine::InitCopyMainRenderTargetToFrameBufferSprite()
	{
		// �X�v���C�g�̏������I�u�W�F�N�g�B
		SpriteInitData spriteInitData;

		// �e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃e�N�X�`���B
		spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();

		// �𑜓x�̓t���[���o�b�t�@�Ɠ���
		spriteInitData.m_width = g_graphicsEngine->GetFrameBufferWidth();
		spriteInitData.m_height = g_graphicsEngine->GetFrameBufferHeight();
	
		// �V�F�[�_�[�̃t�@�C���p�X�͊�{�I�ȃX�v���C�g�̃V�F�[�_�[�̂��̂��g�p�B
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
	
		// �������I�u�W�F�N�g�����ƂɃX�v���C�g���������B
		m_copyMainRtToFrameBufferSprite.Init(spriteInitData);
	}

	/// <summary>
	/// ���s�B
	/// </summary>
	/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
	void RenderingEngine::Execute(RenderContext& rc)
	{
		// �t�H���[�h�����_�����O�B
		ForwardRendering(rc);

		// ���C�������_�����O�^�[�Q�b�g�̓��e���t���[���o�b�t�@�ɃR�s�[����B
		CopyMainRenderTargetToFrameBuffer(rc);

		// �o�^���Ă������f�����N���A����B
		m_forwardRenderingModels.clear();
	}

	/// <summary>
	/// �t�H���[�h�����_�����O�B
	/// </summary>
	/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
	void RenderingEngine::ForwardRendering(RenderContext& rc)
	{
		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�\�ɂȂ�܂ő҂B
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);

		// �����_�����O�^�[�Q�b�g��ݒ肷��B
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);

		// �����_�����O�^�[�Q�b�g���N���A����B
		rc.ClearRenderTargetView(m_mainRenderTarget);

		// �`��
		for (auto& model : m_forwardRenderingModels) {
			model->Draw(rc);
		}

		// �����_�����O�^�[�Q�b�g�ւ̏������ݏI����҂B
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
	}

	void RenderingEngine::CopyMainRenderTargetToFrameBuffer(RenderContext& rc)
	{
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		// �r���[�|�[�g���w�肷��
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
