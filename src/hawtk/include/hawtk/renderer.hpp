#pragma once

#include <hawtk/vec.hpp>

namespace hawtk {
	struct vertex {
		vec2 position;
		color color;
	};

	class renderer {
		friend class context;

	private:
		renderer() = default;
		virtual ~renderer() = default;
		virtual void draw(const std::vector<vertex>& vertices) = 0;
		virtual void enable_alpha_blending();
		virtual void disable_alpha_blending();
		virtual void enable_scissor_test(const vec2& offset, const vec2& bounds);
		virtual void disable_scissor_test();
	};
}
