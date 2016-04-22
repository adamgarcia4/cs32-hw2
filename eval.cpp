
#include <iostream>
#include <stack>

using namespace std;
class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

// Return true if there is a path from (sr,sc) to (er,ec)
// throughout the maze; return false otherwise
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

int main()
{
	//stack<Coord> coordStack; //declares a stack of Coords
	//Coord a(5, 6); // r-c
	//coordStack.push(a); //pushes (5,6) to stack
	//coordStack.push(Coord(3, 4)); //pushes (3,4) to stack
	//cerr << "Row is: " << coordStack.top().r() << "Col is: " << coordStack.top().c() << endl;
	//coordStack.pop();
	//cerr << "Row is: " << coordStack.top().r() << "Col is: " << coordStack.top().c() << endl;


	cin.ignore(1000, '\n');
}

// Return true if there is a path from (sr,sc) to (er,ec)
// throughout the maze; return false otherwise
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	stack<Coord> mazeStack;
	Coord start(sr, sc);
	mazeStack.push(start); // push initial coord to stack
	maze[sr][sc] = '/'; // Record history

	// Allow ability to know current row and column before popping off stack.
	int cr;
	int cc;

	while (!mazeStack.empty())
	{
		// Record current row/col before popping off stack.
		cr = mazeStack.top().r();
		cc = mazeStack.top().c();
		mazeStack.pop();
		
		if (cr == er && cc == ec) //if our current pos is the end, return true.
			return true;

		if() //if we can move north and haven't encountered cell, push to stack.
	
	
	
	
	
	
	}
	
	
	
	return false;
}
