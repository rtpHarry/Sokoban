#include ".\timer.h"

// FPS
float CTimer::m_FPSLastCheckTime = 0.0f;			// to make sure fps is update per second
float CTimer::m_FPSCounter = 0.0f;				// how many frames since last second
float CTimer::m_FPS = 0.0f;						// current fps, ready to report back

// Frame Delta
float CTimer::m_LastTime = 0.0f;					// time of last check
float CTimer::m_FrameDelta = 0.0f;				// frame delta, ready to report back


CTimer::CTimer(void)
{
}

CTimer::~CTimer(void)
{
}

