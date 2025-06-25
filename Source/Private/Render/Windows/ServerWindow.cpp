// Copyright BattleDash. All Rights Reserved.

#include <Render/Windows/ServerWindow.h>

#include <Base/Log.h>
#include <Core/Program.h>
#include <Render/Windows/MainWindow.h>
#include <SDK/Modes.h>
#include <SDK/SDK.h>
#include <Core/Server.h>

#include <vector>
#include <algorithm>
#include <map>

namespace Kyber
{
ServerWindow::ServerWindow() {
    
}

bool ServerWindow::IsEnabled()
{
    return g_mainWindow->IsEnabled() && m_isEnabled;
}

bool DrawScoreboardPlayer(std::vector<ServerPlayer*> playerList, int index)
{
    if (playerList.size() <= (size_t)index)
    {
        return false;
    }
    ServerPlayer* player = playerList[index];
    if (!player) return false;

    ImGui::Text("%s", player->m_name);
    ImGui::SameLine();
    if (ImGui::SmallButton(("SWAP TEAM##" + std::string(player->m_name)).c_str()))
    {
        if (g_program && g_program->m_server)
             g_program->m_server->SetPlayerTeam(player, player->m_teamId == 1 ? 2 : 1);
    }
    ImGui::SameLine();
    if (ImGui::SmallButton(("KICK##" + std::string(player->m_name)).c_str()))
    {
        if (g_program && g_program->m_server)
            g_program->m_server->KickPlayer(player, "You have been kicked.");
    }
    return true;
}

void ServerWindow::Draw()
{
    ImGui::Begin("SERVER SETTINGS", &m_isEnabled, ImGuiWindowFlags_AlwaysAutoResize);
    GameSettings* gameSettings = Settings<GameSettings>("Game");
    ImGui::Text("GAME MODE:");
    ImGui::SameLine();
    ImGui::TextUnformatted(gameSettings->DefaultLayerInclusion ? gameSettings->DefaultLayerInclusion : "N/A");
    ImGui::Text("LEVEL:");
    ImGui::SameLine();
    ImGui::TextUnformatted(gameSettings->Level ? gameSettings->Level : "N/A");
    ImGui::Separator();
    if (!g_program->m_server->m_running)
    {
        static GameMode currentMode = { "", "Mode", {}, {} };
        static GameLevel currentLevel = { "", "Level" };
        
        if (ImGui::BeginCombo("##modeCombo", currentMode.name))
        {
            for (int n = 0; n < IM_ARRAYSIZE(s_game_modes); n++)
            {
                bool selected = (strcmp(currentMode.mode, s_game_modes[n].mode) == 0);
                if (ImGui::Selectable(s_game_modes[n].name, selected))
                {
                    currentMode = s_game_modes[n];
                    currentLevel = { "", "Level" };
                }
                if (selected) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        if (ImGui::BeginCombo("##levelCombo", currentLevel.name))
        {
            for (size_t i = 0; i < currentMode.levels.size(); i++)
            {
                GameLevel level = GetGameLevel(currentMode, currentMode.levels[i]);
                bool selected = (strcmp(currentLevel.level, level.level) == 0);
                if (ImGui::Selectable(level.name, selected))
                {
                    currentLevel = level;
                }
                if (selected) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        static int maxPlayers = 40;
        ImGui::SliderInt("Max Players", &maxPlayers, 2, 64);
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("To allow player connection, you need\nto use give LAN service (like RadminVPN or hamachi)\n or in router settings you need to forward a port 25200 (UDP)\nThen tell to players your IP from LAN service or outer IP by forwarded port.");
        }
        static int errorTime = 0;
        if (ImGui::Button("Start Server"))
        {
            if (strcmp(currentMode.name, "Mode") != 0 && strcmp(currentLevel.name, "Level") != 0)
            {
                g_program->m_server->Start(currentLevel.level, currentMode.mode, maxPlayers, SocketSpawnInfo(false, "", "Direct Connect Server"));
            }
            else
            {
                errorTime = 1000;
            }
        }
        if (errorTime > 0)
        {
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("Please select a game mode and level.");
            errorTime--;
        }
    }
    else if (g_program->m_clientState == ClientState_Ingame)
    {
        ImGui::Text("Leave this game to start a new one.");
        ImGui::Separator();
        AutoPlayerSettings* aiSettings = Settings<AutoPlayerSettings>("AutoPlayers");
        NetworkSettings* networkSettings = Settings<NetworkSettings>("Network");

        static int desiredBotCount = 40;
        ImGui::Text("AI SETTINGS");
        ImGui::SliderInt("Total AI Count", &desiredBotCount, 0, 64);
        
        if (ImGui::Button("FORCE START WITH AI"))
        {
            KYBER_LOG(LogLevel::Warning, "Attempting to force start round with AI...");
            aiSettings->ForcedServerAutoPlayerCount = desiredBotCount;
            aiSettings->UpdateAI = true;

            int maxPlayers = networkSettings->MaxClientCount;
            int teamSize = maxPlayers > 0 ? (maxPlayers / 2) : 20;

            aiSettings->ForceFillGameplayBotsTeam1 = teamSize;
            aiSettings->ForceFillGameplayBotsTeam2 = teamSize > 0 ? (teamSize - 1) : 0;

            KYBER_LOG(LogLevel::Warning, "Force start values set: Team1=" << teamSize << ", Team2=" << (teamSize > 0 ? (teamSize - 1) : 0) << ", TotalAI=" << desiredBotCount);
        }
        
        ImGui::Separator();        
        ImGui::Checkbox("AI IGNORE PLAYERS", &aiSettings->ServerPlayersIgnoreClientPlayers);
        ImGui::SameLine();
        if (auto wsSettings = Settings<WSGameSettings>("Whiteshark")) {
             ImGui::Checkbox("AUTO BALANCE TEAMS", &wsSettings->AutoBalanceTeamsOnNeutral);
        }
        
        ImGui::Separator();
        ImGui::Text("PLAYER LIST");
        ServerPlayerManager* playerManager = g_program->m_server->m_playerManager;
        if (playerManager)
        {
            std::map<int32_t, std::vector<ServerPlayer*>> players;
            players[1] = {};
            players[2] = {};
            for (ServerPlayer* player : playerManager->m_players)
            {
                if (player && !player->m_isAIPlayer)
                {
                    players[player->m_teamId].push_back(player);
                }
            }
            if (ImGui::BeginTable("PLAYER LIST", 2, ImGuiTableFlags_SizingFixedFit))
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn(); ImGui::Text("LIGHT SIDE");
                ImGui::TableNextColumn(); ImGui::Text("DARK SIDE");
                for (int i = 0; i < 32; i++)
                {
                    ImGui::TableNextRow();
                    int drew = 0;
                    ImGui::TableNextColumn(); if (DrawScoreboardPlayer(players[1], i)) drew++;
                    ImGui::TableNextColumn(); if (DrawScoreboardPlayer(players[2], i)) drew++;
                    if (!drew) break;
                }
                ImGui::EndTable();
            }
        }
    }
    else
    {
        ImGui::Text("Settings will be available once\nthe game is fully loaded.");
    }
    ImGui::End();
}
}