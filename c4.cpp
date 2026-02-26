#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Connect{
    private: 
        vector<vector<string>> board;
    public: 
        Connect(){ 
            board = vector<vector<string>>(6, vector<string>(7, "."));
        }
        void Move(int i,string fill){
            for(int j = 5; j>=0; j--){
                if(board[j][i] == "."){
                    board[j][i] = fill;
                    break;
                }
            }
        }
        void Remove(int i){
            int j = 5;
            for(j = 5;j>=0;j--){
                if(board[j][i] == "."){
                    break;
                }
            }
            if(j!=5)board[j+1][i] = ".";
        }
        void PrintBoard(){
            for(int i =0 ; i <6; i++){
                for(int j = 0; j<7; j++){
                    cout<<board[i][j];
                }
                cout<<endl;
            }
        }
        string GameEnd() {
            bool draw = true;

            for (int r = 0; r < 6; r++) {
                for (int c = 0; c < 7; c++) {

                    if (board[r][c] == ".") {
                        draw = false;
                        continue;
                    }

                    string player = board[r][c];

                    // ---- Horizontal ----
                    if (c + 3 < 7 &&
                        board[r][c+1] == player &&
                        board[r][c+2] == player &&
                        board[r][c+3] == player)
                        return player;

                    // ---- Vertical ----
                    if (r + 3 < 6 &&
                        board[r+1][c] == player &&
                        board[r+2][c] == player &&
                        board[r+3][c] == player)
                        return player;

                    // ---- Diagonal Down-Right ----
                    if (r + 3 < 6 && c + 3 < 7 &&
                        board[r+1][c+1] == player &&
                        board[r+2][c+2] == player &&
                        board[r+3][c+3] == player)
                        return player;

                    // ---- Diagonal Down-Left ----
                    if (r + 3 < 6 && c - 3 >= 0 &&
                        board[r+1][c-1] == player &&
                        board[r+2][c-2] == player &&
                        board[r+3][c-3] == player)
                        return player;
                }
            }

            if (draw) return "d";   // draw
            return ".";              // game continues
        }

        int BestMove(string current,string ai){
            int bestval = INT_MIN,bestmove = 0;
            for(int i = 0; i< 7;i++){
                Move(i,current); 
                int val = MinMax((current == "1")?"0":"1", ai); 
                Remove(i);
                if(val>bestval){
                    bestval = val;
                    bestmove = i; 
                }
            }
            return bestmove; 
        }
        int MinMax(string current,string ai){ 
            if(GameEnd() == ai)return 1;
            else if(GameEnd() == "d") return 0; 
            else return -1; 

            if(current == ai){
                int best = INT_MIN;   
                for(int i =0;i<7;i++){
                    Move(i,current); 
                    int score = MinMax((current == "1")?"0":"1", ai); 
                    Remove(i); 
                    if(score > best){ 
                        best = score; 
                    }
                }
                return best;
            } 
            else{
                int best = INT_MAX; 
                for(int i =0; i <7; i++){
                    Move(i,current); 
                    int score = MinMax((current == "1")?"0":"1",ai); 
                    Remove(i); 
                    if(score <best)best = score;
                }
                return best;
            }
        }
};

int main(){
    int input; 
    Connect connect; 
    string output;
    bool turns= true;
    while(true){
        if(turns){
            cin>>input;
            turns = false;
        }
        else{
            input = connect.BestMove("1","1")+1;
            turns = true;
        }
        if(input>6)break;
        connect.Move(input-1,turns?"1":"0"); 
        connect.PrintBoard();
        output = connect.GameEnd();
        if(output != ".")break; 
    }
    return 0; 
}