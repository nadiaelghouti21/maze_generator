//Nadia Elghouti
//id: 30466
// cs 300 HOMEWORK ONE. 

#include "Stack.h" 
#include <iostream>
#include <vector>
#include <random>
#include <ctime> // included for random _range function
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

int random_range(const int& min, const int& max) { // the following function is taken form CS 204 course. 
    static mt19937 generator(time(0));        // it generates random numbers within the chosen range (in this 
    uniform_int_distribution<int> distribution(min, max); // hw it will be 0-3.
    return distribution(generator);
}

struct maze_cell {
    int x;
    int y;
    bool l;
    bool r;
    bool u;
    bool d;
    bool visit;

    maze_cell(int x = 0, int y = 0)
        : x(x), y(y), l(true), r(true), u(true), d(true), visit(false) {};
};

class Maze {  // implement a new class
private:
    int num_col;
    int num_row;
    maze_cell** mz;  // pointer to pointer  to create the matrix.

public:
    Maze(int n, int m)   // switched number of rows and columns. 
        : num_row(m), num_col(n), mz(new maze_cell* [num_row]) {
        for (int i = 0; i < num_row; i++) {
            mz[i] = new maze_cell[num_col];
            for (int j = 0; j < num_col; j++) {
                mz[i][j] = maze_cell(i, j);
            }
        }
    }

    char random_d_generator() {   //this function will randomly pick a letter/index fro the vector and return it
        vector<char> direct = { 'u','l', 'r', 'd' };
        int index = random_range(0, 3);
        char direction = direct[index];
        return direction;
    }

    bool direction_check(maze_cell& m, char direction) {
        int x = m.x;
        int y = m.y;
        bool result = false;
        //in all inner if statments last 2 checks are the same meaning and performed for accuuracy purpose only.
        if (direction == 'l') {
            if (x == 0 || mz[x][y].l == false || mz[x - 1][y].r == false) {  // check if the cell is on the left most side.
                return false;  // or if the wall on the left side is already knocked down then we cannot knocked down the wall
            }// hence direction pick fail.
            result = mz[x - 1][y].visit == false; // else result will show if the cell on the left is visited or not yet.
            
        }
        else if (direction == 'r') {
            if (x == num_row - 1|| mz[x][y].r == false || mz[x + 1][y].l == false) {  //check if the cell is on the right most cell.
                return false; // if so we cannot knockdown the frame of maze also check if the wall on the right is already down.
            }
            result = mz[x + 1][y].visit == false; // will show if the cell on the right is visited.
        }
        else if (direction == 'd') {
            if (y == 0 || mz[x][y].d == false || mz[x][y - 1].u == false) { // check if the cell is at the bottom of maze, 
                return false;// to prevent the knockdown of maze edge also check if the lower wall is already down.
            }
            result = mz[x][y - 1].visit == false; // result shows if the cell below currrent has been visisted or not.
        }
        else if (direction == 'u') {
            if (y == num_col - 1 ||  mz[x][y].u == false || mz[x][y + 1].d == false) { //check if the cell is at top most of the maze
                return false;  // or if the upper wall of current cell is already down
            }
            result = mz[x][y + 1].visit == false; // check if upper cell is already visisted before.
        }

        // If an invalid direction is passed, return false
        return result;
    }



    maze_cell make_move(maze_cell current_c, char direction) {
        int x = current_c.x;
        int y = current_c.y;
       

        if (direction == 'u') { 
            mz[x][y].u = false; // knock down upper wall
            mz[x][y + 1].d = false;  // change the value of upper cell to have no down wall
            current_c = mz[x][y + 1];  // move one cell up
        }
        else if (direction == 'd') {
            mz[x][y].d = false;        // knock down lower wall
            mz[x][y - 1].u = false;// change the value of lower cell to have no up wall
            current_c = mz[x][y - 1];// move one cell down
        }
        else if (direction == 'r') {
            mz[x][y].r = false;// knock down right wall
            mz[x + 1][y].l = false;// change the value of left cell to have no right wall
            current_c = mz[x + 1][y];// move one cell to right
        }
        else if (direction == 'l') {
            mz[x][y].l = false;// knock down left wall
            mz[x - 1][y].r = false;// change the value of right cell to have no left wall
            current_c = mz[x - 1][y];// move one cell to the left
        }
        return current_c;   //return current posititon
    }


