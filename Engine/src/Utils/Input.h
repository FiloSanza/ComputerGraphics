#pragma once

#include <cstdint>
#include <cassert>
#include <unordered_map>

namespace Engine {

	namespace Keyboard {
		using KeyCode = unsigned char;
		
		enum class Key : KeyCode
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

			A = 97,
			B = 98,
			C = 99,
			D = 100,
			E = 101,
			F = 102,
			G = 103,
			H = 104,
			I = 105,
			J = 106,
			K = 107,
			L = 108,
			M = 109,
			N = 110,
			O = 111,
			P = 112,
			Q = 113,
			R = 114,
			S = 115,
			T = 116,
			U = 117,
			V = 118,
			W = 119,
			X = 120,
			Y = 121,
			Z = 122,

			LeftBracket = 91,  /* [ */
			Backslash = 92,  /* \ */
			RightBracket = 93,  /* ] */
			GraveAccent = 96,  /* ` */
		};

		class KeyboardState {
		public:
			bool isPressed(Key key) { return states.count(key) ? states[key] : false; }
			void setPressed(Key key, bool is_pressed) { states[key] = is_pressed; }
		private:
			std::unordered_map<Key, bool> states;
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