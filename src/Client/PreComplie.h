// PreCompile.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#include "task/MyFlag.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// D3D11
#include <d3d11_2.h>
#include <dxgi1_3.h>
#include <D3DX11tex.h>

// D3D12
#include <d3d12.h>
#include <dxgi1_4.h>
//#include <Client.h>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <D3Dcompiler.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <D3DX10Math.h>
#include <d3dcompiler.h>
//#include <client.h>
//#include <D3D9Types.h>

#include <Mmsystem.h>


//#undef _DEBUG
//#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else 
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
//#endif // _DEBUG
//#define _DEBUG


//전역 HWND
static HWND g_Hwnd;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

//#include <xnamath.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <stack>
#include <algorithm>
#include <memory>
#include <process.h>
#include <ctime>
#include <random>
#include <chrono>
#include <atlimage.h>
#include <unordered_map>
#include <functional>
#include <thread>
#include <wrl.h>
#include <assert.h>
//RSH '16.05.01
/*
XBOX 컨트롤러 조작 추가를 위한 라이브러리 정의
*/
#include <XInput.h>
#pragma comment(lib, "XInput.lib")
#pragma comment(lib, "dxgi.lib")

//JJY 16'.04.16 plus
/*
네트워크 include 추가
*/
//NetWork
#pragma comment(lib, "ws2_32")
#include <winsock2.h>

//KYT '18.05.26
/*
C++17 확장
*/
//#include <any>


/* User include */
#define CLIENT_ONLY	// 클라이언트 온니라는 의미
#include "DX12/d3dx12.h"
#include "DX12/DDSTextureLoader12.h"
// #include "d3dx12.h"
// #include "DDSTextureLoader12.h"
#include "task/MyDefine.h"
#include "task/MyClientDefine.h"
#include "task/MyUsing.h"
#include "task/MyStruct.h"
#include "task/MyEnum.h"

#include "Object.h"
#include "DXObject.h"
#include "Camera.h"
#include "Mesh.h"

#include "SingleTon.h"
#include "safe_delete.hpp"
#include "Manager/time/Timer.h"
#include "Manager/input/InputManager.h"
#include "Util/Util.h"
#include "Util/UploadBuffer.h"
#include "Globalvariable.h"
#include "GameFrameWork.h"

// #include "DXObject.h"
// 
// #include "SingleTon.h"
// #include "Globalvariable.h"
// 
// // 순서 중요
// #include "Buffer.h"
// 
// 
// #include "ShaderBase.h"
// #include "GameObject.h"
// #include "LightObject.h"
// 


// KYT '17.07.17 
/*
- 기록
- 현재

* CreateConstantBuffer를 추가해야 함 ->
* DirectShader에 Mesh, ojbect를 붙이는 중

*/