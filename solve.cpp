#include "maze.h"
#include "path.h"
#include<queue>
#include<vector>
#include<list>
#include<tuple>
#include<utility>
#include<iostream>
#include<climits>
#include<sstream>
using namespace std;

path solve_dfs(Maze& m, int rows, int cols);
path solve_bfs(Maze& m, int rows, int cols);
path solve_dijkstra(Maze& m, int rows, int cols);
path solve_tour(Maze& m, int rows, int cols);

//Start User Addition


//This function takes in a point and a list of visited points
//Return true if the point was found in the list.
//If the point was found, then that means we should not travel into that cell

bool hasVisited(point toCheck, list<point> visited);

bool hasSeen(point toCheck, list<WeightedPoint> seen);
//End User Addition

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        cerr << "usage:\n"
             << "./maze option rows cols\n"
             << " options:\n"
             << "  -dfs: depth first search (backtracking)\n"
             << "  -bfs: breadth first search\n"
             << "  -dij: dijkstra's algorithm\n"
             << "  -tour: all corners tour\n"
             << "  -basic: run dfs, bfs, and dij\n"
             << "  -advanced: run dfs, bfs, dij and tour" << endl;
        return 0;
    }
    string opt(argv[1]);

    int rows, cols;
    stringstream s;
    s << argv[2] << " " << argv[3];
    s >> rows >> cols;

    // construct a new random maze;
    Maze m(rows, cols);

    // print the initial maze out
    cout << "Initial maze" << endl;
    m.print_maze(cout, opt == "-dij" || opt == "-tour");

    if(opt == "-dfs")
    {
        cout << "\nSolved dfs" << endl;
        path p = solve_dfs(m, rows, cols);
        m.print_maze_with_path(cout, p, false, false);
    }


    if(opt == "-bfs")
    {
        cout << "\nSolved bfs" << endl;
        path p = solve_bfs(m, rows, cols);
        m.print_maze_with_path(cout, p, false, false);
    }

    if(opt == "-dij")
    {
        cout << "\nSolved dijkstra" << endl;
        path p = solve_dijkstra(m, rows, cols);
        m.print_maze_with_path(cout, p, true, false);
    }

    if(opt == "-tour")
    {
        cout << "\nSolved all courners tour" << endl;
        path p = solve_tour(m, rows, cols);
        m.print_maze_with_path(cout, p, true, true);
    }
    if(opt == "-basic")
    {
        cout << "\nSolved dfs" << endl;
        path p = solve_dfs(m, rows, cols);
        m.print_maze_with_path(cout, p, false, false);

        cout << "\nSolved bfs" << endl;
        p = solve_bfs(m, rows, cols);
        m.print_maze_with_path(cout, p, false, false);

        cout << "\nSolved dijkstra" << endl;
        p = solve_dijkstra(m, rows, cols);
        m.print_maze_with_path(cout, p, true, false);
    }
    if(opt == "-advanced")
    {
        cout << "\nSolved dfs" << endl;
        path p = solve_dfs(m, rows, cols);
        m.print_maze_with_path(cout, p, false, false);

        cout << "\nSolved bfs" << endl;
        p = solve_bfs(m, rows, cols);
        m.print_maze_with_path(cout, p, false, false);

        cout << "\nSolved dijkstra" << endl;
        p = solve_dijkstra(m, rows, cols);
        m.print_maze_with_path(cout, p, true, false);

        cout << "\nSolved all courners tour" << endl;
        p = solve_tour(m, rows, cols);
        m.print_maze_with_path(cout, p, true, true);
    }
}

//Start User Addition

bool hasVisited(point toCheck, vector<point> visited){

	//This will go through the vector of visited cells to see if the point has been visited
	for(int i = 0; i < visited.size() ; ++i)
	{
		if(toCheck.first == visited.at(i).first && toCheck.second == visited.at(i).second)
			return true;

	}

	return false;
}
bool hasSeen(point toCheck, vector<WeightedPoint> seen){

	//This will go through the vector of visited cells to see if the point has been visited
	for(int i = 0; i < seen.size() ; ++i)
	{
		if(toCheck.first == seen.at(i)._point.first && toCheck.second == seen.at(i)._point.second)
			return true;

	}

	return false;
}
//End User Addition

