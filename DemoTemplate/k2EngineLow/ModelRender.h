#pragma once

using namespace nsK2EngineLow;

/// <summary>
/// �Z�p�f���p�G���W���̖��O��ԁB
/// </summary>
namespace nsDemoEngine
{

	/// <summary>
	/// ���f�������_�[�N���X�B
	/// </summary>
	class ModelRender
	{
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		ModelRender() {}
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~ModelRender() {}

	public:
		/// <summary>
		/// ���f���̏������B
		/// </summary>
		/// <param name="filePath">tkm�t�@�C���p�X�B</param>
		/// <param name="animationClips">�A�j���[�V�����N���b�v�̃A�h���X�B</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐��B</param>
		/// <param name="enModelUpAxis">���f���̏�����B</param>
		void Init(const char* filePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ
		);
		/// <summary>
		/// ����ȃt�H���[�h�����_�����O�p���f���̏������֐��B
		/// </summary>
		/// <param name="modelInitData"></param>
		void InitDirectlyNotifyForwardRendering(ModelInitData modelInitData);
		/// <summary>
		/// ���f���̍X�V�B
		/// </summary>
		void Update();
		/// <summary>
		/// ���f���̕`��B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
		void Draw(RenderContext& rc);
		/// <summary>
		/// �A�j���[�V�����Đ��B
		/// </summary>
		/// <param name="animNo">�A�j���[�V�����̔ԍ��B</param>
		/// <param name="interpolateTime">��Ԏ��ԁB</param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}
		/// <summary>
		/// �A�j���[�V�������Đ������ǂ���
		/// </summary>
		/// <returns>true���Ԃ�΍Đ����B</returns>
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}
		/// <summary>
		/// �A�j���[�V�����̍Đ����x��ݒ�B
		/// </summary>
		/// <param name="animationSpeed">�A�j���[�V�����̍Đ����x�B</param>
		void SetAnimaitonSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}
		/// <summary>
		/// ���W�A��]�A�g�嗦��ݒ�B
		/// </summary>
		/// <param name="pos">���W�B</param>
		/// <param name="rot">��]�B</param>
		/// <param name="sca">�g�嗦�B</param>
		void SetTRS(const Vector3& pos, const Quaternion& rot, const Vector3& sca)
		{
			SetPosition(pos);
		}
		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		/// <param name="pos">���W�B</param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		/// <param name="x">X���W�B</param>
		/// <param name="y">Y���W�B</param>
		/// <param name="z">Z���W�B</param>
		void SetPosition(const float& x, const float& y, const float& z)
		{
			SetPosition({ x, y, z });
		}
		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <param name="rot">��]�B</param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// �g�嗦��ݒ�B
		/// </summary>
		/// <param name="sca">�g�嗦�B</param>
		void SetScale(const Vector3& sca)
		{
			m_scale = sca;
		}
		/// <summary>
		/// �g�嗦��ݒ�B
		/// </summary>
		/// <param name="x">X�����ւ̊g�嗦�B</param>
		/// <param name="y">Y�����ւ̊g�嗦�B</param>
		/// <param name="z">Z�����ւ̊g�嗦�B</param>
		void SetScale(const float& x, const float& y, const float& z)
		{
			SetScale({ x, y, z });
		}

	private:
		/// <summary>
		/// �X�P���g�����������B
		/// </summary>
		/// <param name="filePath">tkm�t�@�C���p�X�B</param>
		void InitSkeleton(const char* filePath);
		/// <summary>
		/// �A�j���[�V�������������B
		/// </summary>
		/// <param name="animationClips">�A�j���[�V�����N���b�v�̃A�h���X�B</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐��B</param>
		void InitAnimation(AnimationClip* animationClips, int numAnimationClips);
	private:
		Model					m_model;									// �t�H���[�h�ŕ`�悳��郂�f���B
		Skeleton				m_skeleton;									// �X�P���g���B
		Animation				m_animation;								// �A�j���[�V�����B
		AnimationClip*			m_animationClips = nullptr;					// �A�j���[�V�����N���b�v�B
		int						m_numAnimationClips = 0;
		Vector3					m_position = Vector3::Zero;					// ���W�B
		Quaternion				m_rotation = Quaternion::Identity;			// ��]�B
		Vector3					m_scale = Vector3::One;						// �g�嗦�B
		float					m_animationSpeed = 1.0f;					// �A�j���[�V�����̍Đ����x�{���B
	};
}


