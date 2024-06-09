#pragma once
#include "Constants.h"
#include "Object.h"
#include "Map.h"
#include <set>
#include <array>
#include <cmath>
#include <stack>


// Struct to hold a single node
struct Node {
	// x and y value of the Node 
	int x;
	int y;
	// parent point of the node
	SDL_Point parent;

	// g, h and total cost of node for a* algo.
	int g_cost;
	int h_cost;
	int total_cost;
	
	// tells whether the node is a diagonal or not
	bool diagonal;

	bool init;

	// initalize with default values
	Node() {
		x = y = g_cost = h_cost = total_cost = 0;
		parent = {};
		diagonal = false;
		init = false;
	};

	// initalize a node given x and y values
	Node(int x, int y) {
		parent = {0, 0};
		g_cost = h_cost = total_cost = 0;
		this->x = x;
		this->y = y;
		diagonal = false;
		init = true;
	}

	// operator function to tell the set to order nodes by 
	// total cost since this is a custom object
	bool operator< (const Node& other) const {
		return total_cost < other.total_cost;
	}
	
	// () operator function to help in finding nodes.
	// this way finding is done based on same x, and y coordinates
	// rather than total cost 
	bool operator() (const Node& other) const {
		return x == other.x && y == other.y;
	}

	// equals to operator to compare to nodes
	// and return true if they have the same x and y values
	bool operator ==(const Node& other) const {
		return other.x == x && other.y == y;
	}
 };


// class for A* search 
class Astar {
public:
	// default public ctor
	Astar();

	// ctor that takes target, and start objects
	Astar(Object* target, Object* start);

	// function that calculates A* path
	stack<SDL_Point*> astar(std::array<Tile*, MAP_LENGTH>& map);

	// calculate starting position of a block given x value
	int calc_x(int x);

	// calculate starting position of a block given x value
	int calc_y(int y);

private:
	

	// start position
	Object* start;
	// goal position
	Object* target;

	// generate successors for a given node
	std::array<Node, 8> generate_successors(Node* n);
};

