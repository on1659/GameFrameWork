
// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.


//���� ��ü�� ������ ���� ��� ���۸� �����Ѵ�.
cbuffer cbGameObjectInfo : register(b0)
{
    matrix gmtxWorld : packoffset(c0);
};

//ī�޶��� ������ ���� ��� ���۸� �����Ѵ�. 
cbuffer cbCameraInfo : register(b1)
{
    matrix gmtxView : packoffset(c0);
   matrix gmtxProjection : packoffset(c4);
};

//���� ���̴��� �Է��� ���� ����ü�� �����Ѵ�. 
struct VS_INPUT
{
    float3 position : POSITION; // 3
    float4 color    : COLOR;    // 4
};

//���� ���̴��� ���(�ȼ� ���̴��� �Է�)�� ���� ����ü�� �����Ѵ�. 
struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color    : COLOR;
};

//���� ���̴��� �����Ѵ�.
VS_OUTPUT VSDiffused(VS_INPUT input, uint nVertexID : SV_VertexID)
{
    VS_OUTPUT output;
    output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxWorld), gmtxView), gmtxProjection);
    output.color = input.color;
    return (output);
}

//�ȼ� ���̴��� �����Ѵ�. 
float4 PSDiffused(VS_OUTPUT input) : SV_TARGET
{
  return float4(1, 0, 0, 1);
	//�ԷµǴ� �ȼ��� ������ �״�� ���-���� �ܰ�(���� Ÿ��)�� ����Ѵ�.
    return (input.color);
}
/*
    fxc /E PS_GS_INSTANCE_Cube_GBUFFER /T ps_5_0 /Od /Zi /Fo CompiledGs.fxo GS_Instance_Cube.fx
*/