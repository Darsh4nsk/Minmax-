#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

int N = 6;
class Connect{
    private: 
        vector<vector<string>> board;
    public: 
        Connect(){ 
            board = vector<vector<string>>(N, vector<string>(N+1, "."));
        }
        bool CanMove(int i){
            return board[0][i] == ".";
        }
        void Move(int i,string fill){
            if(!CanMove(i))return;
            for(int j = N-1; j>=0; j--){
                if(board[j][i] == "."){
                    board[j][i] = fill;
                    break;
                }
            }
        }
        void Remove(int i){
            int j = N-1;
            for(j = N-1;j>=0;j--){
                if(board[j][i] == "."){
                    break;
                }
            }
            if(j!=N-1)board[j+1][i] = ".";
        }
        int Evaluate(string ai) {
            int score = 0;
            string opponent = (ai == "1") ? "0" : "1";

            // Center column preference
            for(int r = 0; r < N; r++){
                if(board[r][(N+1)/2] == ai)
                    score += 3;
            }

            // Count 3 in a rows
            for(int r = 0; r < N; r++){
                for(int c = 0; c < N+1; c++){

                    if(c+3 < N+1){
                        int aiCount = 0, oppCount = 0, empty = 0;

                        for(int k = 0; k < 4; k++){
                            if(board[r][c+k] == ai) aiCount++;
                            else if(board[r][c+k] == opponent) oppCount++;
                            else empty++;
                        }

                        if(aiCount == 3 && empty == 1) score += 50;
                        if(aiCount == 2 && empty == 2) score += 10;

                        if(oppCount == 3 && empty == 1) score -= 80; // block opponent
                    }
                }
            }

            return score;
        }
        void PrintBoard(){
            for(int i =0 ; i <N; i++){
                for(int j = 0; j<N+1; j++){
                    cout<<board[i][j];
                }
                cout<<endl;
            }
        }
        string GameEnd() {
            bool draw = true;

            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N+1; c++) {

                    if (board[r][c] == ".") {
                        draw = false;
                        continue;
                    }

                    string player = board[r][c];

                    if (c + 3 < N+1 &&
                        board[r][c+1] == player &&
                        board[r][c+2] == player &&
                        board[r][c+3] == player)
                        return player;

                    if (r + 3 < N &&
                        board[r+1][c] == player &&
                        board[r+2][c] == player &&
                        board[r+3][c] == player)
                        return player;

                    if (r + 3 < N && c + 3 < N+1 &&
                        board[r+1][c+1] == player &&
                        board[r+2][c+2] == player &&
                        board[r+3][c+3] == player)
                        return player;

                    if (r + 3 < N && c - 3 >= 0 &&
                        board[r+1][c-1] == player &&
                        board[r+2][c-2] == player &&
                        board[r+3][c-3] == player)
                        return player;
                }
            }

            if (draw) return "d";  
            return ".";            
        }

        int BestMove(string current,string ai){
            int bestval = INT_MIN,bestmove = 0;
            for(int i = 0; i< N+1;i++){
                if(CanMove(i)){
                    
                    Move(i,current); 
                    int val = MinMax((current == "1")?"0":"1", ai,6,INT_MIN,INT_MAX); 
                    Remove(i);
                    if(val>bestval){
                        bestval = val;
                        bestmove = i; 
                    }
                }
            }
            return bestmove; 
        }
        int MinMax(string current,string ai,int depth,int alpha, int beta){ 
            string gameresult = GameEnd(); 
            if(gameresult == ai)return 1000+depth;
            else if(gameresult == "d") return 0; 
            else if(gameresult != ".") return -1000-depth;

            if(depth == 0)return Evaluate(ai);

            if(current == ai){
                int best = INT_MIN; 
                for(int i =0;i<N+1;i++){
                    if(CanMove(i)){
                        Move(i,current); 
                        int score = MinMax((current == "1")?"0":"1", ai,depth - 1,alpha,beta); 
                        Remove(i); 
                        if(score > best){ 
                            best = score; 
                        }
                        alpha = max(best, alpha); 
                        if(alpha>=beta)break;
                    }
                }
                
                return best;
            } 
            else{
                int best = INT_MAX; 
                for(int i =0; i <N+1; i++){
                    if(CanMove(i)){
                        Move(i,current); 
                        int score = MinMax((current == "1")?"0":"1",ai,depth -1,alpha,beta); 
                        Remove(i); 
                        if(score <best)best = score;
                        beta = min(best,beta); 
                        if(alpha>=beta)break;
                    }
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
            input = connect.BestMove("0","0");
            turns = true;
        }
        if(input > N) break;
        connect.Move(input,!turns?"1":"0"); 
        connect.PrintBoard();
        cout<<endl;
        output = connect.GameEnd();
        if(output != ".")break; 
    }
    return 0; 
}