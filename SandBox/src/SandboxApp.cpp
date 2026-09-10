#include "lzpch.h"
#include <Lazzo.h>
#include <Lazzo/Primitives/Cube.h>

class SandBox : public Lazzo::Application {
public:
	SandBox() {
	}
	~SandBox() {
	}

protected:
	void OnRender() override {
		m_Cube.Draw();
	}

	void OnImGuiRender() override {
		m_Cube.DrawUI();
	}

private:
	Lazzo::Cube m_Cube;
};


Lazzo::Application* Lazzo::CreateApplication() {
	return new SandBox();
}
