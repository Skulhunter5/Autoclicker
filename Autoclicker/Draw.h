#pragma once

#include <string>
#include <Windows.h>
#include <vector>
#include "ImGui/imgui.h"

class Window {
public:
	static unsigned int width;
	static unsigned int height;
	static bool sizeChanged;
};

bool IntWndProc(UINT msg, WPARAM wParam, LPARAM lParam);

void InitImGui();
void Draw();