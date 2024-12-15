#include "Hordes_pch.h"

#include "GameEngine.h"

int main() {

    ELog::Log::Get().startup("LeadTheHordes-");

    LTH::GameEngine game;
    game.run();
}
