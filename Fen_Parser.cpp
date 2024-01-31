#include<iostream>
#include<iomanip>
using namespace std;
#define V 8
char board[V][V];
int t_white=0,t_black=0;
int w_pawn=0,w_knight=0,w_bishop=0,w_rook=0;
int w_king=0,w_queen=0;
int b_pawn=0,b_knight=0,b_bishop=0,b_rook=0;
int b_king=0,b_queen=0;

void FEN_PARSER(string fen){
    int i=0,j=0;
    for(int k=0;k<fen.length();k++){
        bool dgt=false;
        int ec=0;
        if(isdigit(fen[k])) {dgt=true;ec=(fen[k]-'0');}
        if(j>7) j=0;
        if(fen[k]=='/') {i++;continue;}
        if(i>7) i=0;
        if(!dgt) {board[i][j++]=fen[k];}
        else for(int p=0;p<ec;p++)  {board[i][j++]=' ';}
        
    }
}

void statistics(){
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(isalpha(board[i][j]) && isupper(board[i][j])){
                t_white++;
                switch(board[i][j]){
                    case 'P':w_pawn++;
                    break;
                    case 'B':w_bishop++;
                    break;
                    case 'N':w_knight++;
                    break;
                    case 'R':w_rook++;
                    break;
                    case 'K':w_king++;
                    break;
                    case 'Q':w_queen++;
                    break;
                }
            }
            else if(isalpha(board[i][j]) && islower(board[i][j])){
                t_black++;
                switch(board[i][j]){
                    case 'p':b_pawn++;
                    break;
                    case 'b':b_bishop++;
                    break;
                    case 'n':b_knight++;
                    break;
                    case 'r':b_rook++;
                    break;
                    case 'k':b_king++;
                    break;
                    case 'q':b_queen++;
                    break;
                }
            }
        }
    }
    cout<<"---------------------------------"<<endl;
    cout<<"\033[1;34m";
    cout<<"[STATISTICS]:"<<endl<<endl;;
    cout<<"Total White Pieces: "<<t_white<<"\t\t"<<"Total Black Pieces: "<<t_black<<endl;
    cout<<"White Pawns: "<<w_pawn<<"\t\t\t"<<"Black Pawns: "<<b_pawn<<endl;
    cout<<"White Knights: "<<w_knight<<"\t\t"<<"Black Knights: "<<b_knight<<endl;
    cout<<"White Bishops: "<<w_bishop<<"\t\t"<<"Black Bishops: "<<b_bishop<<endl;
    cout<<"White Rooks: "<<w_rook<<"\t\t\t"<<"Black Rooks: "<<b_rook<<endl;
    cout<<"White King: "<<w_king<<"\t\t\t"<<"Black King: "<<b_king<<endl;
    cout<<"White Queen: "<<w_queen<<"\t\t\t"<<"Black Queen: "<<b_queen<<endl;
    cout<<"\033[0m";
   
}

void evaluate(){
    int w_score=0,b_score=0;
    w_score+=w_pawn*1;
    w_score+=w_knight*3;
    w_score+=w_bishop*3;
    w_score+=w_rook*5;
    w_score+=w_queen*9;
    b_score+=b_pawn*1;
    b_score+=b_knight*3;
    b_score+=b_bishop*3;
    b_score+=b_rook*5;
    b_score+=b_queen*9;
    cout<<"\033[1;31m";
    double w_s_p=w_score*1.0/39;
    double b_s_p=b_score*1.0/39;
    if(w_s_p>1) w_s_p=1;
    if(b_s_p>1) b_s_p=1;
    cout<<"White Score: "<<w_score<<"["<<w_s_p<<"]\t";
    cout<<"Black Score: "<<b_score<<"["<<-(b_s_p)<<"]"<<endl<<endl;
    cout<<"\033[0m";
    int w_s_e=w_s_p*10;
    int b_s_e=b_s_p*10;
    cout<<"\033[1;32m";
    cout<<"[Evaluation bar]: "<<endl<<endl;
    int b_rem=10-b_s_e;
    int w_rem=10-w_s_e;
    for(int i=0;i<6;i++) cout<<" ";
    cout<<"("<<setprecision(2)<<b_s_p<<")B";
    cout<<"   W("<<setprecision(2)<<(w_s_p)<<")"<<endl;
    cout<<"   ";
    for(int i=0;i<b_rem;i++) cout<<"_";
    for(int i=0;i<b_s_e;i++) cout<<"#";
    cout<<" | ";
    for(int i=0;i<w_s_e;i++) cout<<"#";
    for(int i=0;i<w_rem;i++) cout<<"_";
    cout<<endl<<"-1.0                      1.0";
    cout<<endl<<endl;
    cout<<"\033[0m";
    cout<<"\033[1;36m";
    cout<<"*[Approx guess]: ";
    cout<<"\033[0m";
    if(w_score>b_score) cout<<"\033[1;32m"<<"White is winning!"<<"\033[0m"<<endl;
    else if(w_score<b_score) cout<<"\033[1;32m"<<"Black is winning!"<<"\033[0m"<<endl;
    else cout<<"\033[1;32m"<<"Position is equal for both !"<<"\033[0m"<<endl;
    
}    

