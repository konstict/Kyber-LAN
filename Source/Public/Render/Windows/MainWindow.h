// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Render/Windows/Window.h>

namespace Kyber
{
class MainWindow : public Window
{
public:
    MainWindow();
    ~MainWindow();
    void Draw() override;
    bool IsEnabled() override;

    Window* m_serverWindow;
    Window* m_clientWindow;
    Window* m_LinkWindow;
};
} // namespace Kyber

extern Kyber::MainWindow* g_mainWindow;