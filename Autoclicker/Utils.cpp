#include "Utils.h"

const std::string Utils::keyCode_to_string(unsigned int keyCode) {
	switch (keyCode) {
	// SPACE & TAB
	case VK_SPACE:
		return "SPACE";
	case VK_TAB:
		return "TAB";
	// Controls (CTRL & SHIFT & ALT & CAPSLOCK)
	case VK_CONTROL:
		return "CTRL";
	case VK_SHIFT:
		return "SHIFT";
	case VK_MENU:
		return "ALT";
	case VK_CAPITAL:
		return "CAPSLOCK";
	// BACKSPACE & RETURN
	case VK_BACK:
		return "BACKSPACE";
	case VK_RETURN:
		return "RETURN";
	// INSERT & DELETE
	case VK_INSERT:
		return "INSERT";
	case VK_DELETE:
		return "DELETE";
	// Positions (POS1/HOME & END)
	case VK_HOME:
		return "HOME";
	case VK_END:
		return "END";
	// Arrows (UP & DOWN & LEFT & RIGHT)
	case VK_UP:
		return "UP";
	case VK_DOWN:
		return "DOWN";
	case VK_LEFT:
		return "LEFT";
	case VK_RIGHT:
		return "RIGHT";
	// PAGEUP & PAGEDOWN
	case VK_PRIOR:
		return "PAGEUP";
	case VK_NEXT:
		return "PAGEDOWN";
	// FunctionKeys (F1-F12) (F13-F24 not implemented)
	case VK_F1:
		return "F1";
	case VK_F2:
		return "F2";
	case VK_F3:
		return "F3";
	case VK_F4:
		return "F4";
	case VK_F5:
		return "F5";
	case VK_F6:
		return "F6";
	case VK_F7:
		return "F7";
	case VK_F8:
		return "F8";
	case VK_F9:
		return "F9";
	case VK_F10:
		return "F10";
	case VK_F11:
		return "F11";
	case VK_F12:
		return "F12";
	// Default
	default:
		return std::string(1, (char)MapVirtualKeyA(keyCode, MAPVK_VK_TO_CHAR));
	}
	return "";
}