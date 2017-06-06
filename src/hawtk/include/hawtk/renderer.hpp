#pragma once

#include <hawtk/vec.hpp>

namespace hawtk {
	struct vertex {
		vec2 position;
		color color;
	};

	class renderer {
		friend class context;

	public:
		virtual ~renderer() = default;

	protected:
		renderer() = default;

	private:
		virtual void draw(const std::vector<vertex>& vertices) = 0;
		virtual void begin_pass() = 0;
		virtual void end_pass() = 0;
		virtual void enable_scissor_test(const vec2& offset, const vec2& bounds) = 0;
		virtual void disable_scissor_test() = 0;
	};
}
