
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

//#include <xnamath.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma region [FrameWork]

	/// <summary>
	/// <remarks> 
	/// 1. HINSTANCE // 2. HWND
	/// </remarks>
	/// </summary>
	struct FrameWorkStartData
	{
		HINSTANCE instance;
		HWND hwnd;
	};

#pragma endregion

#pragma region [Camera]

	struct GBUFFER_UNPACKING_DATA 
	{
		XMFLOAT4 PerspectiveValues;
		XMFLOAT4X4 ViewInv;
	};

	struct stCameraBuffer 
	{
		XMFLOAT4X4 m_xmf4x4ViewProjection;
		XMFLOAT4 m_CameraPos;
	};
#pragma endregion

#pragma region [Mesh]
	
	struct VertexPositionColor
	{
		XMFLOAT3 xmf3Positoin;
		XMFLOAT4 xmf3Color;

		VertexPositionColor() {};
		VertexPositionColor(XMFLOAT3 p, XMFLOAT4 c) :xmf3Positoin{ p }, xmf3Color{ c } {}
	};

#pragma endregion

#pragma region [LIGHT]

#pragma region [CapsuleLight]

	struct CAPSULE_LIGHT_DS_CB
	{
		DirectX::XMMATRIX LightProjection;	//world * view * projection
		float CapsuleLightRange;
		float HalfSegmentLen;
		DirectX::XMFLOAT2 CapsuleTempData;	//쓰레기 데이터 float4 마추려고 사용
	};

	struct CAPSULE_LIGHT_PS_CB
	{

		XMFLOAT3 CapsuleLightPos;	//world._41 42 43
		float CapsuleLightRangeRcp;	//range값 가지고 계산
		XMFLOAT3 CapsuleLightDir;	//look vector
		float CapsuleLightLen;

		XMFLOAT3 CapsuleLightColor;
		float CapsuleLightIntensity;
	};

	struct CAPSULE_LIGHT
	{
		float CapsuleLightLen;
		XMFLOAT3 CapsuleLightColor;
		float CapsuleLightRange;
		//float CapsuleLightIntensity;
	};

#pragma endregion

#pragma region [DirectionalLight]

	struct DIRECTIONAL_AMBIENT_LIGHT
	{
		DirectX::XMFLOAT4 m_DirToLight;
		DirectX::XMFLOAT4 m_DirLightColor;
		DirectX::XMFLOAT4 m_DirLightPower;

		DirectX::XMFLOAT3 m_AmbientDown;
		DirectX::XMFLOAT3 m_AmbientRange;
		DirectX::XMFLOAT2 padding;
	};

#pragma endregion

#pragma region [Point Light]

	struct POINT_LIGHT_DS_CB
	{
		XMMATRIX mtxLight;
	};

	struct POINT_LIGHT_PS_CB
	{
		XMFLOAT3 f3Pos;
		float	 fRange;
		XMFLOAT3 f3Color;
		float	 fIntensity;
	};

	struct POINT_LIGHT
	{
		float fRange;
		XMFLOAT3 xmf3Color;
		float fIntensity;
	};

#pragma endregion

#pragma region [Spot Light]

	struct SPOT_LIGHT_DS_CB
	{
		DirectX::XMMATRIX LightProjection;
		float SpotCosOuterCone;//밖 범위 설정<OuterAngle>
		float SpotSinOuterCone;//<OuterAngle>
		DirectX::XMFLOAT2 tempData;//float4를 맞추기 위한 데이터
	};

	struct SPOT_LIGHT_PS_CB
	{
		DirectX::XMFLOAT3 SpotLightPos;//설정
		float SpotLightRangeRcp;//범위 설정

		DirectX::XMFLOAT3 SpotLightDir;
		float SpotCosOuterCone;//밖 범위 설정<OuterAngle>

		DirectX::XMFLOAT3 SpotLightColor;//색 설정
		float SpotCosConeAttRcp;//안쪽 범위 설정<InnerAngle>
	};

	struct SPOT_LIGHT
	{
		float SpotLightRange;
		DirectX::XMFLOAT3 SpotLightColor;
		float fOuterAngle;
		float fInnerAngle;
	};

#pragma endregion

#pragma endregion

#pragma region [VS]
	
	struct VS_CB_WORLD_MATRIX
	{
		XMFLOAT4X4						m_d3dxmtxWorld;
	};

	struct VS_VB_INSTANCE 
	{
		XMMATRIX m_xmmtxWorld;
	};

#pragma endregion

#pragma region [Input]

	enum WARP_KEY
	{
		WP_LEFT = 0,
		WP_RIGHT,
		WP_UP,
		WP_DOWN,
		WP_RBUTTON,
		WP_LBUTTON,
		WP_LSHIFT,
		WP_SPACE,
		WP_F1,
		WP_F2,
		WP_F3,
		WP_F4,
		WP_F5,
		WP_W,
		WP_A,
		WP_S,
		WP_D,
		WP_Z,
		WP_X,
		WP_C,
		WP_I,
		WP_J,
		WP_K,
		WP_L,
		WP_U,
		WP_O,
		WP_P,
		WP_T,
		WP_Q,
		WP_G,
		WP_0,
		WP_1,
		WP_2,
		WP_3,
		WP_4,
		WP_5,
		WP_6,
		WP_7,
		WP_8,
		WP_9,
		WP_M,
		WP_H,
		WP_TAB,
		WP_F6,	//서버와의 혼선을 주지 않게 하려고
		WP_F7,
		WP_F8,
		WP_Y,
		WP_F11,
		WP_CTRL,
		WP_END
	};

	enum Warp_MouseWheel
	{
		WHEEL_UP = 1,
		WHEEL_DOWN = -1,
		WHEEL_NON = 0,
	};

	enum VK_KEY
	{
		VK_0 = 48,
		VK_1 = 49,
		VK_2,
		VK_3,
		VK_4,
		VK_5,
		VK_6,
		VK_7,
		VK_8,
		VK_9,
		VK_A = 0x41,
		VK_B,
		VK_C,
		VK_D,
		VK_E,
		VK_F,
		VK_G,
		VK_H,
		VK_I,
		VK_J,
		VK_K,
		VK_L,
		VK_M,
		VK_N,
		VK_O,
		VK_P,
		VK_Q,
		VK_R,
		VK_S,
		VK_T,
		VK_U,
		VK_V,
		VK_W,
		VK_X,
		VK_Y,
		VK_Z
	};
	
	enum_def(WARP_DIR)
	{
		FORWARD  = 0x01,
		BACKWARD = 0x02,
		LEFT	 = 0x04,
		RIGHT	 = 0x08,
		UP		 = 0x10,
		DOWN	 = 0x20,
	}
	enum_end

#pragma endregion