#include <iostream>
#include "Render.h"

void menu(int menu_option, Render M) {
    
}

int main(){
    Render R;
    R.clearScreen();

    bool isMenu = true;
    int menu_option = 0;
    int s = 10; // skala awal

    R.showMenu(menu_option, isMenu);
    for(;;){
        if (R.getTerminal().getIsInput() == (int)State::RECEIVED) {
			char input = R.getTerminal().getInput();
            // std::cout << isMenu;
            if (isMenu) {
                switch (input){
                    case 'w': menu_option++; break;
                    case 'a': menu_option--; break;
                    case 's': menu_option--; break;
                    case 'd': menu_option++; break;
                    case 'i': isMenu = false; break;
                    case 'o': // select the menu
                        if (menu_option == 0) {
                            R.getAssetCount() = 0;
                            R.loadAsset("map.txt");
                        }
                        else if (menu_option == 3) {
                            R.changeIsColor();
                            R.drawAll();
                        }
                        isMenu = false;
                        break;
                    default:
                        break;
                }
                if (menu_option < 0) {
                    menu_option = 0;
                }
                if (menu_option > 4) {
                    menu_option = 4;
                }
            }
            else {
                // std::cout << "masuk?";
                switch (input){
                    case 'w':
                        if (menu_option == 0) {
                            R.resetAssetCount();
                            R.loadAsset("heli.txt");
                        }
                        else if (menu_option == 1) {
                            R.translate(0, -10);
                        }
                        else if (menu_option == 2) {
                            s--;
                            if (s < 1) {
                                s = 1;
                            }
                            else {
                                R.skala(s+1, s);
                            }
                        }
                        break;
                    case 'a':
                        if (menu_option == 0) {
                            R.resetAssetCount();
                            R.loadAsset("map.txt");
                        }
                        if (menu_option == 1) {
                            R.translate(-10, 0);
                        }
                        else if (menu_option == 2) {
                            s--;
                            if (s < 1) {
                                s = 1;
                            }
                            else {
                                R.skala(s+1, s);
                            }
                        }
                        break;
                    case 's':
                        if (menu_option == 0) {
                            R.resetAssetCount();
                            R.loadAsset("map.txt");
                        }
                        else if (menu_option == 1) {
                            R.translate(0, 10);
                        }
                        else if (menu_option == 2) {
                            s++;
                            R.skala(s-1, s);
                        }
                        break;
                    case 'd':
                        if (menu_option == 0) {
                            R.resetAssetCount();
                            R.loadAsset("heli.txt");
                        }
                        else if (menu_option == 1) {
                            R.translate(10, 0);
                        }
                        else if (menu_option == 2) {
                            s++;
                            R.skala(s-1, s);
                        }
                        break;
                    case 'i':
                        isMenu = true;
                        break;
                    case 'o':
                        isMenu = true;
                        break;
                    default:
                        break;
                }
            }

            // Show menu
            R.showMenu(menu_option, isMenu);

            R.getTerminal().setIsInput(State::WAITING);
        }
        else if (R.getTerminal().getIsInput() == (int)State::STOP) {
            R.getTerminal().exit();
            break;
        }
    }

    return 0;
}