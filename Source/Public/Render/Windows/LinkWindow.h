// Copyright BattleDash. All Rights Reserved.

#pragma once

#include <Render/Windows/Window.h>

#include <Base/Version.h>

namespace Kyber
{
class LinkWindow : public Window
{
public:
    // clang-format off
    const char* LinkText[3] = {
        ("Kyber v" + KYBER_VERSION).c_str(),
        "",
        "https://github.com/konstict/Kyber-LAN"
    };
    // clang-format on

    LinkWindow();
    ~LinkWindow();
    void Draw() override;
    bool IsEnabled() override;
};
} // namespace Kyber