#include "plugin.h"
#include "Rubbish.h"
#include <filesystem>
#include "debugmenu_public.h"
#include "game_sa\CBike.h"
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
        patch:
        if (DebugMenuLoad()) {
            //DebugMenuAddVar("Rendering", "Rubbish visibility", &CRubbish::RubbishVisibility, NULL, 5.0f, 5.0f, 1000.0f, NULL);
            DebugMenuAddVarBool8("Rendering", "Rubbish invisible", (int8_t*)&CRubbish::bRubbishInvisible, NULL);
        }
        onProcessControl += [](CBike* _this) {
            CRubbish::StirUp(_this);
        };
        onProcessControl2 += [](CAutomobile* _this) {
            CRubbish::StirUp(_this);
        };
        if (fs::exists(GAME_PATH((char*)"MODELS\\RUBBISHSA.TXD"))) {
            // The file exists, do nothing
        }
        else {
            MessageBox(HWND_DESKTOP, "RubbishSA.txd cannot be found in models folder. The game will continue to load, but will crash on loading screen.", "rubbishSA.asi", MB_ICONERROR);

        }
    }
} rubbishSA;
