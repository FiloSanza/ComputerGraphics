#include "Hermite.h"

#include <math.h>
#include <assert.h>
#include <ranges>

namespace Geometry {

	inline float Hermite::phi0(const float t) {
		return 2.0 * pow(t, 3) - 3.0 * pow(t, 2) + 1;
	}

	inline float Hermite::phi1(const float t) {
		return pow(t, 3) - 2.0 * pow(t, 2) + t;
	}

	inline float Hermite::psi0(const float t) {
		return -2.0 * pow(t, 3) + 3.0 * pow(t, 2);
	}

	inline float Hermite::psi1(const float t) {
		return pow(t, 3) - pow(t, 2);
	}

	float Hermite::derive(int idx, const std::vector<float>& t, float delta_prev, float delta_next, float tens, float bias, float cont)
	{
		float sign = (idx & 1) ? -1.0 : 1.0;
		float bias_tens_cont_prev = (1 - tens) * (1 + bias) * (1 + sign * cont);
		float bias_tens_cont_next = (1 - tens) * (1 + bias) * (1 - sign * cont);
		float delta_t_prev = idx == 0 ? 1 : (t[idx] - t[idx - 1]);
		float delta_t_next = idx == t.size()-1 ? 1 : (t[idx + 1] - t[idx]);

		return 0.5f * (bias_tens_cont_prev * delta_prev / delta_t_prev + bias_tens_cont_next * delta_next / delta_t_next);
	}

	float Hermite::derive(int idx, const std::vector<float>& t, const auto& value) {
		if (idx == value.size()) return 0;
		const float delta_prev_x = idx == 0 ? 0 : value[idx] - value[idx - 1];
		const float delta_next_x = idx >= value.size()-1 ? 0 : value[idx + 1] - value[idx];
		return derive(idx, t, delta_prev_x, delta_next_x);
	}

	std::vector<Engine::Vertex> Hermite::interpIntoVertices(
		const std::vector<glm::vec3>& points,
		Engine::Vertex center,
		glm::vec4 color_vertex,
		int samples
	) {
		float t_step = 1.0 / (points.size() - 1);
		std::vector<float> t;

		for (int i = 0; i < points.size(); i++) {
			t.push_back(i * t_step);
		}

		const auto x = std::views::transform(points, [](const auto& p) { return p.x; });
		const auto y = std::views::transform(points, [](const auto& p) { return p.y; });

		std::vector<Engine::Vertex> output = { center };

		// Sample the range [0,1] samples times.
		// We need to move idx accordingly to make sure that we apply the interpolation to the right point.
		int idx = 0;
		float step = 1.0f / (samples - 1);
		for (float sample = 0; sample <= 1; sample += step) {
			// Go to the next interval if the new sample lays after the current one (move from [t[idx], t[idx+1]] to [t[idx+1], t[idx+2]]).
			if (sample > t[idx + 1])
				idx++;

			const float width = t[idx + 1] - t[idx];
			// Normalize the sample within the range [t[idx], t[idx+1]] to a range of [0, 1]
			const float norm_sample = (sample - t[idx]) / width;

			// Derive x both at start and end of the interval [t[idx], t[idx+1]]
			const float dx_start = derive(idx, t, x);
			const float dx_end = derive(idx + 1, t, x);

			// Derive y both at start and end of the interval [t[idx], t[idx+1]]
			const float dy_start = derive(idx, t, y);
			const float dy_end = derive(idx + 1, t, y);

			const float x_coord = x[idx] * phi0(norm_sample) + dx_start * phi1(norm_sample) * width + x[idx+1] * psi0(norm_sample) + dx_end * psi1(norm_sample) * width;
			const float y_coord = y[idx] * phi0(norm_sample) + dy_start * phi1(norm_sample) * width + y[idx+1] * psi0(norm_sample) + dy_end * psi1(norm_sample) * width;
			output.push_back({ glm::vec3(x_coord, y_coord, 0.0), color_vertex });
		}

		return output;
	}
}