//Implement these
path solve_dfs(Maze& m, int rows, int cols)
{
	//This is a list of points that make up the solution
	path myPath; 
	//This keeps track of the current coordinates
	point aPoint;
	//This stack is essential in keeping track of which points
	//are added to the solved path
	stack <point> pile;
	//This vector keeps track of the visited cells
	vector <point> visited;

	//Initialize the start point
	aPoint.first = 0;
	aPoint.second = 0;

	//Push the starting point into the visited list. This effectively
	//turns the cell into a wall. Using the can_go functions will return true,
	//but there will be another conditional to check if the cell has been visited
	visited.push_back(aPoint);

	//Push the starting point onto the stack
	pile.push(aPoint);

	//For iterating through the path later
	path::iterator it;

	//We'll append to the solution path later by using the stack...

	//The depth first search will attempt to move into a cell, if it can.
	//Once it does, it will add the coordinates of that cell onto the stack
	//and search for other potential cells to go to. If it cannot go to any,
	//it will pop off of the stack and go to the next available cell from the stack
	while(aPoint.first != rows-1 || aPoint.second != cols-1)
	{
		
		//If we can go down, AND the cell hasn't been visited
		if(m.can_go_down(aPoint.first , aPoint.second ) == true && hasVisited(aPoint+moveIn(DOWN), visited) == false)
		{	
			//Go down, into that cell
			aPoint = aPoint + moveIn(DOWN);

			//Append the cell to visited cells
			visited.push_back(aPoint);

			//Push the point onto the solution stack
			pile.push(aPoint);

		}
		else if(m.can_go_left(aPoint.first , aPoint.second ) == true && hasVisited(aPoint+moveIn(LEFT), visited) == false)
		{	
			aPoint = aPoint + moveIn(LEFT);
			visited.push_back(aPoint);
			pile.push(aPoint);

		}
		else if(m.can_go_up(aPoint.first , aPoint.second ) == true && hasVisited(aPoint+moveIn(UP), visited) == false)
		{	
			aPoint = aPoint + moveIn(UP);
			visited.push_back(aPoint);
			pile.push(aPoint);

		}
		else if(m.can_go_right(aPoint.first , aPoint.second ) == true && hasVisited(aPoint+moveIn(RIGHT), visited) == false)
		{	
			aPoint = aPoint + moveIn(RIGHT);
			visited.push_back(aPoint);
			pile.push(aPoint);

		}
		//If we reached a dead end (We couldnt move anywhere since we walled off the cell we came from)
		//then we go to the previous cell by popping the dead end off of the stack and returning to
		//the cell on the now exposed top of the stack.
		else
		{
			//We're in a dead end, let's pop this off the stack and go back to the cell before
			pile.pop();
			//We moved to the last point by going to the new top of the stack
			aPoint = pile.top();

			//The loop will now continue from that part, but we have walled off the dead end to prevent going back into it
		}

	}

	//We finished going through the maze, now unwind the stack and add it to the solved path
	cout << "Pile size is: " << pile.size() << endl;
	while(pile.empty() == false)
	{
		myPath.push_back(pile.top());
		pile.pop();
	}

	//Reverse the list since it was appended in the opposite order
	myPath.reverse();

	//Prints out the information on the node travelled to
	cout << "Path size: " << myPath.size() << endl;
	cout << "The path contains: ";
	for(it = myPath.begin(); it!=myPath.end(); ++it)
	{
		cout << ' ' << it->first << ',' << it->second;

	}
	cout << endl;

	return myPath;
}

