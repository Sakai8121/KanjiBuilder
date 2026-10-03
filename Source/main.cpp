#include "DxLib.h"
#include "Core/Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application application;
	if (application.Initialize()) {

		application.Run();
	}
	application.Finalize();
}