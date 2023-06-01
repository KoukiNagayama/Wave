#pragma once

using namespace nsK2EngineLow;

/// <summary>
/// �Z�p�f���p�G���W���̖��O��ԁB
/// </summary>
namespace nsDemoEngine
{
	/// <summary>
	/// �����_�����O�G���W���N���X�B
	/// </summary>
	class RenderingEngine
	{
	private:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		RenderingEngine();
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~RenderingEngine();
	public:
		/// <summary>
		/// ���s�B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		void Execute(RenderContext& rc);
		/// <summary>
		/// �t�H���[�h�����_�����O�̕`��p�X�Ƀ��f����ǉ��B
		/// </summary>
		/// <param name="model"></param>
		void Add3DModelToForwardRenderPass(Model& model)
		{
			m_forwardRenderingModels.push_back(&model);
		}

	public:
		/// <summary>
		/// �C���X�^���X�𐶐��B
		/// </summary>
		static void CreateInstance()
		{
			m_instance = new RenderingEngine;
		};
		/// <summary>
		/// �C���X�^���X��j���B
		/// </summary>
		static void DeleteInstance()
		{
			if (m_instance) {
				delete m_instance;
			}
		}
		/// <summary>
		/// �C���X�^���X���Q�ƁB
		/// </summary>
		static RenderingEngine* GetInstance()
		{
			return m_instance;
		}

	private:
		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g���������B
		/// </summary>
		void InitMainRenderTarget();
		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g�̓��e���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g���������B
		/// </summary>
		void InitCopyMainRenderTargetToFrameBufferSprite();
		/// <summary>
		/// �t�H���[�h�����_�����O�B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		void ForwardRendering(RenderContext& rc);
		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g�̓��e���t���[���o�b�t�@�ɃR�s�[����B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);
	private:
		RenderTarget				m_mainRenderTarget;					// ���C�������_�����O�^�[�Q�b�g�B
		Sprite						m_copyMainRtToFrameBufferSprite;	// ���C�������_�����O�^�[�Q�b�g�̓��e���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
		std::vector<Model*>			m_forwardRenderingModels;			// �t�H���[�h�����_�����O�����郂�f���B
	private:
		static RenderingEngine*		m_instance;							// �B��̃C���X�^���X�B

	};
}


