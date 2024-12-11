#include "Hordes_pch.h"

#include "GameEngine.h"

int main() {

    EUtil::Log::Get().startup("LeadTheHordes-");

    LTH::GameEngine game;
    game.run();
}
