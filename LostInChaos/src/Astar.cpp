#include "../include/Astar.h"

Astar::Astar() {
	// null values on default ctor
	start = target = nullptr;
}

Astar::Astar(Object* target, Object* start) {
	// set target and start object for searching
	this->target = target;
	this->start = start;
}

stack<SDL_Point*> Astar::astar(std::array<Tile*, MAP_LENGTH>& map) {

	// open list that stores possible nodes that should be explored
	// 8 valid neighbours of the current node
	set<Node> openList;

	int openX, openY;
	SDL_GetMouseState(&openX, &openY);

	// starting node 
	Node* s = new Node( calc_x((int) start->getX() )
		, calc_y((int) start->getY()));
	// goal NODE

	Node g(calc_x((int) target->getX() ),
		calc_y((int) target->getY() ));

	// if the tile is astar boundary for - shift the tile one block lower.
	int test = MAP_WIDTH * (g.y / TILE_HEIGHT) + ((g.x - MAP_LEFT_OFFSET) / TILE_WIDTH);
	Tile* m = map.at(test);
	if (m != nullptr) {
		if (m->getTileType() == ASTAR_BOUNDARY) {
			g.x += 32;
			g.y += 32;
		}
	}


	// adding start node to open list to begin our search
	openList.insert(*s);

	// closed list to keep track of nodes we dont have to look at again
	bool closedList[MAP_LENGTH];

	// keeping track of nodes with their parents in order to trace back the path 
	// after goal is found
	Node* nodes[MAP_LENGTH];

	// initialize closed list and nodes with default values
	for (int i = 0; i < MAP_LENGTH; i++) {
		closedList[i] = false;
		nodes[i] = new Node();
		nodes[i]->parent = {};
	}

	// keep searching while the open list is not empty
	// i.e. there are no nodes left to search
	// since the map will have no closed areas, therer will always be a path existing
	// from any given point to another.
	while (!openList.empty()) {

		// get the node with the lowest total_cost cost since set stores 
		// nodes in order. The order criteria is set to be the total_cost
		Node q = *openList.begin();

		// remove that node from open list since it's explored
		openList.erase(q);

		// if the selected node is the same as goal node.
		// goal is found hence stop searching
		if (q == g) {
			break;
		}

		// else generate 8 successors of the current selected node
		std::array<Node, 8> successors = generate_successors(&q);

		// for each of the 8 successors
		for (int i = 0; i < successors.size(); i++) {

			Node s = successors.at(i);

			if (!s.init) continue;

			// get the successor
			

			// access the same tile as successor on map and check to see
			// if it's not a wall. If it's a wall then it's an invalid successor
			// skip this succcessor since it cant be in the path

			int index = MAP_WIDTH * (s.y / TILE_HEIGHT) + ((s.x - MAP_LEFT_OFFSET) / TILE_WIDTH);
			if (index < map.size()) {
				Tile* t = map.at(index);
				// checks if the tile is not null
				if (t != nullptr) {
					int type = t->getTileType();
					if (type == MID_WALL || type == MID_WALL_BOTTOM ||
						type == MID_WALL_TOP || type == MID_WALL_VERTICAL || type == MID_WALL_L || type == MID_WALL_R ||
						type == ASTAR_BOUNDARY) {
						continue;
					}
				}
			}

			// The actual searching algorithm that calculates cost
			// and adds to list based

			/*
			g_cost is the cost to move on to the succesor from the starting point
			accumulates as we move on in order to select a better path

			h_cost is the hueristic value is the distance calculated from selected node to the
			goal point using some formula

			total_cost is the sum of g_cost and h_cost
			*/

			// assigning g_cost to nodes, if a node is diagonal it will have more 
			// g_cost than a orthogonal node (non diagonal).

			// the g_cost is calculated by adding the g_cost of the previously selected node
			// and adding a number based on diagonal or not
			if (s.diagonal) {
				continue;
			}
			else {
				s.g_cost = q.g_cost + 14;
			}

			//s.g_cost = q.g_cost + 14;
			// To calculate the h_cost (hueristic cost) first 
			// absolute difference of x and y position is calculated betewen goal 
			// and successor 

			int dx = abs(g.x - s.x);
			int dy = abs(g.y - s.y);

			// Diagonal distance:  the maximum of absolute values of differences 
			// in the goal’s x and y coordinates and the current cell’s x and y coordinates respectively

			s.h_cost = TILE_WIDTH * (dx + dy) + (16) * min(dx, dy);

			//s.h_cost = dx + dy;

			// set total cost by adding g and h
			s.total_cost = s.g_cost + s.h_cost;

			int pindex = MAP_WIDTH * (s.y / TILE_WIDTH) + (s.x / TILE_HEIGHT);


			if (pindex < MAP_LENGTH) {
				// if already in closed list skip this succecssor
				if (closedList[MAP_WIDTH * (s.y / TILE_HEIGHT) + (s.x / TILE_WIDTH)] == true) {
					continue;
				}
			}


			// find the node with same x, y in open list
			set<Node>::iterator it = std::find_if(openList.begin(), openList.end(), s);

			// if node in open list exist
			if (it != openList.end()) {

				// fetch that node from iterator
				Node p = *it;

				// if the successor has a better G cost than currently existing node
				if (s.g_cost < p.g_cost) {

					// set the parent of that node as the current selected node, so as to
					// select a better path
					if (pindex < MAP_LENGTH) {
						nodes[MAP_WIDTH * (s.y / TILE_WIDTH) + (s.x / TILE_HEIGHT)]->parent = { q.x / TILE_WIDTH, q.y / TILE_HEIGHT };
					}
				}
				// if not, do nothing and go to next successor - or end for loop
				else {
					continue;
				}
			}
			// if node does not exist in open list
			else {


				// set it's parent to selected node so path can be traced
				if (pindex < MAP_LENGTH) {
					// insert that node in open list
					openList.insert(s);
					nodes[MAP_WIDTH * (s.y / TILE_WIDTH) + (s.x / TILE_HEIGHT)]->parent = { q.x / TILE_WIDTH, q.y / TILE_HEIGHT };
				}
			}
		}

		// after dynamically allocated successors have been used,
		// deallocate them to clear up memory
		/*for (int i = 0; i < successors.size(); i++) {
			delete successors.at(i);
		}*/

		// add the selected node to closed list
		closedList[MAP_WIDTH * (q.y / TILE_HEIGHT) + (q.x / TILE_WIDTH)] = true;
	}

	// after A* is completed, and a path is found
	// get the goals x and y values for path tracing
	int pX = g.x / TILE_WIDTH;
	int pY = g.y / TILE_HEIGHT;

	// create a stack to store the path in it's correct order
	stack<SDL_Point*> path;

	// keep creating a path while the parent x and y values are not equal to the goal 
	// node i.e. goal node is reached
	while (!(nodes[MAP_WIDTH * (pY)+pX]->parent.x == (pX * TILE_WIDTH)
		&& nodes[MAP_WIDTH * (pY)+pX]->parent.y == (pY * TILE_HEIGHT))) {

		// create an sdl point of the coordinates on actual SDL Screen 
		SDL_Point* rp = new SDL_Point();
		rp->x = pX * TILE_WIDTH;
		rp->y = pY * TILE_WIDTH;
		SDL_Point r = { pX * TILE_WIDTH, pY * TILE_HEIGHT };
		// push that point on the stack
		path.push(rp);

		// fetch current node's parent x and y values
		int tempX = nodes[MAP_WIDTH * (pY)+pX]->parent.x;
		int tempY = nodes[MAP_WIDTH * (pY)+pX]->parent.y;

		// update the loop values to next parent
		pX = tempX;
		pY = tempY;
	}

	// clean up nodes after path has been traced
	for (int i = 0; i < MAP_LENGTH; i++) {
		delete nodes[i];
	}

	// delete start node
	delete s;

	// return stack as a path
	return path;
}

