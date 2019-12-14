#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream> //std::cout
#include <string> //std::string, std::getline()
#include <fstream> //std::ifstream, std::ostream
#include <cstdlib> //std::exit()
#include <vector> //std::vector
#include <cctype> //std::isdigit()
#include <utility> //std::pair
#include <array> //std::array

const int GRID_SIZE = 12;

enum class Color {
	BLACK, //problem square
	WHITE, //empty square
	RED, //destination square
	YELLOW //beginning square
};

class node {
	int row, col;
	node *u, *d, *l, *r;
	Color color;

	friend class Grid;
};

class Grid {
private:
	node *root;

	//temporary array that will hold white and black spaces of grid
	Color array_grid[12][12]{};

	//content of a file line by line
	std::vector<std::string> file_content;

	int number_of_problems {};

	//coordinates of problems
	std::pair<int, int> src_dest[3][2] {};

private:
	// create an empty node
	node* create_node(int row, int col, Color c);

	// reads a file from path and returns it's content.
	void get_file_content(const std::string &path);

	// parses the content of a file into temporary array grid
	void parse_file_content();

	// applies bfs to a grid
	void bfs(const std::string &solution_txt);

	// prints grid, for debugging purposes
	void print_array_grid();

public:
	Grid();
	Grid(int row, int col, Color c);
	~Grid();

	// run a program
	void run(const std::string &problem_txt, const std::string &solution_txt);
};

#endif