path solve_bfs(Maze& m, int rows, int cols)
{
	//This is a list of points that make up the solution
	path myPath; 
	
	//The starting point
	point startPoint;
	
	//This keeps track of the current coordinates
	point aPoint;
	
	//This queue is essential in keeping track of which points
	//are added to the solved path
	queue <point> line;
	
	//This vector keeps track of the visited cells
	vector <point> visited;

	//This vector keeps track of the cell's parent
	//Once we find the solution, we will backtrack until we reach the starting cell 
	//We will append the cells along the way then reverse them for the solution
	vector <point> parents;

	//Initialize the start point
	startPoint.first = 0;
	startPoint.second = 0;
	
	//Set the current pointer at the start
	aPoint.first = startPoint.first;
	aPoint.second = startPoint.second;

	//Push the starting point into the visited list. This effectively
	//turns the cell into a wall. Using the can_go functions will return true,
	//but there will be another conditional to check if the cell has been visited
	visited.push_back(aPoint);

	//Push the starting point onto the queue
	line.push(aPoint);

	//For iterating through the path later
	path::iterator it;
	//The starting cell's parent is itself
	parents.push_back(aPoint);


	while(aPoint.first != rows-1 || aPoint.second != cols-1)
	{
		
		//If we can go down, AND the cell hasn't been visited
		if(m.can_go_down(aPoint.first , aPoint.second ) == true && hasVisited(aPoint+moveIn(DOWN), visited) == false)
		{	
			//Add that next cell to the queue to check later
			line.push(aPoint+moveIn(DOWN));
			
			//Append the cell to visited cells (Or in this case, cells we checked)
			visited.push_back(aPoint+moveIn(DOWN));

			//The current point is this new point's parent
			parents.push_back(aPoint);

		}
		if(m.can_go_left(aPoint.first , aPoint.second ) == true && hasVisited(aPoint+moveIn(LEFT), visited) == false)
		{
			line.push(aPoint+moveIn(LEFT));
			visited.push_back(aPoint+moveIn(LEFT));
			parents.push_back(aPoint);

		}
		if(m.can_go_up(aPoint.first , aPoint.second ) == true && hasVisited(aPoint+moveIn(UP), visited) == false)
		{	
			line.push(aPoint+moveIn(UP));
			visited.push_back(aPoint+moveIn(UP));
			parents.push_back(aPoint);

		}
		if(m.can_go_right(aPoint.first , aPoint.second ) == true && hasVisited(aPoint+moveIn(RIGHT), visited) == false)
		{	
			line.push(aPoint+moveIn(RIGHT));
			visited.push_back(aPoint+moveIn(RIGHT));
			parents.push_back(aPoint);

		}
		//Once we have checked all adjacent cells, we'll move onto the next cell the queue and check ITS adjacent cells
		
		line.pop();
		aPoint = line.front();


		//We will now be at the next cell to check in the queue
	}
	
	//This variable gets the solution point and find out where to start backtracking
	//It also acts as a container for a child point
	point sPoint;
	sPoint.first = rows-1;
	sPoint.second = cols-1;

	//Print visited and parent vectors
	cout << " Visited: ";
	for(int i = 0; i < visited.size() ; ++i)
	{
		cout << visited.at(i).first << ',' << visited.at(i).second << ' ';
	}

	//Print visited and parent vectors
	cout << endl << " Parents: ";
	for(int i = 0; i < parents.size() ; ++i)
	{
		cout << parents.at(i).first << ',' << parents.at(i).second << ' ';
	}


	//Now we start at the solution and backtrack to find the shortest path
	//Keep looking at parents until we get to the starting position
	//This variable will keep track of the child's position in the visited vector
	int child;
	while(sPoint.first != 0 || sPoint.second != 0)
	{
		//Get the position of the child cell
		//by traversing through the visited vector
		for(int i = 0; i < visited.size(); ++i)
		{
			//If the point is the child we're looking for
			if(visited.at(i) == sPoint)
			{

				myPath.push_back(visited.at(i));
				child = i;
				
				//Stop traversing through the visited vector because we have found the child
				i = visited.size();

			}

		}

		//Set the new child
		sPoint = parents.at(child);

	}
	//Make sure to append the start point before reversing
	myPath.push_back(startPoint);
	//Since we added the points in the reverse order, flip the list
	myPath.reverse();

	
	cout << endl << "Path size: " << myPath.size() << endl;
	cout << "The path contains: ";
	for(it = myPath.begin(); it!=myPath.end(); ++it)
	{
		cout << ' ' << it->first << ',' << it->second;

	}
	cout << endl;


	return myPath;
}

