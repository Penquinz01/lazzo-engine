#include <Lazzo.h>

class SandBox : public Lazzo::Application {
	public:
	SandBox() {
	}
	~SandBox() {
	}
};


void main(){
	SandBox* app = new SandBox();
	app->Run();
	delete app;
}