#include <App/GameApp.h>

// --------------------------------------- //
//	The Main Entry Point of Our Program
// --------------------------------------- //
int main()
{
	GameApp app;

	if (!app.Init())
	{
		app.Cleanup();
		return 1;
	}

	app.Run();

	app.Cleanup();

	return 0;
}