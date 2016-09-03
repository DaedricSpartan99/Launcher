#include "mainwindow.h"
#include "account.h"
#include "temp.h"
#include "Windows.h"
#include <cstdio>
#include <stdlib.h>
#include <direct.h>
#include <iostream>

using namespace std;

void TxtTemp::logcmd(const string& cmd) {

    cout << cmd << endl;

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    wchar_t wpath[2048]; // 50 kb
    mbstowcs(wpath, (path + filename).c_str(), (path + filename).size()+1);
    LPWSTR wfile = wpath;

    HANDLE h = CreateFile(wfile,
       FILE_APPEND_DATA,
       FILE_SHARE_WRITE | FILE_SHARE_READ,
       &sa,
       OPEN_ALWAYS,
       FILE_ATTRIBUTE_NORMAL,
       NULL );

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdInput = NULL;
    si.hStdError = h;
    si.hStdOutput = h;

    wchar_t wtext[51200]; // 50 kb
    mbstowcs(wtext, cmd.c_str(), cmd.size()+1);
    LPWSTR wcmd = wtext;

    if( !CreateProcess( NULL,   // No module name (use command line)
            wcmd,        // Command line
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            TRUE,          // Set handle inheritance to FALSE
            CREATE_NO_WINDOW,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory
            &si,            // Pointer to STARTUPINFO structure
            &pi )           // Pointer to PROCESS_INFORMATION structure
        )
    {
         printf( "CreateProcess failed (%d).\n", GetLastError() );
         return;
    }

    WaitForSingleObject( pi.hProcess, INFINITE );
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}

