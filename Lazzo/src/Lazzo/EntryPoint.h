#pragma once

#ifdef LZ_PLATFORM_WINDOWS


extern Lazzo::Application* Lazzo::CreateApplication();

int main(int argc, char** argv) {

	Lazzo::Log::Init();
	LZ_CORE_WARN("Initialized Log");
	int a = 5;
	LZ_TRACE("Hello mister {0}",a);

	auto app = Lazzo::CreateApplication();
	app->Run();
	delete app;
}

#endif 
