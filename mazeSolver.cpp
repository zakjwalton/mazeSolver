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

enum Dir {RIGHT = 0,LEFT = 1,UP = 2,DOWN = 3};

class Coord{
	int xpos, ypos;
	Dir dir;
public:
	Coord(int x, int y, Dir d){xpos = x; ypos = y; dir = d;}
	int getX(){return xpos;}
	int getY(){return ypos;}
	Dir getDir(){return dir;}
	void setX(int x){xpos = x;}
	void setY(int y){ypos = y;}
	void setDir(Dir d){dir = d;}
	void setCoord(int x, int y){ xpos = x; ypos = y;}
};

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
	in.open("sample_mazes/SPFmaze2.txt");
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
	//int bfDistance = bruteForceMazeSolver(x,y);
	int btDistance = backtrackingMazeSolver(x,y);
	int gDistance = greedyMazeSolver(x,y);
	int dncDistance = divideAndConquerMazeSolver(x,y);
	int dpDistance = dynamicProgrammingMazeSolver(x,y);
	int rDistance = randomizedMazeSolver(x,y);

	//cout << "Brute force distance: " << bfDistance << " units away!" << endl;
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
		Dir oldDir = DOWN;
		srand(time(NULL));

		//Loop until we find the finish
		while(myMaze.matrix[y][x] != 'F'){
			//Remove top element from stack if backtracking
			if(!first){
				if((coordStack.top().getX() == x) && (coordStack.top().getY() == y)){
					coordStack.pop();
				}
			}
			//If it is first iteration or we somehow get back to starting point
			if(coordStack.empty()){
				first = true;
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

			//First time through case.. at starting point
			if(first){
				first = false;
				//Randomly find valid direction
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
						if(myMaze.matrix[y-1][x] != '*')
							break;
					}
					if(dir == DOWN){
						if(myMaze.matrix[y+1][x] != '*')
							break;
					}
				}
				//Move selected direction
				switch(dir){
					case(RIGHT):
						coordStack.push(Coord(x,y,RIGHT));
						x++;
						oldDir = RIGHT;
						break;
					case(LEFT):
						coordStack.push(Coord(x,y,LEFT));
						x--;
						oldDir = LEFT;
						break;
					case(UP):
						coordStack.push(Coord(x,y,RIGHT));
						y--;
						oldDir = UP;
						break;
					case(DOWN):
						coordStack.push(Coord(x,y,RIGHT));
						y++;
						oldDir = DOWN;
						break;
				}
			//Case where there are three openings, need to chose
			} else if(openings == 3){
				//find valid direciton
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
						if(myMaze.matrix[y-1][x] != '*')
							break;
					}
					if(dir == DOWN){
						if(myMaze.matrix[y+1][x] != '*')
							break;
					}
				}
				//move valid direction
				switch(dir){
					case(RIGHT):
						if(coordStack.top().getX() != x+1 || coordStack.top().getY() != y)
							coordStack.push(Coord(x,y,oldDir));
						x++;
						oldDir = RIGHT;
						break;
					case(LEFT):
						if(coordStack.top().getX() != x-1 || coordStack.top().getY() != y){
							coordStack.push(Coord(x,y,oldDir));
						}
						x--;
						oldDir = LEFT;
						break;
					case(UP):
						if(coordStack.top().getX() != x || coordStack.top().getY() != y-1){
							coordStack.push(Coord(x,y,oldDir));
						}
						y--;
						oldDir = UP;
						break;
					case(DOWN):
						if(coordStack.top().getX() != x || coordStack.top().getY() != y+1){
							coordStack.push(Coord(x,y,oldDir));
						}
						y++;
						oldDir = DOWN;
						break;
				}
			//either two or 4 openings, go straight if possible.  Otherwise Randomly
			//chose next direction
			}else if(dir == RIGHT){
				if(myMaze.matrix[y][x+1] != '*'){
					//Push last location
					if(coordStack.top().getX() != x+1 || coordStack.top().getY() != y){
						coordStack.push(Coord(x,y,oldDir));
					}
					x++;
					oldDir = RIGHT;
					first = false;
				}else{
					//Chose next direction
					dir = static_cast<Dir>(rand() % 4);
				}
			}else if(dir == LEFT){
				if(myMaze.matrix[y][x-1] != '*'){
					//Push last location
					if(coordStack.top().getX() != x-1 || coordStack.top().getY() != y){
						coordStack.push(Coord(x,y,oldDir));
					}
					x--;
					oldDir = LEFT;
					first = false;
				}else{
					//chose next direction
					dir = static_cast<Dir>(rand() % 4);
				}
			}else if(dir == UP){
				if(myMaze.matrix[y-1][x] != '*'){
					//Push last location
					if(coordStack.top().getX() != x || coordStack.top().getY() != y-1){
						coordStack.push(Coord(x,y,oldDir));
					}
					y--;
					oldDir = UP;
					first = false;
				}else{
					//chose next direction
					dir = static_cast<Dir>(rand() % 4);
				}
			}else{
				if(myMaze.matrix[y+1][x] != '*'){
					//Push last location
					if(coordStack.top().getX() != x || coordStack.top().getY() != y+1){
						coordStack.push(Coord(x,y,oldDir));
					}
					y++;
					oldDir = DOWN;
					first = false;
				}else{
					//chose next direction
					dir = static_cast<Dir>(rand() % 4);
				}
			}

		}

		//reverse stack so we print latest route last
		stack<Coord> coordStack1;
		while(!coordStack.empty()){
			coordStack1.push(coordStack.top());
			coordStack.pop();
		}

		//Fill up matrix with route, and count number of moves
		int count = -1;
		while (!coordStack1.empty()){
			count++;
			if(myMaze.matrix[coordStack1.top().getY()][coordStack1.top().getX()] != 'S'){
				if(coordStack1.top().getDir() == RIGHT){
					myMaze.matrix[coordStack1.top().getY()][coordStack1.top().getX()] = '>';
				} else if(coordStack1.top().getDir() == LEFT){
					myMaze.matrix[coordStack1.top().getY()][coordStack1.top().getX()] = '<';
				}else if(coordStack1.top().getDir() == UP){
					myMaze.matrix[coordStack1.top().getY()][coordStack1.top().getX()] = '^';
				}else{
					myMaze.matrix[coordStack1.top().getY()][coordStack1.top().getX()] = 'v';
				}
			}
			coordStack1.pop();
		}
    return count;
}
