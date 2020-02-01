#include "ofMain.h"
#include "Llum2020App.h"

//========================================================================



#ifndef TARGET_WIN32

int main() {

    ofGLFWWindowSettings settingsGL;
    settingsGL.doubleBuffering = true;
    settingsGL.windowMode = OF_WINDOW;
    settingsGL.title = "Llum 2020 App";
   
    ofCreateWindow(settingsGL);
    
	//ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new WindowTreeApp());

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


