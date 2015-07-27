#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <stdlib.h>
#include <time.h>

using namespace std;

int bruteForceMazeSolver(int i, int j);
int backtrackingMazeSolver(int i, int j);
int greedyMazeSolver(int i, int j);
int divideAndConquerMazeSolver(int i, int j);
int dynamicProgrammingMazeSolver(int i, int j);
int randomizedMazeSolver(int i, int j);

class Coord{
	int xpos, ypos;
public:
	Coord(int x, int y){xpos = x; ypos = y;}
	int getX(){return xpos;}
	int getY(){return ypos;}
	void setX(int x){xpos = x;}
	void setY(int y){ypos = y;}
	void setCoord(int x, int y){ xpos = x; ypos = y;}
};

enum Dir {RIGHT = 0,LEFT = 1,UP = 2,DOWN = 3};

struct maze
{
	int rows;
	int cols;
	char matrix [100][100];
};

maze myMaze;

int main()
{
	//required variables
	ifstream in;
	in.open("sample_mazes/maze.txt");
	char line;

	//read the matrix using plain c code, character by character
	in >> myMaze.rows;
	in >> line;
	in >> myMaze.cols;
	cout << "Reading a " << myMaze.rows << " by " << myMaze.cols << " matrix." << endl;
	//Burn the end of line character
	in.ignore(200,'\n');
	for(int i=0; i<myMaze.rows; i++)
	{
		for(int j=0; j<myMaze.cols; j++)
		{
			in.get( myMaze.matrix[i][j] );
		}
		//Burn the end of line character
		in.ignore(200,'\n');
	}

	//Print the empty maze
	for(int i=0; i<myMaze.rows; i++)
	{
		for(int j=0; j<myMaze.cols; j++)
			cout << myMaze.matrix[i][j];
		cout << endl;
	}
	int x=1,y=1;

	//Find starting coordinates
	for(int i=0; i<myMaze.rows; i++)
		for(int j=0; j<myMaze.cols; j++)
			if( myMaze.matrix[i][j] == 'S' ){
				x=j;
				y=i;
			}

	//Call a recursive mazeSolver
	int bfDistance = bruteForceMazeSolver(x,y);
	int btDistance = backtrackingMazeSolver(x,y);
	int gDistance = greedyMazeSolver(x,y);
	int dncDistance = divideAndConquerMazeSolver(x,y);
	int dpDistance = dynamicProgrammingMazeSolver(x,y);
	int rDistance = randomizedMazeSolver(x,y);

	cout << "Brute force distance: " << bfDistance << " units away!" << endl;
	cout << "Backtracking distance: " << btDistance << " units away!" << endl;
	cout << "Greedy distance: " << gDistance << " units away!" << endl;
	cout << "Divide and conquer distance: " << dncDistance << " units away!" << endl;
	cout << "Dynamic programming distance: " << dpDistance << " units away!" << endl;
	cout << "Randomized distance: " << rDistance << " units away!" << endl;

	//Print solved maze
	for(int i=0; i<myMaze.rows; i++)
	{
		for(int j=0; j<myMaze.cols; j++)
			cout << myMaze.matrix[i][j];
		cout << endl;
	}

    return 0;
}

