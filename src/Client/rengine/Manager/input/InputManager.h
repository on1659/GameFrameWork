
// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

#pragma once

//KYT '16.02.17
/*
Input Manager

	KeyDown, KeyUp, MouseWheel, MouseClick

	사용법
	1. Define WARP_KEY값에 사용할 키값을 추가한다.
	- 순서지키는게 중요하다.
	- 최적화를 위해 벡터로 하였기 때문이다.

	2. Load서 방금 등록한 key값을 Add한다.
	- AddKey(넣을 키값, 대응시킬 VK_KEY값)
	- HashTable에도 string을 등록 시킨다.

	함수 설명
	1. Load : 사용할 키를 등록한다.
	2. KeyDown( WARP_KEY(enum) )값을 넣어서 판단.
	- True : KeyDown
	- KeyDown과 Up은 같이 사용해야 한다.

	3. KeyUp (const WARP_KEY&(enum))값을 넣어서 판단.
	- KeyDown하고 같이 사용할 필요는 없다.

	4. OnlWPeyDown은 KeyUp을 사용하지 않을때만 사용한다.
	cuz. 스택에 데이터 집어넣는거 때문에 그럼.

	5. GetWheel()은 어떤 장소에서나 데이터를 리턴받아서
	- GetWheel() < 0 휠 아래로
	- GetWheel() = 0 휠 안움직임
	- GetWheel() > 0 휠 위로

	6. GetInputQueue() = input Data의 Queue데이터이다.

	'16.04.18
	m_bKeyState안에 있는 변수들만 확인하면 될 거 같은데?
*/

#include <deque>
#include <queue>
#include <deque>
#include <queue>

#include <XInput.h>
#pragma comment(lib, "XInput.lib")


enum GPAD_KEY
{
	GPAD_dLEFT = XINPUT_GAMEPAD_DPAD_LEFT,
	GPAD_dRIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
	GPAD_dUP = XINPUT_GAMEPAD_DPAD_UP,
	GPAD_dDOWN = XINPUT_GAMEPAD_DPAD_DOWN,
	GPAD_SPACE = WP_SPACE, //bLeftTrigger,
	GPAD_LSHFIT = WP_LSHIFT, //bRightTrigger,
	GPAD_LBUTTON = XINPUT_GAMEPAD_LEFT_SHOULDER,
	GPAD_RBUTTON = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	GPAD_1 = XINPUT_GAMEPAD_A,
	GPAD_2 = XINPUT_GAMEPAD_B,
	GPAD_3 = XINPUT_GAMEPAD_X,
	GPAD_4 = XINPUT_GAMEPAD_Y,
	GPAD_C = XINPUT_GAMEPAD_START,
	GPAD_G = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	GPAD_END = 12,
	GPAD_NONE = 0,
	GPAD_VIVERATE = 50000,
	GPAD_BACK = XINPUT_GAMEPAD_BACK
};

#define GPAD_DURING_VIVERATE 0.5f


typedef struct tagKeyState
{
	WARP_KEY    ytkey;
	GPAD_KEY  padkey;
	bool	bUpCheck;
	bool	bDownCheck;
	bool	bStick;
	BYTE	BKey;
public:
	tagKeyState();

}KEYSTATE;

struct KeyStateCheck
{
	WARP_KEY key;
	bool   bDown;

	KeyStateCheck() {};

	KeyStateCheck(const WARP_KEY& inKey, bool inDown)
	{
		key = inKey;
		bDown = inDown;
	}
};

class CInputManager : public CSingleTonBase<CInputManager>
{
	//키보드
private:
	//Key Data
	std::vector<KEYSTATE>				m_vKeyState;

	//KeyState
	bool*								m_bKeyState;

	std::deque<KeyStateCheck>			m_bInputQueue;


	int									m_sWheel;
	POINT								pt;

	bool								m_bLeftCheck;
	bool								m_bRightCheck;

	//KYT 16'.04.17
	/*
	input 수정
	*/
	bool							m_bKeyBoardPressCheck;
	UCHAR							pKeysBuffer[256];
	//

	//KYT '16.05.03
	/*
		Character Player을 컴포넌트로 옮기기 위함
	*/
	POINT							m_ptOldCursorPos;

	//JJY '16.05.07
	/*
	m_OldcxDelta, m_OldcyDelta 함수 추가
	*/
	float m_OldcxDelta, m_OldcyDelta;


	//RSH '16.05.13
	/*
	GamePad<Byte> Vector
	*/
	std::vector<KEYSTATE>				m_vPadState;
	bool								m_bConnect;

	std::vector<std::string>		    m_stHashTable;

	//진동
	float								m_fVibrateDuringTime;
	float								m_fVibrateionFrame;
	bool								m_bVibrate;

	//KYT '17.09.09
	/*
		HWND 추가
	*/
	HWND								m_hWnd;
#ifdef _CALLFUNCTION_FAIL_0909_
	using tyUpdate = std::function<void(const float&)>;
	using tyWARP_KEY = std::function<bool(const WARP_KEY&)>;

