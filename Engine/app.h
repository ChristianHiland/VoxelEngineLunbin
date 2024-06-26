#ifndef OGLDEV_APP_H
#define OGLDEV_APP_H

class EngineApp {
protected:
	EngineApp();
	void CalcFPS();
	void RenderFPS();
	float GetRunningTime();
protected:
#ifndef _WIN32
//	FontRenderer m_fontRenderer;
#endif
private:
	long long m_frameTime;
	long long m_startTime;
	int m_frameCount;
    int m_fps;
};
#endif
