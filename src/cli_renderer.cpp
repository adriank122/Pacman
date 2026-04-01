#include "cli_renderer.h"
#include "platform_utils.h"
#include "game.h"
#include "map.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

CLIRenderer::CLIRenderer() {
}

CLIRenderer::~CLIRenderer() {
}

void CLIRenderer::clear() {
    clear_screen();
}

char CLIRenderer::getChar() {
    return get_char();
}

bool CLIRenderer::keyAvailable() {
    return key_available();
}

void CLIRenderer::sleep(int milliseconds) {
    sleep_ms(milliseconds);
}

void CLIRenderer::showMenu() {
    clear();
    cout<<"\t\tPACMAN by Adrian Kaliciecki\n\n\n";
    cout<<"Wcisnij:\n\n";
    cout<<"1 -->\tNowa gra\n";
    cout<<"2 -->\tInstrukcja\n";
    cout<<"3 -->\tRanking\n";
    cout<<"4 -->\tWyjscie\n\n";
}

void CLIRenderer::showGameState(const SGame &game) {
    clear();
    showMap(game.map);
    showGameCounter(game);
}

void CLIRenderer::showMap(const SMap &map) {
    for(int i=0; i<17; i++) {
        for(int j=0; j<20; j++) {
            cout << setw(2) << map.map[i][j];
        }
        cout << "\n";
    }
}

void CLIRenderer::showGameCounter(const SGame &game) {
    cout<<"Pozostaly czas: "<<game.stoper/1000<<"\n\n";
    cout<<"Punkty: "<<game.pman.points<<"\n\n";
    
    int food_count = 0;
    for(int i=0; i<17; i++) {
        for(int j=0; j<20; j++) {
            if(game.map.map[i][j]=='.' || game.map.map[i][j]=='e')
                food_count++;
        }
    }
    cout<<"Suma ciasteczek: "<<food_count<<"\n\n";
    cout<<"Ilosc zyc: "<<game.pman.lives<<"\n\n";
}

void CLIRenderer::showGameOver(const std::string &reason) {
    clear();
    if(reason == "lives") {
        cout<<"Koniec gry!\n\n\nWyczerpales limit zyc.\n\n\nWpisz swoje imie i zatwierdz enterem:\n\n";
    } else if(reason == "time") {
        cout<<"Koniec gry!\n\n\nWyczerpales limit czasu.\n\n\nWcisnij enter, aby wrocic do menu\n\n";
    } else if(reason == "won") {
        cout<<"Zjadles wszystkie ciasteczka i ukonczyles poziom!\n\n\nWcisnij 'o', aby przejsc do nastepnego poziomu.\n\n";
        cout<<"Wcisnij 'm', aby wrocic do menu glownego.\n\n";
    }
}

void CLIRenderer::showInstructions() {
    clear();
    cout<<"\nW --> ruch do gory\n";
    cout<<"A --> ruch w lewo\n";
    cout<<"S --> ruch do dolu\n";
    cout<<"D --> ruch w prawo\n\n";
    cout<<"Zbierz wszystkie ciasteczka, aby przejsc etap!\nNie daj sie zjesc duchom.\n";
    cout<<"Masz trzy zycia\n\n\n\n";
    cout<<"1 -->Wroc do menu\n";
}

void CLIRenderer::showRanking() {
    clear();
    cout<<"Lista wynikow graczy:\n";
    showRankingList();
    cout<<"\n\n\n";
    cout<<"1 --> Wroc do menu glownego";
}

void CLIRenderer::showRankingList() {
    cout<<"\n\n\n";
    string napis;
    ifstream we;
    we.open("ranking.txt");
    while(!we.eof()) {
        getline(we, napis);
        cout<<napis<<"\n\n";
    }
    we.close();
}