	tyUpdate	fnUpdate{ nullptr };
	tyWARP_KEY	fnKeyUp;
	tyWARP_KEY	fnKeyDown{ nullptr };
	tyWARP_KEY	fnOnlyKeyDown{ nullptr };
#endif //_CALLFUNCTION_FAIL_0909_

public:
	CInputManager(const CInputManager& rhs) = delete;


public:
	CInputManager(const tstring& name = _XTT("InputManager"));
	~CInputManager();


private:
	void AddKey(const WARP_KEY& key, BYTE input, GPAD_KEY gPad = GPAD_NONE);
	void AddPadButton(const WARP_KEY& pad, BYTE input);


public:

	WARP_RESULT_ENUM Start(void* pData) override;
	void Update(const float& fTimeEleasped);
	void UpdateKeyBoard();
	void UpdateGamePoad(const float& fTimeEleasped);

	// bKeyBoard_Container
	bool KeyDown(const WARP_KEY& input);
	bool KeyBoardDown(const WARP_KEY& key);
	bool KeyPadDown(const WARP_KEY& key);

	// KeyUp
	bool KeyUp(const WARP_KEY& input);
	bool KeyBoardUp(const WARP_KEY& input);
	bool KeyPadUp(const WARP_KEY& input);

	void ShowQueue();
	void ClearQueue() { m_bInputQueue.clear(); }

	//KeyUp은 사용하지 않고 KeyDown만 사용하는 키에서 사용
	bool OnlyKeyDown(const WARP_KEY& input);
	bool OnlyKeyBoardDown(const WARP_KEY& input);
	bool OnlyKeyPadDown(const WARP_KEY& input);

	BYTE AnyOneKeyDown(int n, WARP_KEY ...);

	void SetHWND(HWND hWnd) { m_hWnd = hWnd; }

	//Mouse
	/*  Wheel Down < WheelNon < Wheel Up  */
	void SetWheel(const int& wheel);
	int GetWheel() { return m_sWheel; }
	void MouseWheel();
	void SetMousePoint(const int& x, const int& y);
	void SetMousePoint(POINT _pt);
	bool MouseLeftDown();
	bool MouseRightDown();
	bool MouseLeftUp();
	bool MouseRightUp();
	void SetMouseLeft(const bool& click) { m_bLeftCheck = click; }
	void SetMouseRight(const bool& click) { m_bRightCheck = click; }
	POINT GetMousePoint() { return pt; }



	// Queue Clear 및 데이터 Popup
	void ShowInputData();

	//void DeleteQueue(){ m_bInputQueue.clear(); }

	std::size_t GetSize() { return m_bInputQueue.size(); }

	std::deque<KeyStateCheck> GetInputQueue();


	//KYT '16.04.17
	/*
	input 수정
	*/
	void SetKeyBoardPress(const bool& press) { m_bKeyBoardPressCheck = press; }
	//

	//JJY '16.04.18
	/*
	플레이어 InputDataSending함수 추가
	*/
	void InputDataSending();


	//KYT '16.05.02
	void SetOldCursorPos() { GetCursorPos(&m_ptOldCursorPos); }
	POINT GetOldCursorPos() const { return m_ptOldCursorPos; }

	//JJY '16.05.07
	/*
		GetOldcxDelta, GetOldcyDelta 함수 추가
	*/
	void  MouseUpdate(const float& fTime);
	void SaveCursorPos();
	float GetOldcxDelta() { return m_OldcxDelta; }
	float GetOldcyDelta() { return m_OldcyDelta; }
	void SetOldcxDelta(const float& cxdelta) { m_OldcxDelta = cxdelta; }
	void SetOldcyDelta(const float& cydelta) { m_OldcyDelta = cydelta; }

private:
	//RSH '16.05.01 
	/*
	XBOX 조작을 위한 멤버 변수 추가
	*/
	XINPUT_STATE m_xGamepadState;
	SHORT		 m_oldThumbRX;
	SHORT		 m_oldThumbRY;
	SHORT		 m_oldThumbLX;
	SHORT		 m_oldThumbLY;

public:
	//RSH '16.05.01 
	/*
	XBOX 조작을 위한 멤버 함수 추가
	*/
	XINPUT_GAMEPAD GetGamepad();
	bool IsGamepadConnected() const { return m_bConnect; }
	void IsGamepadConnected(bool*);
	bool IsGamepadRightThumb_outsideDeadzoneX();
	bool IsGamepadRightThumb_outsideDeadzoneY();
	bool IsGamepadRightThumb_outsideDeadzone();

	bool IsGamepadLeftThumb_outsideDeadzoneX();
	bool IsGamepadLeftThumb_outsideDeadzoneY();
	bool IsGamepadLeftThumb_outsideDeadzone();

	bool IsGamepadLeftThumb_outsideDeadzoneLeft();
	bool IsGamepadLeftThumb_outsideDeadzoneRight();

	bool IsGamepadLeftThumb_outsideDeadzoneUp();
	bool IsGamepadLeftThumb_outsideDeadzoneDown();



	void      StartVibrate(int leftVal = GPAD_VIVERATE, int rightVal = GPAD_VIVERATE);
	void  StartLeftVibrate(int vibrate = GPAD_VIVERATE);
	void StartRightVibrate(int vibrate = GPAD_VIVERATE);
	void       StopVibrate(int leftVal = 0, int rightVal = 0);

};

