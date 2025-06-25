# Kyber-LAN
KYBER это революционная платформа для кастомного сервера и лаунчера модов. Но KYBER LAN это платформа для каостомного сервера для хостинга и подключения по локальной сети (LAN, также hamachi, radminVPN и другие, которые позволяют получить LAN) для Star Wars™ Battlefront™ II (2017) на ПК.

<p align="center">
  Сайт: https://kyber.gg/
  Оригинал: https://github.com/ArmchairDevelopers/Kyber
  Помогло: https://github.com/Tratos/Kyber2k19
</p>
  
<p align="center">
  <a href="https://twitter.com/BattleDashBR"><img src="https://img.shields.io/badge/Twitter-@BattleDashBR-1da1f2.svg?logo=twitter"></a>
  <a href="https://discord.gg/kyber">
      <img src="https://img.shields.io/discord/305338604316655616.svg?label=Discord&logo=discord&color=778cd4">
  </a>
</p>

## Почему
Я хотел поиграть против своих друзей и сейчас, когда нет способов это сделать через Kyber (сейчас создается версия 2), я не мог найти никаких других способов - как поиграть. И сейчас я решил это исправить. Я буду рад, если это кому-нибудь поможет!

## Как играть
Скачайте Bin директорию с гитхаба. Затем запустите KyberLauncher.exe. У вас должен быть установлен "раздаватель LAN подключения сервис", и использую RadminVPN, вы можете также использовать hamachi and др.

![image](https://github.com/user-attachments/assets/7d6013bb-f579-419f-b663-f62b23147839)

Далее для подключений скопируйте IPv4 (если вы хости - отправьте друзьям ваш айпи, если друг хост - подключайтесь по его айпи).
Затем все игроки запускают Battlefront 2 и после этого жмут кнопку inject в приложении.

![image](https://github.com/user-attachments/assets/3e16a1bf-e1a6-4d56-bc70-6460c4bdef32)

Если нет ошибок - то в игре вы можете нажать insert и откроется меню выбора между созданием сервера и подключением.

![image](https://github.com/user-attachments/assets/4681c74f-af42-46ed-abd9-8e83bb3b926b)

Сейчас вы можете хостить сервер. 

![image](https://github.com/user-attachments/assets/94fdbd1e-8a68-4360-9682-77fbcdc9e529)

Когда сервер готов - клиент-игроки могут подключиться по айпи.
И фаньтесь!

![image](https://github.com/user-attachments/assets/ed6e4944-ce6c-41e6-811e-bc2fa71f9d20)

## Как собрать

Вам нужно установить следующие зависимости (by vcpkg?):
Kyber utilizes the following open-source projects:
- [MinHook](https://github.com/TsudaKageyu/minhook)
- [ImGUI](https://github.com/ocornut/imgui)
- [GLFW](https://glfw.org)
- [cpp-httplib](https://github.com/yhirose/cpp-httplib)
- [openssl](https://openssl.org)
- [executors](https://github.com/chriskohlhoff/executors)
- [nlohmann-json](https://github.com/nlohmann/json)

И собирайте (by cmake?):
```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows-static
cmake --build build --config Release
```
