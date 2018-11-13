
// Copyright �� http://radar92.tistory.com 
// ���� ���� �� ����� ����
// �ڵ� ��� �� on1659@naver.com�� �����Ͻñ� �ٶ��ϴ�.

#pragma once

const ULONG MAX_SAMPLE_COUNT = 50; // Maximum frame time sample count

class CGameTimer : public CSingleTonBase<CGameTimer>
{
public:
	CGameTimer(const std::string& name = "Timer");
	virtual ~CGameTimer();

	float& Tick(const int nFPS);

	unsigned long GetFrameRate(LPTSTR lpszString = nullptr, int nCharacters = 0) const;

	const float& GetTimeElapsed() const { return m_fTimeElapsed; }

	float& GetGlobalTime() { return m_fGlobalTime; }

private:
	bool									m_bHardwareHasPerformanceCounter;   // Has Performance Counter
	float									m_fTimeScale;						// Amount to scale counter
	float									m_fTimeElapsed;						// Time elapsed since previous frame
	std::chrono::system_clock::time_point	m_nLastTime;						// Performance Counter last frame
	std::chrono::system_clock::time_point	m_nCurrentTime;						// Current Performance Counter
	__int64									m_PerformanceFrequency;				// Performance Frequency

	float									m_fFrameTime[MAX_SAMPLE_COUNT];
	ULONG									m_nSampleCount;

	unsigned long							m_nCurrentFrameRate;				// Stores current framerate
	unsigned long							m_FramePerSecond;					// Elapsed frames in any given second
	float									m_fFPSTimeElapsed;					// How much time has passed during FPS sample
	float									m_fGlobalTime;
};