int bruteForceMazeSolver(int i, int j)
{
    cout << "in method" << endl;

    int curr_x = i;
    int curr_y = j;
    int count = 0;
    stack<char> moves;

    while(myMaze.matrix[curr_x][curr_y] != 'F'){



    	//try going right
    	if(myMaze.matrix[curr_x][curr_y+1] == ' ' || myMaze.matrix[curr_x][curr_y+1] == 'F' ){
    		cout << "right" << endl;
    		count ++;
    		curr_y++;
    		if(myMaze.matrix[curr_x][curr_y] == 'F'){
    			break;
    		}
    		moves.push('r');
    		myMaze.matrix[curr_x][curr_y] = 'o';
    	}

    	//try going up
    	else if(myMaze.matrix[curr_x-1][curr_y] == ' ' || myMaze.matrix[curr_x-1][curr_y] == 'F'){
    		cout << "up" << endl;
    		count++;
    		//break;
    		curr_x--;
    		if(myMaze.matrix[curr_x][curr_y] == 'F'){
    			break;
    		}
    		moves.push('u');
    		myMaze.matrix[curr_x][curr_y] = 'o';
    	}

    	//try going down
    	else if(myMaze.matrix[curr_x+1][curr_y] == ' ' || myMaze.matrix[curr_x+1][curr_y] == 'F'){
    		cout << "down" << endl;
    		count++;
    		curr_x++;
    		if(myMaze.matrix[curr_x][curr_y] == 'F'){
    			break;
    		}
    		moves.push('d');
    		myMaze.matrix[curr_x][curr_y] = 'o';

    	}

    	//try going left
    	else if (myMaze.matrix[curr_x][curr_y-1] == ' ' || myMaze.matrix[curr_x][curr_y-1] == 'F'){
    		count++;
    		cout << "left" << endl;
    		//break;
    		curr_y--;
    		if(myMaze.matrix[curr_x][curr_y] == 'F'){
    			break;
    		}
    		moves.push('l');
			myMaze.matrix[curr_x][curr_y] = 'o';
    	}


    	//try backtracking right
    	else if (moves.top() == 'l'){
    		moves.pop();
    		count++;
    		if(myMaze.matrix[curr_x][curr_y] != 'S'){
    			myMaze.matrix[curr_x][curr_y] = 'x';
    		}
    		curr_y++;
    		cout << "backtracked right" << endl;
    	}

    	//try backtracking up
    	else if (moves.top() == 'd'){
    		moves.pop();
    		count++;
    		if(myMaze.matrix[curr_x][curr_y] != 'S'){
    			myMaze.matrix[curr_x][curr_y] = 'x';
    		}
    		curr_x--;
    		cout << "backtracked up" << endl;
    	}

    	//try backtracking down
    	else if (moves.top() == 'u'){
    		moves.pop();
    		count++;
    		if(myMaze.matrix[curr_x][curr_y] != 'S'){
    			myMaze.matrix[curr_x][curr_y] = 'x';
    		}
    		curr_x++;
    		cout << "backtracked down" << endl;
    	}

    	//try backtracking left
    	else if (moves.top() == 'r'){
    		moves.pop();
    		count++;
    		if(myMaze.matrix[curr_x][curr_y] != 'S'){
    			myMaze.matrix[curr_x][curr_y] = 'x';
    		}
    		curr_y--;
    		cout << "backtracked left" << endl;
    	}

    	else{
    		cout << "Error: Maze Unsolvable" << endl;
    		break;
    	}

    	/*if(count > 118){
    		break;
    	}*/
    }

    //Clear X's
    	for(int k=0; k<myMaze.rows; k++){
    		for(int h=0; h<myMaze.cols; h++){
    			if(myMaze.matrix[k][h] == 'x'){
    				myMaze.matrix[k][h] = ' ';
    			}
    		}
    	}

    return -1;    
}
int backtrackingMazeSolver(int i, int j)
{
    //algorithm goes here
    return -1;
}
int greedyMazeSolver(int i, int j)
{
    //algorithm goes here
    return -1;
}
int divideAndConquerMazeSolver(int i, int j)
{
    //algorithm goes here
    return -1;
}
int dynamicProgrammingMazeSolver(int i, int j)
{
    //algorithm goes here
    return -1;
}
int randomizedMazeSolver(int j, int i)
{
		int x = j;
		int y = i;
		int u;
		int openings;
		stack<Coord> coordStack;
		bool first = true;
		Dir dir = DOWN;
		srand(time(NULL));
		cout << "starting shit" << endl << endl;

		while(myMaze.matrix[y][x] != 'F'){
			//cout << endl << "X = " << coordStack.top().getX() << "  Y = " << coordStack.top().getY() << endl;
			if(coordStack.empty()){
				coordStack.push(Coord(x,y));
				first = true;
			}
			if((coordStack.top().getX() == x) && (coordStack.top().getY() == y) && !first){
				coordStack.pop();
			}


			//Calculate the number of openings
			openings = 0;
			if(myMaze.matrix[y][x+1] != '*')
				openings++;
			if(myMaze.matrix[y][x-1] != '*')
				openings++;
			if(myMaze.matrix[y+1][x] != '*')
				openings++;
			if(myMaze.matrix[y-1][x] != '*')
				openings++;

			//Figure out how to move
			if(openings == 3){
				while(true){
					dir = static_cast<Dir>(rand() % 4);
					if(dir == RIGHT){
						if(myMaze.matrix[y][x+1] != '*')
							break;
					}
					if(dir == LEFT){
						if(myMaze.matrix[y][x-1] != '*')
							break;
					}
					if(dir == UP){
						if(myMaze.matrix[y+1][x] != '*')
							break;
					}
					if(dir == DOWN){
						if(myMaze.matrix[y-1][x] != '*')
							break;
					}
				}
				switch(dir){
					case(RIGHT):
						if(!coordStack.empty())
							if(coordStack.top().getX() != x+1 || coordStack.top().getY() != y){
								coordStack.push(Coord(x,y));
							}
						x++;
						break;
					case(LEFT):
						if(!coordStack.empty())
							if(coordStack.top().getX() != x-1 || coordStack.top().getY() != y){
								coordStack.push(Coord(x,y));
							}
						x--;
						break;
					case(UP):
						if(!coordStack.empty())
							if(coordStack.top().getX() != x || coordStack.top().getY() != y+1){
								coordStack.push(Coord(x,y));
							}
						y++;
						break;
					case(DOWN):
						if(!coordStack.empty())
							if(coordStack.top().getX() != x || coordStack.top().getY() != y-1){
								coordStack.push(Coord(x,y));
							}
						y--;
						break;
				}
			}else if(dir == RIGHT){
				if(myMaze.matrix[y][x+1] != '*'){
					if(!coordStack.empty())
						if(coordStack.top().getX() != x+1 || coordStack.top().getY() != y){
							coordStack.push(Coord(x,y));
						}
					x++;
					first = false;
				}else{
					dir = static_cast<Dir>(rand() % 4);
				}
			}else if(dir == LEFT){
				if(myMaze.matrix[y][x-1] != '*'){
					if(!coordStack.empty())
						if(coordStack.top().getX() != x-1 || coordStack.top().getY() != y){
							coordStack.push(Coord(x,y));
						}
					x--;
					first = false;
				}else{
					dir = static_cast<Dir>(rand() % 4);
				}
			}else if(dir == UP){
				if(myMaze.matrix[y+1][x] != '*'){
					if(!coordStack.empty())
						if(coordStack.top().getX() != x || coordStack.top().getY() != y+1){
							coordStack.push(Coord(x,y));
						}
					y++;
					first = false;
				}else{
					dir = static_cast<Dir>(rand() % 4);
				}
			}else{
				if(myMaze.matrix[y-1][x] != '*'){
					if(!coordStack.empty())
						if(coordStack.top().getX() != x || coordStack.top().getY() != y-1){
							coordStack.push(Coord(x,y));
						}
					y--;
					first = false;
				}else{
					dir = static_cast<Dir>(rand() % 4);
				}
			}

		}

		int count = -1;
		while (!coordStack.empty()){
			count++;
			if(myMaze.matrix[coordStack.top().getY()][coordStack.top().getX()] != 'S'){
				myMaze.matrix[coordStack.top().getY()][coordStack.top().getX()] = '+';
			}
			coordStack.pop();
		}
    return count;
}
