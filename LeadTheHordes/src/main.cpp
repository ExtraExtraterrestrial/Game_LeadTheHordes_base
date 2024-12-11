#include "Hordes_pch.h"
#include "GameEngine.h"


int main() {

    EUtil::Log::Get().startup("LeadTheHordes__");

    LTH::GameEngine game;
    game.run();
}
