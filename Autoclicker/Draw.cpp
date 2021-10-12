#include "Draw.h"

#include <stdlib.h>

static int key_target = -1;

static ImFont* font_corbel_20 = NULL;
static ImFont* font_corbel_30 = NULL;
static ImFont* font_corbel_40 = NULL;

unsigned int Window::width = 1280;
unsigned int Window::height = 800;
bool Window::sizeChanged = true;

static const unsigned int nTabs = 3;
static const char* tabIdToTitle[nTabs] = { "Simple", "Complex", "Shurtcuts" };
static int selectedTab = 0;

struct SimpleMacro {
	char name[20];
	UINT id;
	int key;
	int delay;
};

static std::vector<SimpleMacro> simpleMacros = {};

bool IntWndProc(UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_KEYDOWN) {
		if (key_target >= 0) {
			if (wParam == VK_ESCAPE) {
				key_target = -1;
				return 1;
			}
			simpleMacros.at(key_target).key = wParam;
			key_target = -1;
			return 1;
		}
	}
	return 0;
}

// Tweaks
struct Tweaks {
	float color[3] = { 0.8f, 0.8f, 0.8f };
} tweaks;
//

void InitImGui() {

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGuiStyle& style = ImGui::GetStyle();
	style.GrabRounding = 0.0f;

	font_corbel_20 = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 20);
	font_corbel_30 = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 30);
	font_corbel_40 = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 40);

	//style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);
	// #0059FF
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.50f, 0.90f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.20f, 0.50f, 0.90f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.20f, 0.50f, 0.90f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	//style.Colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_Separator] = ImVec4(1.0f, 0.0f, 1.0f, 1.00f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);


	style.ChildBorderSize = 3.0f;
	style.ItemSpacing = ImVec2(1.0f, 1.0f);
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	ImGui::GetStyle().WindowPadding = ImVec2(0.0f, 0.0f);
}

/*
ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(tweaks.color[0], tweaks.color[1], tweaks.color[2], 1));
ImGui::PopStyleColor();
*/

void Draw() {
	static int simple_editor_open = -1;

	static bool first_time = true;
	if (first_time) {
		simpleMacros.push_back({ "test1", 0, 72, 500 });
		simpleMacros.push_back({ "test2", 1, 73, 1000 });
		simpleMacros.push_back({ "test3", 2, 74, 250 });

		first_time = false;
	}

	{
		ImGui::Begin("Autoclicker", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);

		if (Window::sizeChanged) {
			ImGui::SetWindowPos(ImVec2(0, 0));
			ImGui::SetWindowSize(ImVec2(Window::width, Window::height));
			Window::sizeChanged = false;
		}

		ImGui::PushFont(font_corbel_40);
		{
			ImVec2 buttonSize = ImVec2(Window::width / 3, 50);
			for (int i = 0; i < nTabs; i++) {
				ImGui::SameLine();
				if (ImGui::Button(tabIdToTitle[i], buttonSize)) selectedTab = i;
			}
		}
		ImGui::PopFont();

		// Maybe switch to ImGuiCol_Text = #3EA7FF
		ImGui::PushFont(font_corbel_30);
		{
			const char* text = tabIdToTitle[selectedTab];
			float text_size = ImGui::CalcTextSize(text).x;
			ImGui::Separator();
			ImGui::SetCursorPosX((Window::width - text_size) * 0.5f);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
			ImGui::Text(text);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
			ImGui::Separator();
		}
		ImGui::PopFont();

		float belowBanner = ImGui::GetCursorPosY() + 1;
		float tel_listWidth = 300;

		switch (selectedTab) {
		case 0: { // SimpleMacros
			// MacroList
			ImGui::SetCursorPos(ImVec2(2, belowBanner));
			// -Styles
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(3.0f, 3.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 1.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.0f, 0.5f));
			// -Child
			ImGui::BeginChild("simpleMacros_list", { tel_listWidth, Window::height - ImGui::GetCursorPosY() - 2 }, true, ImGuiWindowFlags_HorizontalScrollbar);
			// -Content
			ImVec2 buttonSize = ImVec2(tel_listWidth - 6, 0);
			for (int i = 0; i < simpleMacros.size(); i++) {
				std::string buttonText = std::string(simpleMacros.at(i).name);
				buttonText.append("##");
				buttonText.append(std::to_string(i));
				if (ImGui::Button(buttonText.c_str(), buttonSize)) {
					simple_editor_open = i;
				}
			}
			// -EndChild
			ImGui::EndChild();
			// -Remove styles
			ImGui::PopStyleVar(3);

			// MacroEditor
			ImGui::SetCursorPos(ImVec2(2 + tel_listWidth + 2, belowBanner));
			// -Styles
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6.0f, 4.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 4.0f));
			// -Child
			ImGui::BeginChild("simpleMacros_editor", ImVec2(Window::width - tel_listWidth, Window::height - ImGui::GetCursorPosY() - 2), true);
			if (simple_editor_open >= 0) {
				SimpleMacro* current = &simpleMacros.at(simple_editor_open);

				ImGui::Text("Name:");
				ImGui::SetCursorPosX(20);
				ImGui::PushItemWidth(291);
				ImGui::InputText("##name", current->name, IM_ARRAYSIZE(current->name));
				ImGui::PopItemWidth();

				ImGui::Text("Key:");
				ImGui::SetCursorPosX(20);
				std::string label = std::string(1, (char)MapVirtualKeyA(current->key, MAPVK_VK_TO_CHAR));
				bool changing_this = false;
				if (key_target == simple_editor_open) {
					changing_this = true;
					label = std::string("Type new key or press again to cancel.");
				}
				if (ImGui::Button(label.c_str(), changing_this ? ImVec2(0, 0) : ImVec2(100, 0))) {
					if (changing_this) {
						key_target = -1;
					}
					else {
						key_target = simple_editor_open;
					}
				}

				ImGui::Text("Delay (ms):");
				ImGui::SetCursorPosX(20);
				ImGui::PushItemWidth(291);
				ImGui::InputInt("##delay", &current->delay);
				ImGui::PopItemWidth();
			}
			// -EndChild
			ImGui::EndChild();
			// -Remove styles
			ImGui::PopStyleVar(2);
			break;
		}
		case 1: // ComplexMacros
			break;
		case 2: // Shortcuts
			break;
		}

		ImGui::End();
	}

	{
		ImGui::Begin("Tweaks");

		ImGui::ColorPicker3("Test", tweaks.color);

		ImGui::End();
	}
}