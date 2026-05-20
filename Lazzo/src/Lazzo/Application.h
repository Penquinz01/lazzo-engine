#pragma once

namespace Lazzo {
	class __declspec(dllexport) Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};
}