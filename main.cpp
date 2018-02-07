#include <iostream>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <conio.h>
#include <string>

using namespace std;

void generate_pattern(int pattern[])
{
    srand(time(NULL));
    for(int i = 0; i < 4; i++)
    {
        do
        {
            pattern[i] = (rand()%8) + 1;
        }
        while (pattern[i] == pattern[i-1]);
    }
}

void display_pattern(int pattern[])
{
    for(int i = 0; i < 4; i++)
    {
        cout<<pattern[i]<<"  ";
    }
    cout<<endl;
}

void initialize_board(int board[][9], char status[][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            board[j][i] = 0;
            status[j][i] = '-';
        }
    }
}

void colour_change(int foo)
{
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );

    switch(foo)
    {
    case 1:
    {
        SetConsoleTextAttribute( hOut, FOREGROUND_RED | FOREGROUND_INTENSITY );
    }
    break;
    case 2:
    {
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
    }
    break;
    case 3:
    {
        SetConsoleTextAttribute( hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY );
    }
    break;
    case 4:
    {
        SetConsoleTextAttribute( hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
    }
    break;
    case 5:
    {
        SetConsoleTextAttribute( hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
    }
    break;
    case 6:
    {
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
    }
    break;
    case 7:
    {
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    }
    break;
    case 8:
    {
        SetConsoleTextAttribute( hOut, FOREGROUND_RED | FOREGROUND_GREEN );
    }
    break;
    default:
    {
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
    break;
    }
}

void display_board(int board[][9], char status[][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(board[j][i] != 0)
            {
                colour_change(board[j][i]);
                cout<<" ["<<board[j][i]<<"] ";
                colour_change(0);
            }
            else
            {
                cout<<" [_] ";
            }
        }
        for(int j = 0; j < 4; j++)
        {
            cout<<" "<<status[j][i];
        }
        cout<<endl;
    }
    cout<<"PS. * oznacza ze ktoras z twoich liczb pasuje do kodu"<<endl;
    cout<<    "O oznacza ze trafiles jedna z liczb dokladnie w punkt."<<endl;
}

void refresh_board(int board[][9], int round, int shot[])
{
    for(int i = 0; i < 4; i++)
    {
        board[i][round] = (int)shot[i];
    }
}

void status_update(char status[][9], int black, int white, int round)
{
    for(int i = 0; i < 4; i++)
    {
        if(white>0)
        {
            status[i][round] = 'O';
            white--;
        }
        else if(black>0)
        {
            status[i][round] = '*';
            black--;
        }
    }
}

bool turn(int board[][9], char status[][9], int shot[], int pattern[], int round)
{
    int black=0, white=0;
    int pattern_copy[4];
    pattern_copy[0] = pattern[0];
    pattern_copy[1] = pattern[1];
    pattern_copy[2] = pattern[2];
    pattern_copy[3] = pattern[3];
    int shot_copy[4];
    char shot_char;

    for(int i = 0; i < 4; i++)
    {
        cin>>shot[i];
        shot_copy[i] = shot[i];

        if(shot_copy[i] == pattern_copy[i])
        {
            white++;
            pattern_copy[i] = 0;
            shot_copy[i] = -1;
        }
    }
    for(int i = 0; i < 4; i++)
    {

        for(int j = 0; j < 4; j++)
        {
            if(shot_copy[j] == pattern_copy[i])
            {
                pattern_copy[i] = 0;
                shot_copy[j] = -1;
                black++;
            }
        }

    }
    ///Do debugowania
    ///cout<<"trafione: "<<black<<endl<<"W punkt: "<<white<<endl;

    status_update(status, black, white, round);
    refresh_board(board, round, shot);

    if(white == 4)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void game()
{
    int board[4][9];
    int pattern[4];
    char status[4][9];
    int shot[4];
    int round = 0;
    bool win = false;
    string imie;

    generate_pattern(pattern);
    display_pattern(pattern);
    cout<<"Witaj w grze mastermind napisanej przez Macka"<<endl;
    cout<<"Zasady gry zapewne znasz, jesli nie to zajrzyj na wiki ;)"<<endl;
    cout<<"Wpisz swoje imie i wcisnij enter, aby zaczac rozgrywke"<<endl;
    cin>>imie;
    system( "cls" );

    clock_t start = clock();

    initialize_board(board, status);
    display_board(board, status);
    while(round<9)
    {
        if(turn(board, status, shot, pattern, round) == true)
        {
            win = true;
            //display_board(board, status);
            break;
        }
        system( "cls" );
        display_board(board, status);
        round++;
    }
    clock_t stop = clock();
    float czas = float((stop - start))/1000;
    ofstream output;
    output.open("scoreboard.txt", ios::app);

    system( "cls" );
    display_board(board, status);
    if(win)
    {
        cout<<"Gratulacje, wygrales! Twoj wynik to: "<<czas<<"s"<<endl;
        output<<imie<<"\t"<<czas<<endl;

    }
    else
    {
        cout<<"Przegrales. Zajelo Ci to "<<czas<<"s. Ja potrafie znacznie szybciej."<<endl;
        cout<<"Poprawny kod to: "<<shot[0]<<shot[1]<<shot[2]<<shot[3]<<endl;
        output<<imie<<"\tlooser"<<endl;
    }
    cout<<endl<<"Wcisnij enter aby wrocic do menu."<<endl;
    getch();
}

void scoreboard()
{
    ifstream input;
    input.open("scoreboard.txt");
    string imie, czas;
    while(input>>imie>>czas)
    {
        cout<<imie<<"\t"<<czas<<endl;
    }
    cout<<endl<<"Wcisnij enter aby wrocic do menu."<<endl;
    getch();
}

int main()
{
    while(true)
    {
        system("cls");
        cout<<"MASTERMIND \t by Maciej Lojek"<<endl;
        cout<<"1.Graj"<<endl;
        cout<<"2.Wyswietl tabele wynikow"<<endl;
        cout<<"3.Zamknij program"<<endl;
        int a;
        do
        {
            cin>>a;
        }
        while(a!=1 and a!=2 and a!=3);

        switch(a)
        {
        case 1:
            game();
            break;
        case 2:
            scoreboard();
            break;
        case 3:
            return 0;
            break;
        default:
            break;
        }
    }

    return 0;
}
