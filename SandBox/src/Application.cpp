namespace Lazzo {
	__declspec(dllimport) Application;
}

void main() {
	Lazzo::Application* app = new Lazzo::Application();
	app->Run();
	delete app;
}