bool valid_fen(string fen){
    int slash=0,total=0;
    bool invalid=false;
    int invalid_index[fen.length()]={0};
    for(int i=0;i<fen.length();i++){
        if(fen[i]=='/') slash++;
        else if(isalpha(fen[i])){
            if(fen[i]=='P'||fen[i]=='p'||fen[i]=='K'||fen[i]=='k'||fen[i]=='Q'||fen[i]=='q'||fen[i]=='B'||fen[i]=='b'||fen[i]=='N'||fen[i]=='n'||fen[i]=='R'||fen[i]=='r') total++;
            else {
            invalid_index[i]=1;
            invalid=true;
            }
        }
        else if(isdigit(fen[i])){
            total+=(fen[i]-'0');    
            
         }
         else{
            invalid_index[i]=1;
            invalid=true;
         }
    }
    if(invalid) {
        cout<<"\033[1;31m"<<"[Invalid piece/s]: "<<"\033[0m";
        for(int i=0;i<fen.length();i++) {
            if(invalid_index[i]) {cout<<"\033[1;31m"<<fen[i]<<"\033[0m";}
            else cout<<fen[i];
         }
        cout<<"\033[0m"<<endl;
        for(int i=0;i<19;i++) cout<<" ";
        for(int i=0;i<fen.length();i++){
           if(invalid_index[i]) cout<<"\033[1;31m"<<"^"<<"\033[0m";
           else cout<<" ";
    
        }
        cout<<endl;
    }
    if(slash<7) cout<<"\033[1;31m"<<"[Row]:Insufficent no of rows [<8]?"<<"\033[0m"<<endl;
    if(slash>7) cout<<"\033[1;31m"<<"[Row]:Row limit exceeded! [>8]?"<<"\033[0m"<<endl;
    if(total<64) cout<<"\033[1;31m"<<"[Total]: Insufficent material!"<<"\033[0m"<<endl;
    if(total>64) cout<<"\033[1;31m"<<"[Total]: Material limit exceeded!"<<"\033[0m"<<endl;
    return (slash==7 && total==64 && !invalid);
}
    
int main(){
    string fen;
    cout<<"Enter FEN string:"<<endl;
    cin>>fen;
    if(valid_fen(fen)) cout<<"\033[1;32m"<<"[Check]:"<<endl<<"Valid FEN string!"<<endl;
    else {cout<<"\033[1;31m"<<"[Error]: Invalid FEN string!"<<"\033[0m"<<endl;return 0;}
    FEN_PARSER(fen);
    cout<<"\033[1;32m";
    cout<<"  +---+---+---+---+---+---+---+---+"<<endl;
    for(int i=0;i<V;i++){
        cout<<V-i<<" |";
        for(int j=0;j<V;j++){
            if(isalpha(board[i][j]) && isupper(board[i][j])) cout<<"\033[1;34m";
            else if(isalpha(board[i][j]) && islower(board[i][j])) cout<<"\033[1;31m";
            cout<<" "<<board[i][j];
            cout<<"\033[1;32m";
            cout<<" |";
            cout<<"\033[1;32m";
        }
        cout<<endl<<"  +---+---+---+---+---+---+---+---+"<<endl;
    }
    cout<<"    a   b   c   d   e   f   g   h"<<endl;
    cout<<"\033[0m";
    statistics();
    evaluate();


    

}