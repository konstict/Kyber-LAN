// Copyright BattleDash. All Rights Reserved.

#include <Render/Windows/ClientWindow.h>

#include <Base/Log.h>
#include <Core/Program.h>
#include <Render/Windows/MainWindow.h>
#include <Utilities/ErrorUtils.h>
#include <SDK/SDK.h>
#include <Core/Server.h>

#include <Windows.h>
#include <chrono>

namespace Kyber
{
ClientWindow::ClientWindow() {}

bool ClientWindow::IsEnabled()
{
    return g_mainWindow->IsEnabled() && m_isEnabled;
}

void ClientWindow::Draw()
{
    ImGui::Begin("Client Settings", &m_isEnabled);
    if (!g_program->m_server->m_running)
    {
        ImGui::Text("Direct Connect to Host");
        static char address[128] = "127.0.0.1";
        ClientSettings* clientSettings = Settings<ClientSettings>("Client");
        ImGui::InputText("Server IP", address, IM_ARRAYSIZE(address));
        
        if (ImGui::Button("Connect") && strlen(address) > 0)
        {
            SocketSpawnInfo info(false, "", "");
            clientSettings->ServerIp = address;
            g_program->m_server->m_socketSpawnInfo = info;
            g_program->m_joining = true;
            g_program->ChangeClientState(ClientState_Startup);
        }
        ImGui::Separator();
        ImGui::Text("Server browser and proxies are disabled.");
    }
    else
    {
        ImGui::Text("Please stop your server in order to join one.");
        ImGui::Text("You can do so by pressing 'Quit' in the pause menu.");
    }
    ImGui::End();
}
} // namespace Kyber