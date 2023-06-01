#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"


namespace nsDemoEngine
{
	void ModelRender::InitDirectlyNotifyForwardRendering(ModelInitData modelInitData)
	{
		// �X�P���g�����������B
		InitSkeleton(modelInitData.m_tkmFilePath);
		// �J���[�o�b�t�@�̃t�H�[�}�b�g���w��B
		modelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R16G16B16A16_FLOAT;
		// ���f���̏������B
		m_model.Init(modelInitData);
	}

	void ModelRender::Init(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis
	)
	{
		// �X�P���g�����������B
		InitSkeleton(filePath);
		// �A�j���[�V�������������B
		InitAnimation(animationClips, numAnimationClips);

		// ���f���̏������f�[�^�B
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = filePath;					// tkm�t�@�C���p�X�B
		modelInitData.m_fxFilePath = "Assets/shader/model.fx";	// fx�t�@�C���p�X�B
		modelInitData.m_modelUpAxis = enModelUpAxis;			// ������B
		if (m_animationClips != nullptr) {
			modelInitData.m_skeleton = &m_skeleton;				// �X�P���g���B
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		modelInitData.m_vsEntryPointFunc = "VSMain";
		modelInitData.m_psEntryPointFunc = "PSMain";
		
		// �������f�[�^����ɂ��ă��f�����������B
		m_model.Init(modelInitData);

	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		// �X�P���g���̃t�@�C���p�X(������)
		std::string skeletonFilePath = filePath;

		// tkm�̃t�@�C���p�X��tks�̃t�@�C���p�X�ɕϊ��B
		// �t�@�C���p�X����.tkm�ƂȂ��Ă��镔���܂ł̕������������B
		int pos = (int)skeletonFilePath.find(".tkm");
		// �擾��������������4������.tks�ɕϊ��B
		skeletonFilePath.replace(pos, 4, ".tks");
		// char*�ɕϊ������t�@�C���p�X���g���ăX�P���g�����������B
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips,
		int numAnimationClips
	)
	{
		// �����Ŏ����Ă����f�[�^�������o�ϐ��ɓo�^����B
		m_numAnimationClips = numAnimationClips;
		m_animationClips = animationClips;

		// �A�j���[�V�����N���b�v�̃f�[�^���������ꍇ�͂������ɃA�j���[�V����������������B
		if (m_animationClips != nullptr) {
			m_animation.Init(
				m_skeleton,				// �A�j���[�V������K�p����X�P���g��
				m_animationClips,		// �A�j���[�V�����N���b�v
				m_numAnimationClips		// �A�j���[�V�����̐�
			);
		}
	}

	void ModelRender::Update()
	{
		// ���f���̃��[���h�s��̍X�V�B
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		// �X�P���g���̃��[���h�s��̍X�V�B
		if (m_skeleton.IsInited()) {
			m_skeleton.Update(m_model.GetWorldMatrix());
		}

		// �A�j���[�V�������X�V�B
		//m_animation.Progress(g_gameTime->GetFrameDeltaTime());
	
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		// �����_�����O�G���W�����̃t�H���[�h�����_�����O�p�`��p�X�Ƀ��f����o�^�B
		RenderingEngine::GetInstance()->Add3DModelToForwardRenderPass(m_model);
	}
}
