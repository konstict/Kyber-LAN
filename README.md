# Kyber-LAN
KYBER is a revolutionary custom server platform and mod launcher. But KYBER LAN is a custom server platform to hosting and connecting by Local Area Network (LAN, also by hamachi, radminVPN and other, with which you can have LAN) for Star Wars™ Battlefront™ II (2017) on PC.

<p align="center">
  Site: https://kyber.gg/
  Original: https://github.com/ArmchairDevelopers/Kyber
  Helped: https://github.com/Tratos/Kyber2k19
</p>
  
<p align="center">
  <a href="https://twitter.com/BattleDashBR"><img src="https://img.shields.io/badge/Twitter-@BattleDashBR-1da1f2.svg?logo=twitter"></a>
  <a href="https://discord.gg/kyber">
      <img src="https://img.shields.io/discord/305338604316655616.svg?label=Discord&logo=discord&color=778cd4">
  </a>
</p>

## Why
I had wanted to play with against my friends and now, when there is no way to play with kyber (is being created now Version 2), I can`t to find any methods - how to play. And then I have decided to solve this problem. I'll be glad if it helps someone!

## How to play
Install Bin directory in this github. Then execute KyberLauncher.exe. You need to have installed any "give LAN service", I use RadminVPN, you can also use hamachi and etc.

![image](https://github.com/user-attachments/assets/7d6013bb-f579-419f-b663-f62b23147839)

Then copy IPv4 to have connection (if you host - you send your IP to friends, if friend host - you connecting in his IP).
Next all players start Battlefront 2 and after that click in Inject button.

![image](https://github.com/user-attachments/assets/3e16a1bf-e1a6-4d56-bc70-6460c4bdef32)

If no any errors - in the Game you can to press Insert and have this menu with Server setup and Server browser.

![image](https://github.com/user-attachments/assets/4681c74f-af42-46ed-abd9-8e83bb3b926b)

Now you can to host server to your friend. 

![image](https://github.com/user-attachments/assets/94fdbd1e-8a68-4360-9682-77fbcdc9e529)

When the server ready - client-players can connecting by IP.
And now have fun!

![image](https://github.com/user-attachments/assets/ed6e4944-ce6c-41e6-811e-bc2fa71f9d20)

## How to build

You need to install requirements (by vcpkg?):
Kyber utilizes the following open-source projects:
- [MinHook](https://github.com/TsudaKageyu/minhook)
- [ImGUI](https://github.com/ocornut/imgui)
- [GLFW](https://glfw.org)
- [cpp-httplib](https://github.com/yhirose/cpp-httplib)
- [openssl](https://openssl.org)
- [executors](https://github.com/chriskohlhoff/executors)
- [nlohmann-json](https://github.com/nlohmann/json)

And do make (by cmake?):
```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows-static
cmake --build build --config Release
```
