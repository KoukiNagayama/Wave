#include "stdafx.h"
#include "Wave.h"

namespace
{

}

bool Wave::Start()
{
	// ‰Šú‰»ƒf[ƒ^B
	ModelInitData initData;
	initData.m_tkmFilePath = "Assets/modelData/waveModel_01.tkm";
	initData.m_fxFilePath = "Assets/shader/wave.fx";
	initData.m_modelUpAxis = enModelUpAxisZ;
	initData.m_expandConstantBuffer = &m_waveCb;
	initData.m_expandConstantBufferSize = sizeof(m_waveCb);


	m_modelRender.InitDirectlyNotifyForwardRendering(initData);

	m_modelRender.SetTRS(
		m_pos,
		m_rot,
		m_sca
	);
	m_modelRender.SetScale(Vector3(5.0f, 1.0f, 5.0f));
	m_modelRender.Update();

	// ”g1
	m_waveCb.m_waveDetail[0].m_length = 30.0f;
	m_waveCb.m_waveDetail[0].m_sharpness = 0.7f;
	m_waveCb.m_waveDetail[0].m_height = 0.8f;
	m_waveCb.m_waveDetail[0].m_direction = Vector2(0.2f, 0.3f);
	// ”g2
	m_waveCb.m_waveDetail[1].m_length = 60.0f;
	m_waveCb.m_waveDetail[1].m_sharpness = 0.3f;
	m_waveCb.m_waveDetail[1].m_height = 0.5f;
	m_waveCb.m_waveDetail[1].m_direction = Vector2(-0.4f, 0.7f);
	// ”g3
	m_waveCb.m_waveDetail[2].m_length = 40.0f;
	m_waveCb.m_waveDetail[2].m_sharpness = 0.3f;
	m_waveCb.m_waveDetail[2].m_height = 0.9f;
	m_waveCb.m_waveDetail[2].m_direction = Vector2(0.4f, 0.4f);
	// ”g4
	m_waveCb.m_waveDetail[3].m_length = 35.0f;
	m_waveCb.m_waveDetail[3].m_sharpness = 0.4f;
	m_waveCb.m_waveDetail[3].m_height = 1.0f;
	m_waveCb.m_waveDetail[3].m_direction = Vector2(-0.3f, 0.6f);

	return true;
}

void Wave::Update()
{
	g_camera3D->SetTarget(m_pos);

	// ŒX‚¯‚éB
	if (g_pad[0]->IsPress(enButtonA)) {
		m_rot.AddRotationDegX(5.0f);
	}
	else if (g_pad[0]->IsPress(enButtonB)) {
		m_rot.AddRotationDegX(-5.0f);
	}
	else if (g_pad[0]->IsPress(enButtonX)) {
		m_rot.AddRotationDegY(5.0f);
	}
	else if (g_pad[0]->IsPress(enButtonY)) {
		m_rot.AddRotationDegY(-5.0f);
	}
	m_modelRender.SetRotation(m_rot);

	m_modelRender.Update();

	// ”g–äƒŠƒZƒbƒg
	if (m_waveCb.m_isGenerateRipple) {
		m_waveCb.m_isGenerateRipple = false;
	}

	// ”g–ä
	if (m_timerToRippleGenerate >= 10.0f) {
		m_waveCb.m_ripplePos.x = rand() % 100 + 1;
		m_waveCb.m_ripplePos.y = rand() % 100 + 1;
		m_waveCb.m_isGenerateRipple = true;
		m_timerToRippleGenerate = 0.0f;
	}

	// ƒ^ƒCƒ}[isB
	m_waveCb.m_deltaTime += g_gameTime->GetFrameDeltaTime();
	m_timerToRippleGenerate += g_gameTime->GetFrameDeltaTime();
}

void Wave::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
