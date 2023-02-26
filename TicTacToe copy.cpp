// Adnaan Chida
// Tic Tac Toe Game
// To play a Tic Tac Toe game with 1 or 2 players
// C++ (.cpp)
// HackIllinois 2023

#include<iostream>
#include<list>
#include <cstdlib>
#include<string>
#include <ctime>
using namespace std;
 
//struct for declaration
typedef struct{
    int *row;
}
WinList;
 
// player class
class Player {
// private and public variables
private:
    string name;    //variable to store the name
    int score;  //variable to store the score
public:
    Player() :Player {""}{}  //constructor
    Player(string n) :score{0}, name{n}{}   //parameterized constructor
 
    // void function to call what happens if player wins
    void won(){
        score++;    //inrease the score by 1
    }
    int getScore(){ return this->score;}    //returns the score 
    string getName(){ return this->name;}   //returns name
};
 
 // game class
class Game {
private:
    char board[9];//array to display board
    int emptyIndex[9];//array to store indices of board
    int game; // calling game function
    int againstComputer; // against computer function
    int emptyCount;
    WinList winlist[8];//winning lists
 
    // function to display the board when the program is run
    // board design (3 x 3) 
    void displayBoard(){
        cout <<endl;
        cout << "   |   |   "<<endl;
        cout << " "<< board[0] <<" | "<<board[1]<<" | "<<board[2]<<endl;
        cout << "   |   |   "<<endl;
        cout << "-----------"<<endl;
        cout << "   |   |   "<<endl;
        cout << " "<< board[3] <<" | "<<board[4]<<" | "<<board[5]<<endl;
        cout << "   |   |   "<<endl;
        cout << "-----------"<<endl;
        cout << "   |   |   "<<endl;
        cout << " "<< board[6] <<" | "<<board[7]<<" | "<<board[8]<<endl;
        cout << "   |   |   "<<endl;
        cout <<endl;
    }
 
    //function for computer input if its a 1 player game 
    void computerInput(){
        int pos;
        pos = rand()%10;
        if(emptyIndex[pos] == 1){
            if(emptyCount < 0)
                return;
            computerInput();
        } else {
            cout<< "Computer choose: " << pos+1 << endl;
            emptyIndex[pos] =1;
            emptyCount-=1;
            board[pos] = 'O';
        }
    }
    
    // function for player input if its a two player game
    void playerInput(Player &player)
    {
        int pos;
        cout << endl;
        cout << "\t" << player.getName() <<" Turn: ";
        cout <<"\t Enter the position " << endl;
        cin >> pos;
        pos -=1;
        if(emptyIndex[pos] == 1){
            cout << "-----Position not empty-------"<< endl;
            playerInput(player);
        } else {
            emptyIndex[pos] =1;
            emptyCount-=1;
            player.getName().compare("Player 1") == 0 ? board[pos] ='X': board[pos] ='O';
        }
 
    }
 
    void checkWin(Player &p1,Player &p2){//function to check if a player has won
        int i,j,k;
        bool flag = false;
        char first_symbol;
        for(i=0; i<8; i++){
            first_symbol = board[winlist[i].row[0]];
 
            if((first_symbol != 'X') && (first_symbol != 'O')){
                flag = false;
                continue;
            }
            flag = true;
            for(j=0;j<3;j++){
                if(first_symbol != board[winlist[i].row[j]]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                game = 0;
                if(first_symbol == 'X'){
                    cout << "-----------------------"<< endl;
                    cout << "\t Player 1 Wins"<< endl;
                    cout << "-----------------------"<< endl;
                    p1.won();
                } else {
                    p2.won();
                    if(againstComputer){
                        cout << "-----------------------"<< endl;
                        cout << "\t Computer Wins"<< endl;
                        cout << "-----------------------"<< endl;
                    } else {
                        cout << "-----------------------"<< endl;
                        cout << "\t Player 2 Wins"<< endl;
                        cout << "-----------------------"<< endl;
 
                    }
                }
                displayScore(p1,p2);
                break;
            }
        }
    }
 
        void play(Player &p1,Player &p2){//function to start the game play
            char rematch ='\0';
            int hand = 0;
            game = 1;
            displayBoard();
            while((emptyCount > 0) && (game != 0)){
 
                if(againstComputer)
                    hand == 1 ? computerInput(): playerInput(p2);
                else
                    hand == 1 ? playerInput(p1): playerInput(p2);
                hand= !hand;
                displayBoard();
                checkWin(p1,p2);
            }
            if (emptyCount <=0){
                cout << "      -----------------------"<< endl;
                cout << "\t No Winner"<< endl;
                cout << "      -----------------------"<< endl;
            }
            cout<< endl;
            cout << "Rematch Yes/No: ";
            cin >> rematch;
            if((rematch == 'Y')||(rematch == 'yes')||(rematch == 'y'))
            {
                init();
                play(p1,p2);
            }
 
        }
    void displayScore(Player &p1, Player &p2){//function to display the scores of players
        cout << endl;
        cout << "\t Score: \t";
        if(againstComputer)
            cout<<" Player 1: " <<p1.getScore()<<" \t Computer: "<<p2.getScore()<< endl;
        else
            cout<<" Player 1: " <<p1.getScore()<<" \t Player 2: "<<p2.getScore()<< endl;
    }
 
public:
    Game(): emptyCount{0}, game{1}, againstComputer{0}{//game initailizer list
        init();
        //winlists for winning validation
        winlist[0].row = new int[3]{0,1,2};
        winlist[1].row = new int[3]{3,4,5};
        winlist[2].row = new int[3]{6,7,8};
        winlist[3].row = new int[3]{0,3,6};
        winlist[4].row = new int[3]{1,4,7};
        winlist[5].row = new int[3]{2,5,8};
        winlist[6].row = new int[3]{0,4,8};
        winlist[7].row = new int[3]{2,4,6};
    }
 
    void init(){//game initialization
        game = 1;
 
        emptyCount =0;
        srand(time(0));
        for(size_t i=0; i<10; i++){
            emptyIndex[i] = 0;
            board[i] = (i+1) +'0';
            emptyCount++;
        }
        emptyCount--;
    }
 
    void onePlayerGame(){//function for 1 player game
        //Creating Player
        Player p("Player I");
        Player c("Computer");
        cout << endl;
        cout << "Player I: X \t Computer: O"<< endl;
        cout << endl;
        againstComputer = 1;
        play(c,p);
 
    }
 
    void twoPlayerGame(){//function for 2 player game
        //Creating Player
        Player p("Player I");
        Player c("Player II");
        cout << endl;
        cout << "Player I: X \t Player II: O"<< endl;
        cout << endl;
        againstComputer = 0;
        play(c,p);
    }
};
 
int main()
{
    int ch;//variable for choice of user
 
    while(1){//displays menu and keeps the program running acccording to users choioce
        cout<< "------------TIC TAC TOE----------" << endl;
        cout << "1) 1 Player game"<<endl;
        cout << "2) 2 Player game"<<endl;
        cout << "3) Exit " <<endl<<endl;
        cout <<"Select an option" << endl;
        cin >> ch;
       
        switch(ch){//switch case for conditional implementation
               case 1:
               {
                              Game *g=new Game;
               g->init();
               g->onePlayerGame();
                                             }                   
            break;
               case 2:
            {
               Game *g=new Game;
               g->init();
               g->twoPlayerGame();
                                             }          
            break;
               case 3:
               return 0;
        default:
            cout<<"Invalid Option, Please try again!"<<endl;
        }
 
    }
    return 0;
}