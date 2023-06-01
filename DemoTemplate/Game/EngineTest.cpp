#include "stdafx.h"
#include "EngineTest.h"

bool EngineTest::Start()
{
	// ƒ‚ƒfƒ‹‚ð‰Šú‰»B
	m_modelRender.Init(
		"Assets/modelData/waveModel_01.tkm",
		nullptr,
		0,
		enModelUpAxisZ
	);
	m_modelRender.SetTRS(
		m_pos,
		m_rot,
		m_sca
	);



	return true;
}

void EngineTest::Update()
{
	if (g_pad[0]->IsPress(enButtonA)) {
		m_rot.AddRotationDegY(5.0f);
	}
	else if (g_pad[0]->IsPress(enButtonB)) {
		m_rot.AddRotationDegY(-5.0f);
	}
	m_modelRender.SetRotation(m_rot);
	m_modelRender.Update();
}

void EngineTest::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