    void generate_m() {
        int walls_dwn = num_row * num_col - 1; //step taken from hw sheet
        Stack<maze_cell> main_maze;     //take from hw sheet
        main_maze.push(mz[0][0]);       
        maze_cell current_c = mz[0][0];
        mz[0][0].visit = true;

        
        while (walls_dwn > 0) {  // following homework instructions.
            int x = current_c.x;
            int y = current_c.y;
            bool nxt_c_unvisited = false;


            if (x > 0 && !mz[x - 1][y].visit ) {   // if not the left most cell check if the cell to left is visited
                nxt_c_unvisited = true;
            }
            else if (x < num_row - 1 && !mz[x + 1][y].visit) {  // if not the right most cell check if the cell to the right is visited
                nxt_c_unvisited = true;
            }
            else if (y > 0 && !mz[x][y - 1].visit ) {  // if not bottom cell check if cell lower is visited.
                nxt_c_unvisited = true;
            }
            else if (y < num_col - 1 && !mz[x][y + 1].visit ) { // if not upper most cell check if the upper cell is visited
                nxt_c_unvisited = true;
            }

            if (nxt_c_unvisited) {  // if we still have unvisited cells in maze
                
                main_maze.push(current_c); // puch the current cell into the stack
                char go_to = random_d_generator();  // get a random direction.
                while (!direction_check(current_c, go_to)) {  // if direction fails thhe checks keep getting a new direction

                    go_to = random_d_generator();

                }

                current_c = make_move(current_c, go_to); // move according to the random direction generated 
                current_c.visit = true;  // mark the new cell as visisted 
                mz[current_c.x][current_c.y].visit = true; // do the same for the private varaiable 
                walls_dwn--;  
            }
            
            else {
                if (!main_maze.isEmpty()) {  // if no more unvisited cells around the current cell move back one cell and try again.
                    current_c = main_maze.pop();
                }
                else {
                    break; 
                }
            }

        }

            
        
    } //end of algo one.

    // START ALGO 2

   Stack<maze_cell> findPath(int in_x, int in_y, int out_x, int out_y) {
       
        for (int i = 0; i < num_row; ++i) {  // setting all the cells to unvisted status 
            for (int j = 0; j < num_col; ++j) {
                mz[i][j].visit= false;
            }
        }
        maze_cell entry = mz[in_x][in_y]; // definig the entry point
        mz[in_x][in_y].visit = true;  // mark it as visited
        Stack<maze_cell> path; // following step 1 of hw.
        path.push(entry);  //push the entry cell into the stack

        while (!path.isEmpty()) {

            maze_cell current = path.top();  //check the top value of the stack.
            int x = current.x;
            int y = current.y;
            Stack <char> sides_goto = direction_check2(current); // stack of the possible directions for a path.
            current = make_move2(sides_goto, current);// move to the cell. 
            if (current.x == out_x && current.y == out_y) { // if this is the exit cell 
                return path; // return the stack of path.
               
            }
            
            else {
                
               
               
                if (current.x == 0 && current.y == 0) { // if no suitable direction found 
                    current = path.pop();  // go back one cell.
                }
                else { 
                    current.visit = true; //update visit status of current cell
                    mz[x][y].visit = true;
                    path.push(current); // push the cell to stack.
                }

            }


        }
        
        return path; 



    }
  

