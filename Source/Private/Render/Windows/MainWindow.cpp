// Copyright BattleDash. All Rights Reserved.

#include <Render/Windows/MainWindow.h>

#include <Core/Program.h>
#include <Render/Windows/ServerWindow.h>
#include <Render/Windows/ClientWindow.h>
#include <Render/Windows/LinkWindow.h>
#include <Utilities/ErrorUtils.h>

#include <Windows.h>

Kyber::MainWindow* g_mainWindow;

namespace Kyber
{
MainWindow::MainWindow()
{
    if (g_mainWindow)
    {
        ErrorUtils::ThrowException("MainWindow is already initialized.");
    }
    m_serverWindow = new ServerWindow();
    m_clientWindow = new ClientWindow();
    m_LinkWindow = new LinkWindow();
}

bool MainWindow::IsEnabled()
{
    return m_isEnabled;
}

void MainWindow::Draw()
{
    ImGui::Begin("KYBER", &m_isEnabled, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::Button("SERVER SETUP"))
    {
        m_serverWindow->m_isEnabled = true;
    }

    if (ImGui::Button("SERVER BROWSER"))
    {
        m_clientWindow->m_isEnabled = true;
    }

    ImGui::Separator();

    if (ImGui::SmallButton("GITHUB (OTHER LINKS)"))
    {
        m_LinkWindow->m_isEnabled = true;
    }

    ImGui::End();
}
} // namespace Kyber