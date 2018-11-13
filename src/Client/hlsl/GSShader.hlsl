

static const int gSize = 3;

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

Texture2D gtxtTexture : register(t0);
SamplerState gSamplerState : register(s0);

struct VS_INPUT
{
    float3 position : POSITION; // 3
   // float4 color : COLOR; // 4
};

struct GS_INPUT
{
    float4 positionW : POSITION; // world
  //  float4 color : COLOR;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float4 color : COLOR;
};

GS_INPUT VSDiffused(VS_INPUT input, uint nVertexID : SV_VertexID)
{
    GS_INPUT output;
    output.positionW = float4(input.position, 1.0f);
    return (output);
}

[maxvertexcount(4)]
void GSDiffused
(
    point GS_INPUT input[1],
    uint nPrimID : SV_PrimitiveID,
    inout TriangleStream<PS_INPUT> stream
)
{
    PS_INPUT v[4];

   //월드 좌표
    float4 position = input[0].positionW;
   //  float4 diffuse = input[0].color;
    matrix viewProject = mul(gmtxView, gmtxProjection);
    float index = 0;

    v[0].position = mul(mul(float4(position.x - gSize, position.y + gSize, position.z, position.w), gmtxWorld), viewProject);
    v[0].color = float4(1, 0, 0, 1);

    v[1].position = mul(mul(float4(position.x - gSize, position.y - gSize, position.z, position.w), gmtxWorld), viewProject);
    v[1].color = float4(0, 1, 0, 1);
    
    v[2].position = mul(mul(float4(position.x + gSize, position.y + gSize, position.z, position.w), gmtxWorld), viewProject);
    v[2].color = float4(0, 0, 1, 1);
    
    v[3].position = mul(mul(float4(position.x + gSize, position.y - gSize, position.z, position.w), gmtxWorld), viewProject);
    v[3].color = float4(1, 0, 1, 1);
   //--------------------------------------------------------------------

    stream.Append(v[0]);
    stream.Append(v[2]);
    stream.Append(v[1]);
    stream.Append(v[3]);
    stream.RestartStrip();
}


[maxvertexcount(24)]
void GSCube
(
    point GS_INPUT input[1],
    uint nPrimID : SV_PrimitiveID,
    inout TriangleStream<PS_INPUT> stream
)
{
    PS_INPUT v[24];

   //월드 좌표
    float4 position = float4(gmtxWorld._41, gmtxWorld._42, gmtxWorld._43, 1.0f);
    float fx = gSize;
    float fy = gSize;
    float fz = gSize;
    float4 posRot;

    float index = 0;
    float3 fNormalVector; // = float3(0.0f, 0.0f, 0.0f);
    matrix gmtxViewProjection = mul(gmtxView, gmtxProjection);

   //0
    posRot = mul(float4(-fx, +fy, -fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(1, 0, 0, 1);
    index++;
   //1
    posRot = mul(float4(-fx, -fy, -fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(0, 1, 0, 1);
    index++;
   //2
    posRot = mul(float4(+fx, +fy, -fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(0, 0, 1, 1);
    index++;
   //3
    posRot = mul(float4(+fx, -fy, -fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(1, 0, 1, 1);
    index++;


   //4
    posRot = mul(float4(+fx, +fy, -fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(1, 0, 1, 1);
    v[index].uv = float2(0.0, 0.0);
    index++;
   //5
    posRot = mul(float4(+fx, -fy, -fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(0, 0, 1, 1);
    v[index].uv = float2(0.0, 1.0);
    index++;
   //6
    posRot = mul(float4(+fx, +fy, +fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(0, 1, 0, 1);
    v[index].uv = float2(1.0, 0.0);
    index++;
   //7
    posRot = mul(float4(+fx, -fy, +fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(1, 0, 0, 1);
    v[index].uv = float2(1.0, 1.0);
    index++;


   //8
    posRot = mul(float4(+fx, +fy, +fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(1, 0, 1, 1);
    v[index].uv = float2(0.0, 0.0);
    index++;
   //9
    posRot = mul(float4(+fx, -fy, +fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(0, 0, 1, 1);
    index++;
   //10
    posRot = mul(float4(-fx, +fy, +fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(0, 0, 1, 1);
    index++;
   //11
    posRot = mul(float4(-fx, -fy, +fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(1, 0, 0, 1);
    index++;
   //-----------------------여기까지-----------------------------------

   //12
    posRot = mul(float4(-fx, +fy, +fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(1, 0, 0, 1);
    index++;
   //13
    posRot = mul(float4(-fx, -fy, +fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(0, 0, 1, 1);
    index++;
   //14
    posRot = mul(float4(-fx, +fy, -fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(0, 0, 1, 1);
    index++;
   //15
    posRot = mul(float4(-fx, -fy, -fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(1, 0, 1, 1);
    index++;


   //16
    posRot = mul(float4(-fx, +fy, +fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(1, 0, 0, 1);
    index++;
   //17
    posRot = mul(float4(-fx, +fy, -fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(0, 1, 1, 1);
    index++;
   //18
    posRot = mul(float4(+fx, +fy, +fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(0, 1, 0, 1);
    index++;
   //19
    posRot = mul(float4(+fx, +fy, -fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(1, 1, 0, 1);
    index++;


   //20
    posRot = mul(float4(-fx, -fy, -fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(1, 0, 0, 1);
    index++;
   //21
    posRot = mul(float4(-fx, -fy, +fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(1, 0, 1, 1);
    index++;
   //22
    posRot = mul(float4(+fx, -fy, -fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(0, 1, 0, 1);
    index++;
   //23
    posRot = mul(float4(+fx, -fy, +fz, 0.f), gmtxWorld).xyzw;
    v[index].position = posRot + position;
    v[index].position = mul(v[index].position, gmtxViewProjection);
    v[index].color = float4(0, 1, 1, 1);
    index++;

    int i = 0;
    for (int count = 0; count < 6; count++)
    {
        v[i + 0].uv = float2(0.0, 0.0);
        v[i + 2].uv = float2(0.0, 1.0);
        v[i + 1].uv = float2(1.0, 0.0);
        v[i + 3].uv = float2(1.0, 1.0);

        stream.Append(v[i + 0]);
        stream.Append(v[i + 2]);
        stream.Append(v[i + 1]);
        stream.Append(v[i + 3]);
        i += 4;
        stream.RestartStrip();
    }
    stream.RestartStrip();
}

float4 PSDiffused(PS_INPUT input) : SV_TARGET
{
    float4 cColor = gtxtTexture.Sample(gSamplerState, input.uv);
    return cColor;
    //return (input.color);
}

/*
    fxc /E PSDiffused /T ps_5_0 /Od /Zi /Fo CompiledGs.fxo GSShader.hlsl
*/