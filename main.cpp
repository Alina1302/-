#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include "../../LIBRARY/array_functions.h"

using namespace std;


void Record (string record){
    ofstream Coordinates;
    Coordinates.open("Coordinates.txt", ios::app);
    Coordinates<<record<<endl;
    Coordinates.close();
}

void Lost (){
    cout << "You're LOST!";
}
void Win(){
    cout << "You're WIN!";
}
void Winner (string name ){
    cout << name << " is winner!";
}
int GetRandomNumber(int min, int max){
    srand(time(NULL));
    int num = min + rand() % (max - min + 1);
    return num;
}

int main() {
    srand(time(NULL));

    string array;
    string for_record="";
    string name_first, name_second;
    string mode;
    string alphabet[11] = {"Q", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    string numbers[11] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    string field[11][11];
    string field_1[11][11];
    string coordinate_letter;
    int coordinate_index;
    int array_letters[7];
    int array_numbers[7];
    int index_letters = 0;
    int index_numbers = 0;
    bool hit;
    string field_empty_1[11][11];
    int field_in_s_empty[11][11];
    string field_empty_2[11][11];
    int left_or_down;
    bool field_in_s[11][11];
    char yes;
    string letter;
    bool miss_or_not=false;

//Заполнение полей
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= 10; j++) {
            if ((i == 0) && (j != 0)) {
                field[i][j] = alphabet[j];
            }
            if ((j == 0) && (i != 0)) {
                field[i][j] = numbers[i];
            }
            if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                field[i][j] = " ";
            }
            if ((i == 0) && (j != 0)) {
                field_1[i][j] = alphabet[j];
            }
            if ((j == 0) && (i != 0)) {
                field_1[i][j] = numbers[i];
            }
            if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                field_1[i][j] = " ";
            }
            if ((i == 0) && (j != 0)) {
                field_empty_1[i][j] = alphabet[j];
            }
            if ((j == 0) && (i != 0)) {
                field_empty_1[i][j] = numbers[i];
            }
            if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                field_empty_1[i][j] = " ";
            }
            if ((i == 0) && (j != 0)) {
                field_empty_2[i][j] = alphabet[j];
            }
            if ((j == 0) && (i != 0)) {
                field_empty_2[i][j] = numbers[i];
            }
            if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                field_empty_2[i][j] = " ";
            }
            field_in_s[i][j] = false;
            field_in_s_empty[i][j]=0;
        }
    }

