// Copyright BattleDash. All Rights Reserved.

#include <Render/Windows/LinkWindow.h>

#include <Render/Windows/MainWindow.h>

#include <Windows.h>

namespace Kyber
{
LinkWindow::LinkWindow() {}

bool LinkWindow::IsEnabled()
{
    return g_mainWindow->IsEnabled() && m_isEnabled;
}

void LinkWindow::Draw()
{
    ImGui::Begin("Link", &m_isEnabled, ImGuiWindowFlags_AlwaysAutoResize);
    for (const char* ch : LinkText)
    {
        ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - ImGui::CalcTextSize(ch).x / 2);
        ImGui::Text(ch);
    }
    ImGui::End();
}
} // namespace Kyber