    void print_path(Stack<maze_cell> p, int id, int inx, int iny, int outx, int outy) {

        string filename = "maze_" + to_string(id) + "_path_" + to_string(inx) + "_" + to_string(iny) + "_" + to_string(outx) + "_" + to_string(outy) + ".txt";
        ofstream output_file(filename);

        Stack<maze_cell> reverse; // temperory stack to print path in organied manner
        while (!p.isEmpty()) {
            maze_cell first_c = p.top(); // take the top element of stack (exit point) to push it to new stck
            reverse.push(first_c);
            p.pop();
        }
       while(!reverse.isEmpty()) {
           maze_cell c = reverse.top(); //printing the entry point till exit in order
            output_file << c.x << " " << c.y << endl;
            reverse.pop();
        }
       output_file << outx << " " << outy << endl; // print the exit points entered by user.
       output_file.close();
        
        cout << "Path found and written to " << filename << endl;

    }
    maze_cell make_move2(Stack<char> & d, maze_cell c) {
        int x = c.x;
        int y = c.y;

            char direction = d.pop();  // pick direction
            if (direction == 'u') {
               
                    return mz[x][y + 1];  // move to upper cell
                
            }
            if (direction == 'd') { //move to lower cell
                
              
                    return mz[x][y - 1];
                
            }
            if (direction == 'r') {  // move to cell on right
                
                
                
                    return mz[x + 1][y];
                
            }
            if (direction == 'l') {  // ove to cell on left
                
                
                   return mz[x -1][y];
                
            }
       
        return mz[0][0];  // no move possible return the first cell.

    }
    Stack< char>  direction_check2(maze_cell c) {
        Stack < char> possible_goto;
        int x = c.x;
        int y = c.y;
        if (c.d == 0 && mz[x][y - 1].visit == false) { // if the path open (no wall seperating cells) and lower cell is not visted
            char d = 'd';
            possible_goto.push(d); // suitable direction found
        }
        if (c.l == 0  && mz[x-1][y].visit == false){// if the path open (no wall seperating cells) and left cell is not visited
            char l = 'l';
            possible_goto.push(l); // suitable direction found
        }
        if (c.r == 0 && mz[x +1 ][y].visit == false) {//if the path open (no wall seperating cells) and right cell is not visited
            char r = 'r';
            possible_goto.push(r);// suitable direction found
        }
        if (c.u ==0 && mz[x][y + 1].visit == false){// if the path open(no wall seperating cells) and upper cell is not visited
            char u = 'u';
            possible_goto.push(u);// suitable direction found
        
        }
        return possible_goto;  //all possible directions
        
    }

    ~Maze() { //destructor.
        for (int i = 0; i < num_row; ++i) {
            delete[] mz[i];
        }
        delete[] mz;
    }

  
    void print_m(int mz_id) const { // print each cell cooridnantes 
        ostringstream Filename;
        Filename << "maze_" << mz_id << ".txt";
        string file = Filename.str();
        ofstream outputFile(file);
        outputFile << num_col << " " << num_row << endl;
        for (int i = 0; i < num_row; ++i) {
            for (int j = 0; j < num_col; ++j) {
                maze_cell cell = mz[i][j];
                outputFile << "x=" << cell.x << " y=" << cell.y
                    << " l=" << cell.l << " r=" << cell.r
                    << " u=" << cell.u << " d=" << cell.d << endl;
            }
        }
        outputFile.close();
    }
};

int main() {
    int k, M, N;
    cout << "Enter the number of mazes: " << endl;
    cin >> k;
    cout << "Enter the number of rows and columns (M and N): " << endl;
    cin >> M >> N;
    Maze** mazes = new Maze*[k];
    for (int i = 0; i < k; i++) {
        mazes[i] = new Maze(M, N); // for each cell define a maze
        mazes[i]->generate_m();  // generate the maze
        mazes[i]->print_m(i + 1); // print into a file
       
    }
    cout << "All mazes are generated." << endl;
    int id;
    cout << "Enter a maze ID between 1 " << "to " << k << " inclusive to find a path: " << endl;
    cin >> id;
    if (1 <= id && id <= k) { // if id is within range 
        int enter_x, enter_y, exit_x, exit_y;
        cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): " << endl;
        cin >> enter_x >> enter_y;
        cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): " << endl;
        cin >> exit_x >> exit_y;

        Stack< maze_cell > path_generated = mazes[id - 1]->findPath(enter_x, enter_y, exit_x, exit_y); //generate unique path
        mazes[id - 1]->print_path(path_generated, id, enter_x, enter_y, exit_x, exit_y); // print into seperate files
    }
    else {
        cout << "Maze Id not found..." << endl;
    }
    
    

    return 0;
}