//Правила

    /*cout << R"(***Rules***
The goal of the game is to drown all the opponent's combat units.
The player chooses which cell he wants to check.
After which he first calls its letter, and then a number (for example, "E8").
If the second player has a ship in such a cell, the person answers "hit" or "killed".
The attacker puts a cross in the right place on the drawn empty field.
After being hit, a person gets the right to another shot.

When he calls the cell that the opponent has empty, he will answer "by".
After that, the move goes to the second player.
The winner is the one who first discovered all the opponent's vessels.

***the fleet consists of ***
    one four - deck
    two three - deck
    three two - deck
    four single - deck)";*/

    cout << "\nIf you want to continue, enter your name, else enter 'exit' and you will lost!\n";
    cin >> name_first;
    if (name_first == "exit") {
        Lost();
        return 0;
    } else {
        cout << "Now you can choose the mode. Doubles -> 'd' or singles -> 's'\t:";
        enter_the_mode:
        cin >> mode;
        if (mode == "d") {
            cout << "OK, then enter the name of the second player: ";
            cin >> name_second;
            cout << "Well, now we should arrange the ships. " << name_first << " will be first" << endl;
            cout << "This is blank field\n\n";
//Вывод незаполненного поля
            for (int i = 0; i < 11; ++i) {
                for (int j = 0; j < 11; ++j)
                    if (i == 0 && j != 0) {
                        cout << field[i][j] << " | ";
                    } else if (i != 10) {
                        cout << field[i][j] << " |  ";
                    } else {
                        cout << field[i][j] << "|   ";
                    }
                cout << endl;
            }
            int j = 1;
            int s = 1;
            int trust = 0;
            int domn = 0;
            int sch = 1;

//Ввод координат, раставление плюсов на месте кораблей
            do {
                switch (j) {
                    case 1:
                        domn = 4;
                        break;
                    case 4:
                        domn = 4;
                        break;
                    case 2:
                        domn = 6;
                        break;
                    case 3:
                        domn = 6;
                        break;
                    default:
                        cerr << "ERROR IN SWITCH ";
                }
                do {
                    cout << "Enter the coordinates of the " << j << "-deck. Each coordinate enter with 'enter'\n";
                    cin >> coordinate_letter >> coordinate_index;
                    array_numbers[index_numbers] = coordinate_index;
                    for (int i = 1; i < 11; i++) {
                        if (coordinate_letter == alphabet[i]) {
                            array_letters[index_letters] = i;
                        }
                    }
                    index_letters++;
                    index_numbers++;
                    s++;
                } while (s <= domn);
                j++;
                for (int i = 0; i <= domn - 1; i++) {
                    field[array_numbers[i]][array_letters[i]] = "+";
                }
                index_letters = 0;
                index_numbers = 0;
                sch = 1;
                s = 1;
            } while (j <= 4);


            for (int i = 0; i < 11; ++i) {
                for (int j = 0; j < 11; ++j) {
                    if (i == 0) {
                        cout << "|" << field[i][j];
                    } else {
                        if (j == 0) {
                            cout << field[i][j];
                        } else {
                            if (field[i][j] != "+" && j != 10) {
                                cout << "  " << field[i][j];
                            } else {
                                if (field[i][j] != "+" && j == 10) {
                                    cout << " " << field[i][j];
                                } else {
                                    if (field[i][j] == "+" && j != 10) {
                                        cout << " " << field[i][j];
                                    } else {
                                        cout << " " << field[i][j];
                                    }
                                }
                            }
                        }
                    }
                }
                cout << endl;
            }

//Второй игрок вводит свои координаты
            j = 1;
            s = 1;
            domn = 0;
            sch = 1;
            do {
                cout << j;
                switch (j) {
                    case 1:
                        domn = 4;
                        break;
                    case 4:
                        domn = 4;
                        break;
                    case 2:
                        domn = 6;
                        break;
                    case 3:
                        domn = 6;
                        break;
                    default:
                        cerr << "ERROR IN SWITCH ";
                }
                do {
                    cout << "Enter the coordinates of the " << j << "-deck. Each coordinate enter with 'enter'\n";
                    cin >> coordinate_letter >> coordinate_index;
                    array_numbers[index_numbers] = coordinate_index;
                    for (int i = 1; i < 11; i++) {
                        if (coordinate_letter == alphabet[i]) {
                            array_letters[index_letters] = i;
                        }
                    }
                    index_letters++;
                    index_numbers++;
                    s++;
                } while (s <= domn);
                j++;
                for (int i = 0; i <= domn - 1; i++) {
                    field_1[array_numbers[i]][array_letters[i]] = "+";
                }
                index_letters = 0;
                index_numbers = 0;
                sch = 1;
                s = 1;
            } while (j <= 4);

//Вывод массива с +
            for (int i = 0; i < 11; ++i) {
                for (int j = 0; j < 11; ++j) {
                    if (i == 0) {
                        cout << "|" << field_1[i][j];
                    } else {
                        if (j == 0) {
                            cout << field_1[i][j];
                        } else {
                            if (field_1[i][j] != "+" && j != 10) {
                                cout << "  " << field_1[i][j];
                            } else {
                                if (field_1[i][j] != "+" && j == 10) {
                                    cout << " " << field_1[i][j];
                                } else {
                                    if (field_1[i][j] == "+" && j != 10) {
                                        cout << " " << field_1[i][j];
                                    } else {
                                        cout << " " << field_1[i][j];
                                    }
                                }
                            }
                        }
                    }
                }
                cout << endl;
            }

            cout << "Well, when all ships are in the field, we can start game! Good luck\n";
            cout << name_first << " will be first. Enter the coordinates\n";
            int hit_1 = 0, hit_2 = 0;

//САМА ИГРА

            while (true) {

//FIRST_PLAYER_COORDINATES

                first_player_coordinates:
                cin >> coordinate_letter >> coordinate_index;
//индекс по букве
                for (int i = 1; i < 11; i++) {
                    if (coordinate_letter == alphabet[i]) {
                        index_letters = i;
                        break;
                    }
                }
//Сначала строка потом столбец


                if (field_1[coordinate_index][index_letters] == "+") {
                    cout << name_first << " is hit\n";
                    field_1[coordinate_index][index_letters] = "%";
                    field_empty_2[coordinate_index][index_letters] = "%";
                    hit_1 += 1;
                    hit = true;
                } else {
                    cout << name_first << " is miss\n";
                    field_empty_2[coordinate_index][index_letters] = "¶";
                    field_1[coordinate_index][index_letters] = "¶";
                    hit = false;
                }
//Безусловный переход на first_player_coordinates
                if ((hit) && (hit_1 < 20)) {
                    cout << name_first << " you can enter the coordinates one more time!\n";
                    coordinate_index = 0;
                    index_letters = 0;
                    coordinate_letter = "0";
                    goto first_player_coordinates;
                } else {
                    if (hit_1 == 20) {
                        goto label_for_exit;
                    }
                }
//Вывод массива
                for (int i = 0; i < 11; ++i) {
                    for (int j = 0; j < 11; ++j) {
                        if (i == 0) {
                            cout << "|" << field_empty_2[i][j];
                        } else {
                            if (j == 0) {
                                cout << field_empty_2[i][j];
                            } else {
                                if ((field_1[i][j] != "+") && field_1[i][j] != "%" && field_1[i][j] != "¶" && j != 10) {
                                    cout << "  " << field_empty_2[i][j];
                                } else {
                                    if (field_1[i][j] != "+" && field_1[i][j] != "%" && field_1[i][j] != "¶" &&
                                        j == 10) {
                                        cout << " " << field_empty_2[i][j];
                                    } else {
                                        if ((field_1[i][j] == "+" || field_1[i][j] != "%" || field_1[i][j] != "¶") &&
                                            j != 10) {
                                            cout << " " << field_empty_2[i][j];
                                        } else {
                                            cout << " " << field_empty_2[i][j];
                                        }
                                    }
                                }
                            }
                        }
                    }
                    cout << endl;
                }


                coordinate_index = 0;
                index_letters = 0;
                coordinate_letter = "0";


                cout << name_second << ". Enter the coordinates!\n";
//SECOND_PLAYER_COORDINATES
                second_player_coordinates:
                cin >> coordinate_letter >> coordinate_index;
//индекс по букве
                for (int i = 1; i < 11; i++) {
                    if (coordinate_letter == alphabet[i]) {
                        index_letters = i;
                        break;
                    }
                }

                if (field[coordinate_index][index_letters] == "+") {
                    cout << name_second << " is hit\n";
                    field[coordinate_index][index_letters] = "%";
                    field_empty_1[coordinate_index][index_letters] = "%";
                    hit_2 += 1;
                    hit = true;
                } else {
                    cout << name_second << " is miss\n";
                    field_empty_1[coordinate_index][index_letters] = "¶";
                    field[coordinate_index][index_letters] = "¶";
                    hit = false;
                }
//Безусловный переход к SECOND_PLAYER_COORDINATES
                if ((hit) && (hit_2 < 20)) {
                    cout << name_second << " you can enter the coordinates one more time!\n";
                    coordinate_index = 0;
                    index_letters = 0;
                    coordinate_letter = "0";
                    goto second_player_coordinates;
                } else {
                    if (hit_2 == 20) {
                        goto label_for_exit;
                    }
                }

                for (int i = 0; i < 11; ++i) {
                    for (int j = 0; j < 11; ++j) {
                        if (i == 0) {
                            cout << "|" << field_empty_1[i][j];
                        } else {
                            if (j == 0) {
                                cout << field_empty_1[i][j];
                            } else {
                                if ((field[i][j] != "+") && field[i][j] != "%" && field[i][j] != "¶" && j != 10) {
                                    cout << "  " << field_empty_1[i][j];
                                } else {
                                    if (field[i][j] != "+" && field[i][j] != "%" && field[i][j] != "¶" && j == 10) {
                                        cout << " " << field_empty_1[i][j];
                                    } else {
                                        if ((field[i][j] == "+" || field[i][j] != "%" || field[i][j] != "¶") &&
                                            j != 10) {
                                            cout << " " << field_empty_1[i][j];
                                        } else {
                                            cout << " " << field_empty_1[i][j];
                                        }
                                    }
                                }
                            }
                        }
                    }
                    cout << endl;
                }

                label_for_exit:

                if (hit_1 == 20 || hit_2 == 20) {
                    break;
                } else {
                    cout << name_first << ". Enter the coordinates\n";
                }


                coordinate_index = 0;
                index_letters = 0;
                coordinate_letter = "0";
            }
            if (hit_1 == 20) {
                Winner(name_first);
            } else {
                Winner(name_second);
            }


        } else if (mode == "s") {

//Вывод незаполненного поля

            for (int i = 0; i < 11; ++i) {
                for (int j = 0; j < 11; ++j)
                    if (i == 0 && j != 0) {
                        cout << field[i][j] << " | ";
                    } else if (i != 10) {
                        cout << field[i][j] << " |  ";
                    } else {
                        cout << field[i][j] << "|   ";
                    }
                cout << endl;
            }

            int j = 1;
            int s = 1;
            int trust = 0;
            int domn = 0;

//Неудачная попытка рандомного расположения кораблей
/*Четырехпалубный{

            index_numbers = GetRandomNumber(1, 10);
            index_letters = GetRandomNumber(1, 7);
            field_in_s[index_numbers][index_letters] = 1;
            field_in_s[index_numbers][index_letters + 1] = 1;
            field_in_s[index_numbers][index_letters + 2] = 1;
            field_in_s[index_numbers][index_letters + 3] = 1;
            //up
            field_in_s[index_numbers + 1][index_letters] = 0;
            field_in_s[index_numbers + 1][index_letters + 1] = 0;
            field_in_s[index_numbers + 1][index_letters + 2] = 0;
            field_in_s[index_numbers + 1][index_letters + 3] = 0;
            //down
            field_in_s[index_numbers - 1][index_letters] = 0;
            field_in_s[index_numbers - 1][index_letters + 1] = 0;
            field_in_s[index_numbers - 1][index_letters + 2] = 0;
            field_in_s[index_numbers - 1][index_letters + 3] = 0;
            //l+r
            field_in_s[index_numbers][index_letters - 1] = 0;
            field_in_s[index_numbers][index_letters + 4] = 0;
            //corner
            field_in_s[index_numbers - 1][index_letters - 1] = 0;
            field_in_s[index_numbers - 1][index_letters + 1] = 0;
            field_in_s[index_numbers + 1][index_letters + 4] = 0;
            field_in_s[index_numbers - 1][index_letters + 4] = 0;


            while (true){
                index_numbers= GetRandomNumber(1, 8);
                index_letters= GetRandomNumber(1, 10);
                if (field_in_s[index_numbers][index_letters]!=3){
                    continue;
                }else{
                    break;
                }
            }
*/
//заполнение 1 field_in_s

                field_in_s[1][2] = true;
                field_in_s[2][4] = true;
                field_in_s[2][5] = true;
                field_in_s[2][6] = true;
                field_in_s[2][7] = true;
                field_in_s[3][10] = true;
                field_in_s[4][1] = true;
                field_in_s[5][1] = true;
                field_in_s[6][1] = true;
                field_in_s[5][3] = true;
                field_in_s[5][4] = true;
                field_in_s[5][9] = true;
                field_in_s[5][10] = true;
                field_in_s[7][3] = true;
                field_in_s[8][6] = true;
                field_in_s[9][6] = true;
                field_in_s[10][2] = true;
                field_in_s[10][3] = true;
                field_in_s[10][4] = true;
                field_in_s[8][9] = true;


//Ввод координат игроком и вывод заполненного поля

            do {
                switch (j) {
                    case 1:
                        domn = 4;
                        break;
                    case 4:
                        domn = 4;
                        break;
                    case 2:
                        domn = 6;
                        break;
                    case 3:
                        domn = 6;
                        break;
                    default:
                        cerr << "ERROR IN SWITCH 2 ";
                }
                do {
                    cout << "Enter the coordinates of the " << j << "-deck. Each coordinate enter with 'enter'\n";
                    cin >> coordinate_letter >> coordinate_index;
                    array_numbers[index_numbers] = coordinate_index;
                    for (int i = 1; i < 11; i++) {
                        if (coordinate_letter == alphabet[i]) {
                            array_letters[index_letters] = i;
                        }
                    }
                    index_letters++;
                    index_numbers++;
                    s++;
                } while (s <= domn);
                j++;
                for (int i = 0; i <= domn - 1; i++) {
                    field[array_numbers[i]][array_letters[i]] = "+";
                    field_in_s_empty[array_numbers[i]][array_letters[i]]=1;
                }
                index_letters = 0;
                index_numbers = 0;
                s = 1;

            } while (j <= 4);
//Вывод массива
            for (int i = 0; i < 11; ++i) {
                for (int j = 0; j < 11; ++j) {
                    if (i == 0) {
                        cout << "|" << field[i][j];
                    } else {
                        if (j == 0) {
                            cout << field[i][j];
                        } else {
                            if (field[i][j] != "+" && j != 10) {
                                cout << "  " << field[i][j];
                            } else {
                                if (field[i][j] != "+" && j == 10) {
                                    cout << " " << field[i][j];
                                } else {
                                    if (field[i][j] == "+" && j != 10) {
                                        cout << " " << field[i][j];
                                    } else {
                                        cout << " " << field[i][j];
                                    }
                                }
                            }
                        }
                    }
                }
                cout << endl;
            }
//САМА ИГРА

            int hit_1=0, hit_2=0;

            cout <<"You should be first.\n";
            while (true){
                cout<<name_first<< ". Enter the coordinates";
//player enter coordinates
                player_enter_coordinates:
                cin>>coordinate_letter>>coordinate_index;
//Индкекс по букве
                for (int i=1; i<11; i++){
                    if (alphabet[i]==coordinate_letter){
                        index_letters=i;
                    }
                }

//Проверка, попал игрок или нет

                if (field_in_s[coordinate_index][index_letters]){
                    cout << "\nYou're hit!\n";
                    field_in_s[coordinate_index][index_letters]=false;
                    hit_1+=1;
                    hit=true;
                }else{
                    cout << "\nYou're miss(\n";
                    hit = false;
                }
                if (hit && hit_1!=20){
                    cout << name_first << ". You can enter the coordinates one more time!\n";
                    goto player_enter_coordinates;
                }else{
                    if (hit_1==20){
                        goto little_win;
                    }
                }
//bot enter coordinates
                bot_enter_coordinates:
                index_letters= GetRandomNumber(1,10);
                letter=alphabet[index_letters];
                coordinate_index= GetRandomNumber(1,10);
                for_record=letter;
                for_record+=coordinate_index;
                if (array.find(for_record)>=0 && array.find(for_record)<=array.size()){
                    goto bot_enter_coordinates;
                }else{
                    cout << letter <<" "<< coordinate_index;
                    array+=for_record;
                    for_record="";
                }
                if (field_in_s_empty[coordinate_index][index_letters]==3){
                    coordinate_index=0;
                    index_letters=0;
                    coordinate_letter="";
                    hit = false;
                    goto bot_enter_coordinates;
                }else{
                    if (field_in_s_empty[coordinate_index][index_letters]==1){
                        cout << "\nHit!\n";
                        field_in_s_empty[coordinate_index][index_letters]=3;
                        hit_2+=1;
                        hit=true;
                        field[coordinate_index][index_letters]="%";

                    }else {
                        cout << "\nMiss\n";
                        field_in_s_empty[coordinate_index][index_letters]=3;
                        hit = false;
                        goto player_enter_coordinates;
                    }
                }
                if (hit && hit_2!=20){
                    coordinate_index=0;
                    index_letters=0;
                    coordinate_letter="";
                    goto bot_enter_coordinates;
                }else{
                    if (hit_2==20){
                        goto little_win;
                    }else {
                        continue;
                    }
                }
                little_win:
                if (hit_1!=20 && hit_2!=20){
                    continue;
                }else{
                    break;
                }

            }
            if (hit_1==20){
                Win();
            }else{
                Lost();
            }
        } else {
            cerr << "Error in choosing the mode\n";
            cout << "Do you want to enter the mode again? yes -> 'y'\n";
            cin >> yes;
            if (yes=='y'){
                cout << "Enter: ";
                goto enter_the_mode;
            }else{
                Lost();
            }
        }
    }

    return 0;
}