#include<bits/stdc++.h> 
using namespace std; 

#define AI 1 
#define human 2 

#define side 3 

#define computermove 'O' 
#define humanmove 'X' 

void showboard(char board[][side]) 
{ 
	
	cout<<"\t\t\t"<<board[0][0]<<"  |  "<< board[0][1]<<"  |  "<<board[0][2]<<"\n"; 
	cout<<"\t\t\t---------------\n";
    cout<<"\t\t\t"<<board[1][0]<<"  |  "<< board[1][1]<<"  |  "<<board[1][2]<<"\n"; 
	cout<<"\t\t\t---------------\n";
    cout<<"\t\t\t"<<board[2][0]<<"  |  "<< board[2][1]<<"  |  "<<board[2][2]<<"\n"; 
	  
} 


bool rowcrossed(char board[][side]){
    for(int i=0;i<side;i++){
        if(board[i][0]==board[i][1]&&board[i][1] == board[i][2] && 
			board[i][0] != '*'){
                return true;
			}
    }
	return false;
}
bool columncrossed(char board[][side]) 
{ 
	for (int i=0; i<side; i++) 
	{ 
		if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] != '*') 
			return (true); 
	} 
	return(false); 
} 
bool diagonalcrossed(char board[][side]) 
{ 
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] != '*') 
		return(true); 
		
	if (board[0][2] == board[1][1] &&
     board[1][1] == board[2][0] && 
		board[0][2] != '*') 
		return(true); 

	return(false); 
} 



void instruct(){
    cout << "\nchoose no. between 1 to 9 to play\n";
    cout<<"\t\t\t 1|2|3\n";
    cout<<"\t\t\t-------\n";
    cout<<"\t\t\t 4|5|6\n";
    cout<<"\t\t\t-------\n";
    cout<<"\t\t\t 7|8|9\n\n";
}
void declarewinner(int whoseturn) 
{ 
	if (whoseturn == AI) 
		cout<<"AI has won\n"; 
	else
		cout<<"HUMAN has won\n"; 
} 

void start(char board[][side]){
    for(int i=0;i<side;i++){
        for(int j=0;j<side;j++){
            board[i][j]='*';
        }

    }
}
bool gameover(char board[][side]){
    return(rowcrossed(board) || columncrossed(board) || diagonalcrossed(board) );
}
int minimax(char board[][side], int depth, bool isAI){
    int score = 0;
	int bestscore = 0;
	if (gameover(board) == true)
	{
		if (isAI == true)
			return -10;
		if (isAI == false)
			return +10;
	}
	else
	{
		if(depth < 9)
		{
			if(isAI == true)
			{
				bestscore = -999;
				for(int i=0; i<side; i++)
				{
					for(int j=0; j<side; j++)
					{
						if (board[i][j] == '*')
						{
							board[i][j] = computermove;
							score = minimax(board, depth + 1, false);
							board[i][j] = '*';
							if(score > bestscore)
							{
								bestscore = score;
							}
						}
					}
				}
				return bestscore;
			}
			else
			{
				bestscore = 999;
				for (int i = 0; i < side; i++)
				{
					for (int j = 0; j < side; j++)
					{
						if (board[i][j] == '*')
						{
							board[i][j] = humanmove;
							score = minimax(board, depth + 1, true);
							board[i][j] = '*';
							if (score < bestscore)
							{
								bestscore = score;
							}
						}
					}
				}
				return bestscore;
			}
		}
		else
		{
			return 0;
		}
	}
}




int bestmove(char board[][side], int moveindex)
{
 int x=-1,y=-1;
 int score=0,bestscore=-999;
 for(int i=0;i<side;i++){
    for(int j = 0; j < side; j++){
     if (board[i][j] == '*'){
         
				board[i][j] = computermove;
				score = minimax(board, moveindex+1, false);
				board[i][j] = '*';
				if(score > bestscore)
				{
					bestscore = score;
					x = i;
					y = j;
				}

     }
     
    } 

 }
 return x*3+y;
}
void playtictactoe(int whoseturn){
   char board[side][side];
   int moveindex=0,x=0,y=0;
   start(board);
   instruct();

   while(gameover(board)==false && moveindex!=side*side){
    int n;
    if(whoseturn==AI){
        n = bestmove(board, moveindex);
			x = n / side;
			y = n % side;
			board[x][y] = computermove; 
			cout<<"COMPUTER has put a" << computermove <<"in cell  " << n+1 <<"\n\n";
			showboard(board);
			moveindex ++; 
			whoseturn = human;

    }
    else if (whoseturn == human) 
		{
			cout<<"You can insert in the following positions : ";
			for(int i=0; i<side; i++)
				for (int j = 0; j < side; j++)
					if (board[i][j] == '*')
						cout<<(i * 3 + j) + 1<<" ";
			cout<<"\n\nEnter the position = ";
			cin>>n;
			n--;
			x = n / side;
			y = n % side; 
			if(board[x][y] == '*' && n<9 && n>=0)
			{
				board[x][y] = humanmove; 
				cout<<"\nHUMAN has put a "<<humanmove<<"in cell"<<n+1<<"\n\n"; 
				showboard(board); 
				moveindex ++; 
				whoseturn = AI;
			}
			else if(board[x][y] != '*' && n<9 && n>=0)
			{
				cout<<"\nPosition is occupied, select any one place from the available places\n\n";
			}
			else if(n<0 || n>8)
			{
				cout<<"Invalid position\n";
			}
		} 
	} 

	if (gameover(board) == false && moveindex == side * side) {
		cout<<"It's a draw\n"; }
	else
	{ 
		if (whoseturn == AI) 
			whoseturn = human; 
		else if (whoseturn == human) 
			whoseturn = AI; 
		
		declarewinner(whoseturn); 
	} 
} 


   

int main(){
   cout<<endl<<"         *********"<<endl; 
   cout<<endl<<"         ccccccccccccccccccccccc"<<endl; 
   cout<<endl<<"             TIC-TAC-TOE"<<endl;
   char cont='y';
   do{
       char choice;
       cout<<"           wanna start first?(y/n):";
       cin>>choice;
       if(choice=='n'){
          playtictactoe(AI);
       }
       else{
       if(choice=='y'){
          playtictactoe(human);
       }
       else{
           cout<<"invaid choice";
       }}
       cout<<"wanna quit";
       cin>>cont;
   } while(cont=='n');
   return 0;
}