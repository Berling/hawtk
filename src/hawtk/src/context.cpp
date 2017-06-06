#include <vector>

#include <hawtk/context.hpp>

namespace hawtk {
	void context::draw() {
		std::vector<vertex> vertices = {{vec2{-0.5f, -0.5f}, color{1.f}},
		                                {vec2{0.5f, -0.5f}, color{1.f}},
		                                {vec2{0.f, 0.5f}, color{1.f}}};
		_renderer->begin_pass();
		_renderer->draw(vertices);
	}

	void context::update() {}
}
