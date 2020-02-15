#include "ofMain.h"
#include "Llum2020App.h"
#include "ofxWatchdog.h"

//========================================================================



#ifndef TARGET_WIN32

int main() {

    // ofxWatchdog::boot(msec, reboot, override, verbose)
    //
    //     msec : how long does the watchdog wait, when the process hangs-up in milli seconds
    //   reboot : automatically restart the process
    // override : use internal signal handler (optional)
    //  verbose : print more log information (optional)
    ofxWatchdog::boot(3000, true, true, true);
    
    ofGLFWWindowSettings settingsGL;
    settingsGL.doubleBuffering = true;
    settingsGL.windowMode = OF_WINDOW;
    settingsGL.title = "Llum 2020 App";
   
    ofCreateWindow(settingsGL);
    
    // ofxWatchdog::trap(void)
    ofxWatchdog::trap();
    
	//ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new Llum2020App());

}

#else

#include "../../resource.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

    ofGLFWWindowSettings settingsGL;
    settingsGL.doubleBuffering = true;
    settingsGL.windowMode = OF_WINDOW;
    settingsGL.title = "Llum 2020 App";
    
    ofCreateWindow(settingsGL);
    
	//ofSetupOpenGL(1280, 768, OF_WINDOW);

	HWND hwnd = ofGetWin32Window();
	HICON hMyIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hMyIcon);


	ofRunApp(new Llum2020App());

}

#endif


