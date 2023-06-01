/*!
 * @brief	�g�p���f���V�F�[�_�[�B
 */


////////////////////////////////////////////////
// �\����
////////////////////////////////////////////////
//���_�V�F�[�_�[�ւ̓��́B
struct SVSIn
{
    float4 pos : POSITION; //���f���̒��_���W�B
    float2 uv : TEXCOORD0; //UV���W�B
    float3 normal : NORMAL;
};
//�s�N�Z���V�F�[�_�[�ւ̓��́B
struct SPSIn
{
    float4 pos : SV_POSITION; //�X�N���[����Ԃł̃s�N�Z���̍��W�B
    float2 uv : TEXCOORD0; //uv���W�B
    float3 normal : TEXCOORD1;
    float4 vertexW : TEXCOORD2;
};
struct WaveDetail
{
    float length;           // �����B
    float sharpness;        // �s���B
    float height;           // �����B
    float pad1;
    float2 direction;       // �����B
    float pad2;
    float pad3;
};


////////////////////////////////////////////////
// �萔�o�b�t�@�B
////////////////////////////////////////////////
//���f���p�̒萔�o�b�t�@
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};


cbuffer TimeCb : register(b1)
{
    float deltaTime;
    float3 pad;
    WaveDetail waveDetail[4];
}



////////////////////////////////////////////////
// �O���[�o���ϐ��B
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0); //�A���x�h�}�b�v
sampler g_sampler : register(s0); //�T���v���X�e�[�g�B

////////////////////////////////////////////////
// �萔�B
////////////////////////////////////////////////
static const float PI = 3.14159f;
static const float GRAVITY = 9.8f;


////////////////////////////////////////////////
// �֐���`�B
////////////////////////////////////////////////

/// <summary>
/// �Q���X�g�i�[�g�����֐��B
/// </summary>
void GerstnerWave(in float3 localVtx,
        float deltaTime,
        float length,
        float sharpness,
        float height,
        float2 direction,
        inout float3 localVtxPos,
        inout float3 localNormal)
{
    float3 browDir = normalize(float3(direction.x, 0.0f, direction.y));
    float A = length / 14.0f;
    float _2pi_per_L = 2.0f * PI / length;
    float d = dot(browDir.xz, localVtx.xz);
    float th = _2pi_per_L * d + sqrt(GRAVITY / _2pi_per_L) * deltaTime;
    
    float3 pos = float3(0.0f, 0.0f, height * A * sin(th));
    pos.xy = sharpness * A * browDir * cos(th);
    
    float3 normal = float3(0.0f, 1.0f, 0.0f);
    normal.xy = -browDir * height * cos(th) / (7.0f / PI - sharpness * browDir * browDir * sin(th));
    
    localVtxPos += pos;
    localNormal += normalize(normal);
}

void CyclicWave(in float3 localVtx,
    float deltaTime,
    float length,
    float sharpness,
    float height,
    inout float3 localVtxPos,
    inout float3 localNormal
)
{
    
}


/// <summary>
/// ���_�V�F�[�_�[�̃R�A�֐��B
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
    SPSIn psIn;
    psIn.pos = vsIn.pos;
    psIn.vertexW = mul(mWorld, vsIn.pos);
    
    float3 oPosW = float3(0.0f, 0.0f, 0.0f);
    float3 oNormalW = float3(0.0f, 0.0f, 0.0f);
    float t = deltaTime;
    
    // �g1
    GerstnerWave(
        psIn.vertexW.xyz, 
        t + 2.0f, 
        waveDetail[0].length, 
        waveDetail[0].sharpness, 
        waveDetail[0].height, 
        waveDetail[0].direction, 
        oPosW, 
        oNormalW
    );
    // �g2
    GerstnerWave(
        psIn.vertexW.xyz, 
        t,
        waveDetail[1].length,
        waveDetail[1].sharpness,
        waveDetail[1].height,
        waveDetail[1].direction,
        oPosW,
        oNormalW
    );
    // �g3
    GerstnerWave(
        psIn.vertexW.xyz, 
        t + 3.0f,
        waveDetail[2].length,
        waveDetail[2].sharpness,
        waveDetail[2].height,
        waveDetail[2].direction,
        oPosW,
        oNormalW
    );
    // �g4
    GerstnerWave(
        psIn.vertexW.xyz, 
        t,
        waveDetail[3].length,
        waveDetail[3].sharpness,
        waveDetail[3].height,
        waveDetail[3].direction,
        oPosW,
        oNormalW
    );
    
   /* GerstnerWave(psIn.vertexW.xyz, t, 60.0f, 0.3f, 0.5f, float2(-0.4f, 0.7f), oPosW, oNormalW);
    GerstnerWave(psIn.vertexW.xyz, t + 3.0f, 40.0f, 0.3f, 0.9f, float2(0.4f, 0.4f), oPosW, oNormalW);
    GerstnerWave(psIn.vertexW.xyz, t, 35.0f, 0.4f, 1.0f, float2(-0.3f, 0.6f), oPosW, oNormalW);*/
    psIn.vertexW.x += oPosW.x;
    psIn.vertexW.y += oPosW.y;
    psIn.vertexW.z += oPosW.z;

    psIn.pos = mul(mView, psIn.vertexW);
    psIn.pos = mul(mProj, psIn.pos);

    psIn.uv = vsIn.uv;
    return psIn;
}

/// <summary>
/// �s�N�Z���V�F�[�_�[�̃G���g���[�֐��B
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
    float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
    return albedoColor;
}
