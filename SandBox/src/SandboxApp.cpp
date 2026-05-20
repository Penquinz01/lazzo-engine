#include <Lazzo.h>

class SandBox : public Lazzo::Application {
public:
	SandBox() {
	}
	~SandBox() {
	}
};


Lazzo::Application* Lazzo::CreateApplication() {
	return new SandBox();
}