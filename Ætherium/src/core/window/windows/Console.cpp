#include "Console.h"
namespace Ætherium {
	namespace UIWindow {
        using namespace Debug;
        void Console::Update()
        {
            if (show) {
                if (!Begin("Console")) {
                    End();
                }
                
                //ImGui::ListBox("Console", &cur_item, items, 3);s
                ImVec2 screenSize = ImGui::GetWindowSize();
                if (ImGui::Button("CLEAR")) {
                    Debug::Debugger::log.clear();
                }

                int size = Debug::Debugger::log.size();

                if (screenSize.y - 120 > 0) {
                    ImGui::BeginListBox("", ImVec2(screenSize.x - 20,screenSize.y - 120));
                
                
                    for (int i = 0; i < size; i++)
                    {
                        ImGui::Text(Debug::Debugger::log[i].msg);
                    }
             
                    ImGui::EndListBox();
                }
                End();
            }
        }

	}
}