std::array<Node, 8> Astar::generate_successors(Node* n) {

	std::array<Node, 8> nodes;

	// init array to nullptr
	for (Node p : nodes) {
		p = Node();
	}

	int x, y;

	// TOP
	x = n->x;
	y = n->y - 5;
	if (y > 0) nodes[0] =  Node(x, calc_y(y));

	// BOTTOM
	y = n->y + TILE_HEIGHT + 5;
	if (y <= SCREEN_HEIGHT) nodes[1] =  Node(n->x, calc_y(y));

	// LEFT
	x = n->x - 5;
	y = n->y;
	if (x > MAP_LEFT_OFFSET) nodes[2] = Node(calc_x(x), y);

	// RIGHT
	x = n->x + TILE_WIDTH + 5;
	y = n->y;
	if (x < SCREEN_WIDTH) nodes[3] = Node(calc_x(x), y);

	//// TOP LEFT DIAGONAL
	//nodes[4] = Node(calc_x(n->x - 5), calc_y(n->y - 5));
	//// TOP RIGHT DIAGNOAL
	//nodes[5] =  Node(calc_x(n->x + TILE_WIDTH + 5), calc_y(n->y - 5));
	//// BOTTOM LEFT DIAGNOAL
	//nodes[6] =  Node(calc_x(n->x - 5), calc_y(n->y + TILE_HEIGHT + 5));
	//// BOTTOM RIGHT DIAGNOAL
	//nodes[7] =  Node(calc_x(n->x + TILE_WIDTH + 5), calc_y(n->y + TILE_HEIGHT + 5));

	//// set diagonal to true for diagonal nodes
	//for (int i = 4; i < 7; i++) {
	//	nodes[i].diagonal = true;
	//}

	return nodes;

}
int Astar::calc_x(int x) {
	// calculate remainders
	double x_remainder = (double)x / TILE_WIDTH;

	// multiplying decimal remainder value with BLOCK SIZE 
	//gives amount of x, y to be subtracted to reach block start
	x_remainder = (x_remainder - (int)x_remainder) * TILE_WIDTH;

	// subtract from mouse click values
	int x_val = x - (int)x_remainder;

	// return the value 
	return x_val;
}

// same procedure followed as calculating the x coordinate
int Astar::calc_y(int y) {
	double y_remainder = double(y) / TILE_WIDTH;

	y_remainder = (y_remainder - (int)y_remainder) * TILE_WIDTH;

	int y_val = y - (int)y_remainder;

	return y_val;
}