#pragma once

#include <string>
#include <Windows.h>
#include "ImGui/imgui.h"
#include "Utils.h"
#include "Data.h"

class Window {
public:
	static unsigned int width;
	static unsigned int height;
	static bool sizeChanged;
};

void DrawSimpleMacros(float belowBanner);

bool IntWndProc(UINT msg, WPARAM wParam, LPARAM lParam);

void InitImGui();
void Draw();