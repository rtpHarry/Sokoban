#pragma once

#ifdef _MSC_VER
#pragma comment( lib, "winmm.lib" )
#endif

#include <Windows.h>
#include <mmsystem.h>

class CTimer
{
public:
	CTimer(void);
	~CTimer(void);
private:
	// Frames Per Second Monitor
	static float m_FPSLastCheckTime;		// to make sure fps is update per second
	static float m_FPSCounter;				// how many frames since last second
	static float m_FPS;						// current fps, ready to report back

	// Frame Delta
	static float m_LastTime;				// time of last check
	static float m_FrameDelta;				// frame delta, ready to report back


public:
	// Update the Frame Delta
	void Tick(void)
	{
		// frame delta update
		//////////////////////////////////////////////////////////////////////////
		// grab time from most accurate time source
		float currentTime = timeGetTime() * 0.001f;

		// calculate frame delta
		m_FrameDelta = currentTime - m_LastTime;

		// store for next frame
		m_LastTime = currentTime;

		// fps counter update
		//////////////////////////////////////////////////////////////////////////
		// increase the fps counter
		++m_FPSCounter;

		// if a second has passed update the real fps
		if( currentTime - m_FPSLastCheckTime > 1.0f)
		{
			// prepare last check time
			m_FPSLastCheckTime = currentTime;

			// set real fps
			m_FPS = m_FPSCounter;

			// reset counter
			m_FPSCounter = 0;
		}

	}

	// Get the current frame delta
	float GetFrameDelta(void)
	{
		return m_FrameDelta;
	}

	// Get the current fps
	float GetFPS(void)
	{
		return m_FPS;
	}
};
