
#include "plugin.h"
#include "Rubbish.h"
#include <filesystem>
#include "debugmenu_public.h"
#include "game_sa\CBike.h"
#include "ini.h"
#include "CMessages.h"
#include "CAudioEngine.h"
using namespace plugin;
DebugMenuAPI gDebugMenuAPI;
namespace fs = std::filesystem;
plugin::ThiscallEvent<AddressList<0x53E175, H_CALL>, PRIORITY_AFTER, ArgPickNone, void()> movingThingsEvent;
plugin::ThiscallEvent <plugin::AddressList<0x6B92F5, plugin::H_CALL>, plugin::PRIORITY_BEFORE, plugin::ArgPickN<CBike*, 0>, void(CBike*)> onProcessControl;
plugin::ThiscallEvent <plugin::AddressList<0x6B19F2, plugin::H_CALL>, plugin::PRIORITY_AFTER, plugin::ArgPickN<CAutomobile*, 0>, void(CAutomobile*)> onProcessControl2;

class RubbishSA {
public:
    RubbishSA() {
        plugin::Events::initRwEvent += []() {
            CRubbish::Init();
        };
        plugin::Events::gameProcessEvent += []() {
            CRubbish::Update();
        };

        movingThingsEvent += []() {
            CRubbish::Render();
        };
        plugin::Events::shutdownRwEvent += []() {
            CRubbish::Shutdown();
        };
        if (DebugMenuLoad()) {
            //DebugMenuAddVar("Rendering", "Rubbish visibility", &CRubbish::RubbishVisibility, NULL, 5.0f, 5.0f, 1000.0f, NULL);
            DebugMenuAddVarBool8("Rendering", "Rubbish invisible", (int8_t*)&CRubbish::bRubbishInvisible, NULL);
        }
        onProcessControl += [](CBike* _this) {
            CRubbish::StirUp(_this);
        };
        if (fs::exists(PLUGIN_PATH((char*)"MODELS\\rubbishSA.ini"))) {
            // The file exists, do nothing
        }
        else {
            MessageBox(HWND_DESKTOP, "rubbishSA.ini cannot be found in models folder. The game will not launch without it.", "RubbishSA.asi", MB_ICONERROR);
            exit(0); // Exit if not found
        }

        onProcessControl2 += [](CAutomobile* _this) {
            CRubbish::StirUp(_this);
        };
        if (fs::exists(PLUGIN_PATH((char*)"MODELS\\RUBBISHSA.TXD"))) {
            // The file exists, do nothing
        }
        else {
            MessageBox(HWND_DESKTOP, "rubbishSA.txd cannot be found in models folder. The game will not launch without it.", "RubbishSA.asi", MB_ICONERROR);
            exit(0); // Exit if not found
        }
    }
} rubbishSA;
