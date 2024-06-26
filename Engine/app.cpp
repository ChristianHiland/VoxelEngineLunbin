#include "app.h"
#include "util.h"

EngineApp::EngineApp() {
    m_frameCount = 0;
    m_frameTime = 0;
    m_fps = 0;

    m_frameTime = m_startTime = GetCurrentTimeMillis();
}
void EngineApp::CalcFPS() {
    m_frameCount++;

    long long time = GetCurrentTimeMillis();

    if (time - m_frameTime >= 1000) {
        m_frameTime = time;
        m_fps = m_frameCount;
        m_frameCount = 0;
    }
}
void EngineApp::RenderFPS() {
    char text[32];
    ZERO_MEM(text);
    SNPRINTF(text, sizeof(text), "FPS: %d", m_fps);
#ifndef _WIN32
//    m_fontRenderer.RenderText(10, 10, text);
#endif
}
float EngineApp::GetRunningTime() {
    float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)m_startTime) / 1000.0f;
    return RunningTime;
}