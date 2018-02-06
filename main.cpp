#include <iostream>
#include <cstdlib>
#include <time.h>

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

void display_board(int board[][9], char status[][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(board[j][i] != 0)
                cout<<" ["<<board[j][i]<<"] ";
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

    for(int i = 0; i < 4; i++)
    {
        cin>>shot[i];
    }
    for(int i = 0; i < 4; i++)
    {
        if(shot[i] == pattern_copy[i])
        {
            white++;
            pattern_copy[i] = 0;
        }

        for(int j = 0; j < 4; j++)
        {
            if(shot[j] == pattern_copy[i] )
            {
                pattern_copy[i] = 0;
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

int main()
{
    int board[4][9];
    int pattern[4];
    char status[4][9];
    int shot[4];
    int round = 0;

    generate_pattern(pattern);
    display_pattern(pattern);
    initialize_board(board, status);
    display_board(board, status);
    while(round<8)
    {

        if(turn(board, status, shot, pattern, round) == true)
        {
            break;
        }
        display_board(board, status);
        round++;
    }

    cout<<endl<<"Gratulacje, wygrales!";

}