string gencmd(const string& nick, const string& uuid, const string& mc_dir, const string& lbdg_dir) {

    string cmd = "";

    //cmd += "cd " + mc_dir + " && ";
    cmd += "cmd /c D:\\Programmi\\Minecraft\\runtime\\jre-x64\\1.8.0_25\\bin\\javaw.exe ";
    //cmd += "-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump ";
    cmd += "-Xmx1G -XX:+UseConcMarkSweepGC -XX:+CMSIncrementalMode -XX:-UseAdaptiveSizePolicy ";
    cmd += "-Xmn128M \"-Dos.name=Windows 10\" -Dos.version=10.0 ";
    cmd += "-Djava.library.path=" + lbdg_dir + "LaBiscaDeiGamer-natives ";
    cmd += "-cp ";
    cmd += mc_dir + "libraries\\com\\mojang\\netty\\1.6\\netty-1.6.jar;";
    cmd += mc_dir + "libraries\\oshi-project\\oshi-core\\1.1\\oshi-core-1.1.jar;";
    cmd += mc_dir + "libraries\\net\\java\\dev\\jna\\jna\\3.4.0\\jna-3.4.0.jar;";
    cmd += mc_dir + "libraries\\net\\java\\dev\\jna\\platform\\3.4.0\\platform-3.4.0.jar;";
    cmd += mc_dir + "libraries\\com\\ibm\\icu\\icu4j-core-mojang\\51.2\\icu4j-core-mojang-51.2.jar;";
    cmd += mc_dir + "libraries\\net\\sf\\jopt-simple\\jopt-simple\\4.6\\jopt-simple-4.6.jar;";
    cmd += mc_dir + "libraries\\com\\paulscode\\codecjorbis\\20101023\\codecjorbis-20101023.jar;";
    cmd += mc_dir + "libraries\\com\\paulscode\\codecwav\\20101023\\codecwav-20101023.jar;";
    cmd += mc_dir + "libraries\\com\\paulscode\\libraryjavasound\\20101123\\libraryjavasound-20101123.jar;";
    cmd += mc_dir + "libraries\\com\\paulscode\\librarylwjglopenal\\20100824\\librarylwjglopenal-20100824.jar;";
    cmd += mc_dir + "libraries\\com\\paulscode\\soundsystem\\20120107\\soundsystem-20120107.jar;";
    cmd += mc_dir + "libraries\\io\\netty\\netty-all\\4.0.23.Final\\netty-all-4.0.23.Final.jar;";
    cmd += mc_dir + "libraries\\com\\google\\guava\\guava\\17.0\\guava-17.0.jar;";
    cmd += mc_dir + "libraries\\org\\apache\\commons\\commons-lang3\\3.3.2\\commons-lang3-3.3.2.jar;";
    cmd += mc_dir + "libraries\\commons-io\\commons-io\\2.4\\commons-io-2.4.jar;";
    cmd += mc_dir + "libraries\\commons-codec\\commons-codec\\1.9\\commons-codec-1.9.jar;";
    cmd += mc_dir + "libraries\\net\\java\\jinput\\jinput\\2.0.5\\jinput-2.0.5.jar;";
    cmd += mc_dir + "libraries\\net\\java\\jutils\\jutils\\1.0.0\\jutils-1.0.0.jar;";
    cmd += mc_dir + "libraries\\com\\google\\code\\gson\\gson\\2.2.4\\gson-2.2.4.jar;";
    cmd += mc_dir + "libraries\\com\\mojang\\authlib\\1.5.21\\authlib-1.5.21.jar;";
    cmd += mc_dir + "libraries\\com\\mojang\\realms\\1.7.39\\realms-1.7.39.jar;";
    cmd += mc_dir + "libraries\\org\\apache\\commons\\commons-compress\\1.8.1\\commons-compress-1.8.1.jar;";
    cmd += mc_dir + "libraries\\org\\apache\\httpcomponents\\httpclient\\4.3.3\\httpclient-4.3.3.jar;";
    cmd += mc_dir + "libraries\\commons-logging\\commons-logging\\1.1.3\\commons-logging-1.1.3.jar;";
    cmd += mc_dir + "libraries\\org\\apache\\httpcomponents\\httpcore\\4.3.2\\httpcore-4.3.2.jar;";
    cmd += mc_dir + "libraries\\org\\apache\\logging\\log4j\\log4j-api\\2.0-beta9\\log4j-api-2.0-beta9.jar;";
    cmd += mc_dir + "libraries\\org\\apache\\logging\\log4j\\log4j-core\\2.0-beta9\\log4j-core-2.0-beta9.jar;";
    cmd += mc_dir + "libraries\\org\\lwjgl\\lwjgl\\lwjgl\\2.9.4-nightly-20150209\\lwjgl-2.9.4-nightly-20150209.jar;";
    cmd += mc_dir + "libraries\\org\\lwjgl\\lwjgl\\lwjgl_util\\2.9.4-nightly-20150209\\lwjgl_util-2.9.4-nightly-20150209.jar;";
    cmd += mc_dir + "libraries\\tv\\twitch\\twitch\\6.5\\twitch-6.5.jar;";
    cmd += mc_dir + "versions\\LaBiscaDeiGamer\\LaBiscaDeiGamer.jar ";
    cmd += "net.minecraft.client.main.Main ";
    cmd += "--username " + nick + " ";
    cmd += "--version LaBiscaDeiGamer ";
    cmd += "--gameDir " + mc_dir + " ";
    cmd += "--assetsDir " + mc_dir + "assets ";
    cmd += "--assetIndex 1.8 ";
    cmd += "--uuid " + uuid + " ";
    cmd += "--accessToken null ";
    cmd += "--userProperties {} ";
    cmd += "--userType legacy ";
    //cmd += "--nativeLauncherVersion 301  6896";
    //cmd += " exit";

    return cmd;
}

void Account::requestUuid() {

    string cmd = "java -jar httpreq.jar get https://api.mojang.com/users/profiles/minecraft/" + username;
    TxtTemp * f = new TxtTemp(".request.txt", file->getPath());

    f->logcmd(cmd);

    string res = f->lastLine();

    std::cout << "Request output: " << ((res != "") ? res : "null") << std::endl;

    size_t pos = res.find("\"id\":\"");

    if (pos == string::npos)
        uuid = "null";

    else {

        uuid = res.substr(7, 32);
    }

    f->remove();
    delete f;
}
