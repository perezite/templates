#include "app/AppDelegate.h"
#include "CCEGLView.h"
#include <iostream>
#include <stdlib.h>

USING_NS_CC;

int main()
{
    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setViewName("HelloCpp");
    eglView->setFrameSize(1024, 768);
    // The resolution of ipad3 is very large. In general, PC's resolution is smaller than it.
    // So we need to invoke 'setFrameZoomFactor'(only valid on desktop(win32, mac, linux)) to make the window smaller.
    eglView->setFrameZoomFactor(0.6f);
    return CCApplication::sharedApplication()->run();

}