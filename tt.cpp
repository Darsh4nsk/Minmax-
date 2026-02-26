#include <iostream>
#include <vector>
#include <map>
using namespace std;
#include <unordered_map>
#include <climits>

void printboard(vector<vector<string>> b){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << b[i][j];
        }
        cout << endl;
    }
}
//winnning mech checking1
bool teamwin(vector<vector<string>> b,string c){
    bool done = 1;
    for(int i =0 ; i<3; i++){
        done = 1;
        for(int j =0; j<3 ; j++){
            if(b[i][j] != c){
                done = 0;
            }
        }
        if(done){
            return true;
        }
    }
    for(int i =0 ; i<3; i++){
        done = 1;
        for(int j =0; j<3 ; j++){
            if(b[j][i] != c){
                done = 0;
            }
        }
        if(done){
            return true;
        }
    }

    if(b[1][1]==c){
        if(b[0][0]==c && b[2][2]==c)return true;
        if(b[0][2]==c && b[2][0]==c)return true;
    }
    return false;
    
}
bool draw(vector<vector<string>> b){
    for(int i =0;i<3;i++){
        for(int j = 0; j<3; j++){
            if(b[i][j] == ".")return false;
        }
    }
    return true;
}
string gameend(vector<vector<string>> b){
    if(teamwin(b, "x")){
        
        //cout<<"THE WINNER IS X";
        return "x";
    }
    else if(teamwin(b, "o")){
        //cout<<"THE WINNER IS O";
        return "o";
    }
    else if(draw(b)){
        //cout<<"DRAW";
        return "d";
    }
    
    return ".";
}

//minmax algo 
int minmaxalgo(vector<vector<string>> board, string c,string ai){
    if(gameend(board)!="."){
        if(gameend(board) == ai){
            return 1;
        }
        else if(gameend(board) == "d"){
            return 0;
        }
        else{
            return -1;
        }
    }
    int temp;
    if(c == ai){
        int best = INT_MIN;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(board[i][j] == "."){
                    board[i][j] = c; 
                    temp = minmaxalgo(board, (c=="x")?"o":"x",ai);
                    if(temp > best)best = temp;
                    board[i][j] = ".";
                }
            }
        }
        return best;
    }
    else{ 
        int best = INT_MAX;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(board[i][j] == "."){
                    board[i][j] = c; 
                    temp = minmaxalgo(board, (c=="x")?"o":"x",ai);
                    if(temp < best)best = temp;
                    board[i][j] = ".";
                }
            }
        }
        return best;
    }
}
int bestmove(vector<vector<string>> board,string c){
    int mi = 0;
    int mj = 0; 
    int maxval = INT_MIN;
    int val = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0;j<3;j++){
            if(board[i][j]=="."){
                board[i][j] = c;
                val = minmaxalgo(board, (c=="x")?"o":"x",c);
                board[i][j] = ".";
                if(val > maxval){
                    maxval = val; 
                    mi = i; mj = j;
                }
            }
        }
    }
    return (mi*3 + mj);
}



int main()
{
    vector<vector<string>> board(3, vector<string>(3, "."));
    //vector<vector<string>> checkboard = {{"x","","o"},{"x","x","o"},{"o"," ","x"}};
    //cout<< gameend(checkboard)<<endl;

    int input;
    bool turns=1;
    while(gameend(board) == "."){
        if(turns){
            cin>>input;
        }
        else{
            input = bestmove(board, "x");
        }
        if(!turns){
            board[input / 3][input % 3] = "x";
            turns=1;
        }
        else{
            board[input / 3][input % 3] = "o";
            turns = 0;
        }
        printboard(board);
        cout<<endl;
    }

    return 0;
}
