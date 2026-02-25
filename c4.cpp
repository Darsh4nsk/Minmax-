#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Connect{
    private: 
        vector<vector<string>> board;
        string turn;
    public: 
        Connect(){ 
            turn = "1";
            board = vector<vector<string>>(6, vector<string>(7, "."));
        }
        void Move(int i){
            for(int j = 5; j>=0; j--){
                if(board[j][i] == "."){
                    board[j][i] = turn;
                    turn = (turn == "1")?"0":"1";
                    break;
                }
            }
        }
        void PrintBoard(){
            for(int i =0 ; i <6; i++){
                for(int j = 0; j<7; j++){
                    cout<<board[i][j];
                }
                cout<<endl;
            }
        }
        string GameEnd(){ 
            string temp;
            for(int i= 0; i< 6 ;i++){
                for(int j =0;j<7;j++){
                    if(board[i][j] != "."){
                        temp = board[i][j];
                        
                    }
                }
            }
        }
};

int main(){
    int input; 
    Connect connect; 
    while(true){
        cin>>input;
        if(input>6)break;
        connect.Move(input-1); 
        connect.PrintBoard();
    }
    return 0; 
}