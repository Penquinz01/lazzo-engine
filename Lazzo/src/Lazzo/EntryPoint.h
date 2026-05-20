#pragma once

#ifdef LZ_PLATFORM_WINDOWS


extern Lazzo::Application* Lazzo::CreateApplication();

int main(int argc, char** argv) {
	auto app = Lazzo::CreateApplication();
	app->Run();
	delete app;
}

#endif 
