//
// Created by huion on 2024/4/8.
//

#include "GLThread.h"


#include <thread>

#include "EglHelper.h"



void GLThread::run() {
    guardedRun();
    {
        std::unique_lock lk(sGLThreadManager);
        mExited = true;
    }
}

void GLThread::setRenderMode(int renderMode) {

}

int GLThread::getRenderMode() const {
    return ;
}

void GLThread::stopEglSurfaceLocked() {

}

void GLThread::stopEglContextLocked() {

}

void GLThread::guardedRun() {
    mEglHelper = std::make_shared<EglHelper>();
    mHaveEglContext = false;
    mHaveEglSurface = false;
    mWantRenderNotification = false;

    bool createEglContext = false;
    bool createEglSurface = false;
    bool createGlInterface = false;
    bool lostEglContext = false;
    bool sizeChanged = false;
    bool wantRenderNotification = false;
    bool doRenderNotification = false;
    bool askedToReleaseEglContext = false;
    int w = 0;
    int h = 0;

    Runnable event;
    Runnable finishDrawingRunnable;

    while(true) {
        {
            std::unique_lock lk(sGLThreadManager);
            while (true) {
                if (mShouldExit) {
                    return;
                }
                if(mEventQueue.empty()) {
                    event = mEventQueue.front();
                    mEventQueue.pop_front();
                    break;
                }
                bool pausing = false;
                if (mPaused != mRequestPaused) {
                    pausing = mRequestPaused;
                    mPaused = mRequestPaused;
                    cv.notify_all();
                }
                if (mShouldReleaseEglContext) {
                    stopEglSurfaceLocked();
                    stopEglContextLocked();
                    mShouldReleaseEglContext = false;
                    askedToReleaseEglContext = true;
                }
                if (lostEglContext) {
                    stopEglSurfaceLocked();
                    stopEglContextLocked();
                    lostEglContext = false;
                }
                if (pausing && mHaveEglSurface) {
                    stopEglSurfaceLocked();
                }
                if (pausing && mHaveEglContext) {
                    if (!preserveEglContextOnPause) {
                        stopEglContextLocked();
                    }
                }
                if (!mHasSurface && !mWaitingForSurface) {
                    if (mHaveEglSurface) {
                        stopEglSurfaceLocked();
                    }
                    mWaitingForSurface = true;
                    mSurfaceIsBad = false;
                    cv.notify_all();
                }
                if (mHasSurface && mWaitingForSurface) {
                    mWaitingForSurface = false;
                    cv.notify_all();
                }
                if (doRenderNotification) {
                    mWantRenderNotification = false;
                    doRenderNotification = false;
                    mRenderComplete = true;
                    cv.notify_all();
                }
                if (mFi)
            }
        }
    }
}

bool GLThread::ableToDraw() {
    return false;
}

void GLThread::requestRender() {

}

void GLThread::requestRenderAndNotify(const Runnable &finishDrawing) {

}

void GLThread::surfaceCreated() {

}

void GLThread::surfaceDestroyed() {

}

void GLThread::onPause() {

}

void GLThread::onResume() {

}

void GLThread::onWindowResize(int w, int h) {

}

void GLThread::requestExitAndWait() {

}

void GLThread::requestReleaseEglContextLocked() {

}

void GLThread::queueEvent(const Runnable &r) {

}