path solve_dijkstra(Maze& m, int rows, int cols)
{
	//This is a list of points that make up the solution
	path myPath; 
	
	//The starting point
	point startPoint;
	
	//This keeps track of the current coordinates
	point aPoint;
	//This keeps track of the Weighted Point we're trying to find to update it's tentative cost
	int child;
	//This variable stores the current coordinates, the cost to get there, and the tentative cost to get there from the start
	WeightedPoint wPoint;
	
	//This priority queue is essential in keeping track of which points are added to the solved path
	//The paramaters are Type of element stored, what they're stored in, and the comparison used to decide where to place new elements
	//Basically, we have a class called WeightedPoint which stores a point and it's cost to go in a direction
	//When we append to this queue, it will check the cell with the lowest cost first
	priority_queue <WeightedPoint, vector<WeightedPoint>, CostCompare> vip;
	
	//This vector keeps track of the visited cells
	vector <point> visited;
	//This vector keeps track of cells that have been seen but not visited
	//This is so that we can backtrack parents once we've contructed a path
	vector <WeightedPoint> seen;

	//This vector keeps track of the cell's parent
	//Once we find the solution, we will backtrack until we reach the starting cell 
	//We will append the cells along the way then reverse them for the solution
	vector <point> parents;

	//Initialize the start point
	startPoint.first = 0;
	startPoint.second = 0;
	
	//Set the current pointer at the start
	//Set the starting weighted point too
	aPoint.first = startPoint.first;
	aPoint.second = startPoint.second;
	wPoint._point = aPoint;
	wPoint._cost = 0;
	wPoint._tentative = 0;

	//Push the starting point into the visited list. This effectively
	//turns the cell into a wall. Using the can_go functions will return true,
	//but there will be another conditional to check if the cell has been visited
	//visited.push_back(aPoint);

	//Push the starting point onto the pqueue
	vip.push(wPoint);

	//For iterating through the path later
	path::iterator it;
	//The starting cell's parent is itself
	//parents.push_back(aPoint);

	//All cells start with a cost of infinity, (Or the biggest int possible)
	//If the cell's previous cost is larger than the next comparison, change it to the smaller value
	int infinity = INT_MAX;
	//Tentative starts at zero since the distance from the start is 0
	int tentative = 0;
	while(vip.empty() == false)
	{
		
		vip.pop();
		//If we can go down, AND the cell hasn't been visited
		if(m.can_go_down(aPoint.first , aPoint.second ) == true && hasVisited(aPoint+moveIn(DOWN), visited) == false)
		{	
			//Add that next cell to the queue to check later
			//Do this by finding out the cost and putting this
			//weighted point into the priority queue
			wPoint._point = aPoint+moveIn(DOWN);
			wPoint._cost = m.cost(aPoint.first, aPoint.second, DOWN);

			//If we haven't seen this node yet, then we calculate tentative distance using infinity
			if(hasSeen(aPoint+moveIn(DOWN), seen) == false)
			{
				if(wPoint._tentative + wPoint._cost < infinity)
					wPoint._tentative = wPoint._cost + tentative;
			}
			//If we have seen it, we want to see if it's tentative distance from the start can be changed
			else
			{
				//Go to the seen cell in question
				for(int i = 0; i < seen.size() ; ++i)
				{
					if(seen.at(i)._point == aPoint+moveIn(DOWN))
					{
						//Save the index to look for the corresponding parent
						child = i;
						i = seen.size();
						//Stop searching
					}
				}
				//Now that we have the point, we can update it
				if(tentative < seen.at(child)._tentative)
				{
					seen.at(child)._tentative = tentative;
				}
			}
			vip.push(wPoint);

			//Append the cell to seen (cells we checked)
			seen.push_back(wPoint);

			//The current point is this new point's parent
			parents.push_back(aPoint);

		}
		
		if(m.can_go_left(aPoint.first , aPoint.second ) == true && hasVisited(aPoint+moveIn(LEFT), visited) == false)
		{
			wPoint._point = aPoint+moveIn(LEFT);
			wPoint._cost = m.cost(aPoint.first, aPoint.second, LEFT);
			if(wPoint._tentative + wPoint._cost < infinity)
				wPoint._tentative = wPoint._cost + tentative;
			else
			{
				for(int i = 0; i < seen.size() ; ++i)
				{
					if(seen.at(i)._point == aPoint+moveIn(DOWN))
					{
						child = i;
						i = seen.size();
					}
				}
				if(tentative < seen.at(child)._tentative)
				{
					seen.at(child)._tentative = tentative;
				}
			}
			vip.push(wPoint);

			seen.push_back(wPoint);
			parents.push_back(aPoint);

		}
		if(m.can_go_up(aPoint.first , aPoint.second ) == true && hasVisited(aPoint+moveIn(UP), visited) == false)
		{
			wPoint._point = aPoint+moveIn(UP);
			wPoint._cost = m.cost(aPoint.first, aPoint.second, UP);
			if(wPoint._tentative + wPoint._cost < infinity)
				wPoint._tentative = wPoint._cost + tentative;
			else
			{
				for(int i = 0; i < seen.size() ; ++i)
				{
					if(seen.at(i)._point == aPoint+moveIn(DOWN))
					{
						child = i;
						i = seen.size();
					}
				}
				if(tentative < seen.at(child)._tentative)
				{
					seen.at(child)._tentative = tentative;
				}
			}
			vip.push(wPoint);

			seen.push_back(wPoint);
			parents.push_back(aPoint);


		}
		if(m.can_go_right(aPoint.first , aPoint.second ) == true && hasVisited(aPoint+moveIn(RIGHT), visited) == false)
		{	
			wPoint._point = aPoint+moveIn(RIGHT);
			wPoint._cost = m.cost(aPoint.first, aPoint.second, RIGHT);
			if(wPoint._tentative + wPoint._cost < infinity)
				wPoint._tentative = wPoint._cost + tentative;
		else
			{
				for(int i = 0; i < seen.size() ; ++i)
				{
					if(seen.at(i)._point == aPoint+moveIn(DOWN))
					{
						child = i;
						i = seen.size();
					}
				}
				if(tentative < seen.at(child)._tentative)
				{
					seen.at(child)._tentative = tentative;
				}
			}
			vip.push(wPoint);

			seen.push_back(wPoint);
			parents.push_back(aPoint);

		}
		
		
		//Once we've considered all of the unvisited neighbors of the current node of the current node,
		//mark the current node as visited and remove it from the unvisited set. A visited node will
		//never be checked again
		visited.push_back(aPoint);

		wPoint = vip.top();
		aPoint = wPoint._point; //Make sure to set the current point to the top priority too
		tentative = wPoint._tentative; //The tentative for this current point is taken
		//We will now be at the next cell to check in the queue

	}



	//This variable gets the solution point and find out where to start backtracking
	//It also acts as a container for a child point
	point sPoint;
	sPoint.first = rows-1;
	sPoint.second = cols-1;

	//Print visited vectors
	cout << " Visited: ";
	for(int i = 0; i < visited.size() ; ++i)
	{
		cout << visited.at(i).first << ',' << visited.at(i).second << ' ';
	}

	//Print parent vectors
	cout << endl << endl << " Parents: ";
	for(int i = 0; i < parents.size() ; ++i)
	{
		cout << parents.at(i).first << ',' << parents.at(i).second << ' ';
	}

	//Print seen vectors
	cout << endl << endl << "    Seen: ";
	for(int i = 0; i < seen.size() ; ++i)
	{
		//cout << seen.at(i)._tentative << ' ';
		cout << seen.at(i)._point.first << ',' << seen.at(i)._point.second << ' ';
	}
	cout << endl;


	//Now we start at the solution and backtrack to find the shortest path
	//Keep looking at parents until we get to the starting position
	//This variable will keep track of the child's position in the visited vector
	//int child;
	while(sPoint.first != 0 || sPoint.second != 0)
	{
		//Get the position of the child cell
		//by traversing through the visited vector
		for(int i = 0; i < seen.size(); ++i)
		{
			//If the point is the child we're looking for
			if(seen.at(i)._point == sPoint)
			{

				myPath.push_back(seen.at(i)._point);
				child = i;
				
				//Stop traversing through the visited vector because we have found the child
				i = seen.size();

			}

		}

		//Set the new child
		sPoint = parents.at(child);

	}
	//Make sure to append the start point before reversing
	myPath.push_back(startPoint);
	//Since we added the points in the reverse order, flip the list
	myPath.reverse();

	
	cout << endl << "Path size: " << myPath.size() << endl;
	cout << "The path contains: ";
	for(it = myPath.begin(); it!=myPath.end(); ++it)
	{
		cout << ' ' << it->first << ',' << it->second;

	}
	cout << endl;

	return myPath;
}

path solve_tour(Maze& m, int rows, int cols)
{
    //Not doing advanced
    return list<point>();
}
