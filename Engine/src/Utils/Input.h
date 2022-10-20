#pragma once

#include <cstdint>
#include <cassert>

namespace Engine {

	namespace Keyboard {
		using KeyCode = unsigned char;
		
		enum Key : KeyCode
		{
			Space = 32,
			Apostrophe = 39, /* ' */
			Comma = 44, /* , */
			Minus = 45, /* - */
			Period = 46, /* . */
			Slash = 47, /* / */

			D0 = 48, /* 0 */
			D1 = 49, /* 1 */
			D2 = 50, /* 2 */
			D3 = 51, /* 3 */
			D4 = 52, /* 4 */
			D5 = 53, /* 5 */
			D6 = 54, /* 6 */
			D7 = 55, /* 7 */
			D8 = 56, /* 8 */
			D9 = 57, /* 9 */

			Semicolon = 59, /* ; */
			Equal = 61, /* = */

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,

			LeftBracket = 91,  /* [ */
			Backslash = 92,  /* \ */
			RightBracket = 93,  /* ] */
			GraveAccent = 96,  /* ` */
		};
	}

	namespace Mouse {
		using ButtonType = int;
		using StateType = int;

		enum class ButtonState : StateType {
			Down	= 0,
			Up		= 1
		};

		enum class Button : ButtonType {
			/* Values taken from GLUT library */
			Left	= 0,
			Middle	= 1,
			Right	= 2,
		};

		static std::string mouseButtonToString(Button button) {
			switch (button) {
			case Button::Left:		return "Left";
			case Button::Middle:	return "Middle";
			case Button::Right:		return "Right";
			default: assert(false); //TODO HANDLE
			}
		}

		static std::string mouseButtonStateToString(ButtonState state) {
			switch (state) {
			case ButtonState::Up:		return "Up";
			case ButtonState::Down:	return "Down";
			default: assert(false); //TODO HANDLE
			}
		}
	};
}