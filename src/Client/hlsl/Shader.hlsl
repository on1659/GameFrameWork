
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.


//게임 객체의 정보를 위한 상수 버퍼를 선언한다.
cbuffer cbGameObjectInfo : register(b0)
{
    matrix gmtxWorld : packoffset(c0);
};

//카메라의 정보를 위한 상수 버퍼를 선언한다. 
cbuffer cbCameraInfo : register(b1)
{
    matrix gmtxView : packoffset(c0);
   matrix gmtxProjection : packoffset(c4);
};

//정점 셰이더의 입력을 위한 구조체를 선언한다. 
struct VS_INPUT
{
    float3 position : POSITION; // 3
    float4 color    : COLOR;    // 4
};

//정점 셰이더의 출력(픽셀 셰이더의 입력)을 위한 구조체를 선언한다. 
struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color    : COLOR;
};

//정점 셰이더를 정의한다.
VS_OUTPUT VSDiffused(VS_INPUT input, uint nVertexID : SV_VertexID)
{
    VS_OUTPUT output;
    output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxWorld), gmtxView), gmtxProjection);
    output.color = input.color;
    return (output);
}

//픽셀 셰이더를 정의한다. 
float4 PSDiffused(VS_OUTPUT input) : SV_TARGET
{
  return float4(1, 0, 0, 1);
	//입력되는 픽셀의 색상을 그대로 출력-병합 단계(렌더 타겟)로 출력한다.
    return (input.color);
}
/*
    fxc /E PS_GS_INSTANCE_Cube_GBUFFER /T ps_5_0 /Od /Zi /Fo CompiledGs.fxo GS_Instance_Cube.fx
*/