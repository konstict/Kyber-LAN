// Copyright BattleDash. All Rights Reserved.

#include <Base/Log.h>
#include <API/KyberAPIService.h>
#include <ICMP/IcmpTypes.h>
#include <Core/Program.h>


#include <json/json.hpp>

namespace Kyber
{
KyberAPIService::KyberAPIService()
    : m_client(httplib::SSLClient("kyber.gg"))
    , m_thread_pool(std::experimental::thread_pool(4))
{
    m_client.set_connection_timeout(20);
    m_client.enable_server_certificate_verification(false);
}

void KyberAPIService::GetProxies(std::function<void(std::optional<std::vector<KyberProxy>>)> callback)
{
    callback(std::nullopt);
}

int KyberAPIService::GetPing(std::string ip)
{
    HINSTANCE hIcmp = LoadLibrary("ICMP.DLL");
    if (hIcmp == 0) {
        KYBER_LOG(LogLevel::Error, "Unable to locate ICMP.dll");
        return 0;
    }

    struct hostent* phe;
    if ((phe = gethostbyname(ip.c_str())) == 0) {
        KYBER_LOG(LogLevel::Error, "Could not find IP address for " << ip);
        return 0;
    }

    typedef HANDLE (WINAPI* pfnHV)(VOID);
    typedef BOOL (WINAPI* pfnBH)(HANDLE);
    typedef DWORD (WINAPI* pfnDHDPWPipPDD)(HANDLE, DWORD, LPVOID, WORD,
            PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);
    pfnHV pIcmpCreateFile;
    pfnBH pIcmpCloseHandle;
    pfnDHDPWPipPDD pIcmpSendEcho;
    pIcmpCreateFile = (pfnHV)GetProcAddress(hIcmp, "IcmpCreateFile");
    pIcmpCloseHandle = (pfnBH)GetProcAddress(hIcmp, "IcmpCloseHandle");
    pIcmpSendEcho = (pfnDHDPWPipPDD)GetProcAddress(hIcmp, "IcmpSendEcho");
    if ((pIcmpCreateFile == 0) || (pIcmpCloseHandle == 0) || (pIcmpSendEcho == 0)) 
    {
        KYBER_LOG(LogLevel::Error, "Failed to get proc addr for function.");
        return 0;
    }

    HANDLE hIP = pIcmpCreateFile();
    if (hIP == INVALID_HANDLE_VALUE) 
    {
        KYBER_LOG(LogLevel::Error, "Unable to open ping service.");
        return 0;
    }
   
    char acPingBuffer[64];
    memset(acPingBuffer, '\xAA', sizeof(acPingBuffer));
    PIP_ECHO_REPLY pIpe = (PIP_ECHO_REPLY)GlobalAlloc(
            GMEM_FIXED | GMEM_ZEROINIT,
            sizeof(IP_ECHO_REPLY) + sizeof(acPingBuffer));
    if (pIpe == 0) 
    {
        KYBER_LOG(LogLevel::Error, "Failed to allocate global ping packet buffer.");
        return 0;
    }
    pIpe->Data = acPingBuffer;
    pIpe->DataSize = sizeof(acPingBuffer);      

    DWORD dwStatus = pIcmpSendEcho(hIP, *((DWORD*)phe->h_addr_list[0]), 
            acPingBuffer, sizeof(acPingBuffer), NULL, pIpe, 
            sizeof(IP_ECHO_REPLY) + sizeof(acPingBuffer), 5000);
    if (dwStatus == 0) 
    {
        KYBER_LOG(LogLevel::Error, "Error obtaining info from ping packet.");
        return 0;
    }

    int ping = int(pIpe->RoundTripTime);
    GlobalFree(pIpe);
    return ping;
}

void KyberAPIService::GetServerList(int page, std::function<void(int, std::optional<std::vector<ServerModel>>)> callback)
{
    callback(page, std::nullopt);
}
} // namespace Kyber