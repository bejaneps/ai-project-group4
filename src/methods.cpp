#include "header.hpp"

Grid::Grid():
root(create_node(0, 0, Color::YELLOW)) {

}

Grid::Grid(int row, int col, Color c):
root(create_node(row, col, c)) {

}

Grid::~Grid() {
	delete root;
}

node* Grid::create_node(int row, int col, Color c) {
	//to allocate a memory even if memory refuses
	node *temp;
	while(true)
	{
		temp = new (std::nothrow) node;
		if(!temp) continue;
		break;
	}
	temp->col = col;
	temp->row = row;
	temp->color = c;
	temp->u = temp->d = temp->l = temp->r = nullptr;

	return temp;
}

void Grid::get_file_content(const std::string &path) {
	file_content.reserve(50);
	std::string line {};

	//opening a file
	std::ifstream file(path);
	if (file.is_open()) {
		//reading each line of file into string and then pushing it to vector
		while(std::getline(file, line)) {
			file_content.push_back(line);
		}
		
		if(file.bad()) {
			std::cout << "Error reading file" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	} else 
	{
		std::cout << "Error loading file" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return;
}

// fills the temporary array with black & white squares squares
void Grid::parse_file_content() {
	//convert character to integer
	auto ctoi = [] (const char &c) {
		return static_cast<int>(c - '0');
	};

	std::string empty_squares = file_content.at(0);

	//creating white squares in a array_grid
	for(int i = 0; i < static_cast<int>(empty_squares.size()); ) {
		long row {}, col{};
		if(empty_squares[i] == ' ') {
			++i;
			continue;
		}
		if(empty_squares[i] == '(') {
			++i;
			if(std::isdigit(empty_squares[i])) {
				row = ctoi(empty_squares[i]);
			}
			++i;
			if(std::isdigit(empty_squares[i])) {
				row = stoi(empty_squares.substr(i-1, 2));
				++i;
			}
			if(empty_squares[i] == ',') {
				++i;
				if(std::isdigit(empty_squares[i])) {
					col = ctoi(empty_squares[i]);
				}
				++i;
				if(std::isdigit(empty_squares[i])) {
					col = stoi(empty_squares.substr(i-1, 2));
					++i;
				}
				if(empty_squares[i] == ')') {
					++i;
				}
			}
		}

		array_grid[row][col] = Color::WHITE;
	}

	//creating black squares in a array_grid
	for(int r = 0; r < 12; r++) {
		for(int c = 0; c < 12; c++) {
			if(array_grid[r][c] != Color::WHITE) {
				array_grid[r][c] = Color::BLACK;
			}
		}
	}

	number_of_problems = ctoi(file_content.at(1)[0]);

	//getting coordinates of start and end squares
	for(int i = 0; i < number_of_problems; i++) {
		std::string problem = file_content.at(i+2); //coordinates of src and dest start from line 3 of problems.txt
		for(int j = 0, k = 0; j < static_cast<int>(problem.size()); ++k) {
			int row {}, col{};
			if(problem[j] == '(') {
				++j;
				if(std::isdigit(problem[j])) {
					row = ctoi(problem[j]);
				}
				++j;
				if(std::isdigit(problem[j])) {
					row = stoi(problem.substr(j-1, 2));
					++j;
				}
				if(problem[j] == ',') {
					++j;
					if(std::isdigit(problem[j])) {
						col = ctoi(problem[j]);
					}
					++j;
					if(std::isdigit(problem[j])) {
						col = stoi(problem.substr(j-1, 2));
						++j;
					}
					if(problem[j] == ')') {
						++j;
					}
				}
			}
			src_dest[i][k] = std::make_pair(row, col);
		}
	}
}

void Grid::bfs(const std::string &solution_txt) {
	std::ostream outfile ();
	if(!root) {
		node *temp = create_node(0, 0, Color::WHITE);
		root = temp;
	} else {
		node *next = root, *prev = nullptr;
		char coordinates[8];

		if(next->row < 0 || next->row > 12) {
			next = next->l;
		}
		for(int r = 0; r < GRID_SIZE; r++) {
			for(int c = 0; c < GRID_SIZE; c++) {
				sprintf(coordinates, "(%d,%d)", next->row, next->col);
			}
		}

		//fill row 1,12 ; col 1,12
		for(int r = 0; r < GRID_SIZE; r++) {
			for(int c = 0; c < GRID_SIZE; c++) {
				if(r == 0) {
					if(c == 0) {
						next->l = nullptr;
					}
					next->u = nullptr;
				} else if(c == 0) {
					next->l = nullptr;
				} else if(r == 11) {
					next->d = nullptr;
				} else if(c == 11) {
					next->r = nullptr;
				}
				
				next->color = array_grid[r][c];
			}
		}
	}

	return ;
}

void Grid::print_array_grid() {
	//array_grid
	for(int i = 0; i < GRID_SIZE; i++) {
		for(int j = 0; j < GRID_SIZE; j++) {
			if(array_grid[i][j] == Color::WHITE) {
				std::cout << "W";
			} else if(array_grid[i][j] == Color::BLACK) {
				std::cout << "B";
			}
		}
		std::cout << std::endl;
	}

	std::cout << "\n\n";

	//src and dest coordinates
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 2; j++) {
			std::cout << src_dest[i][j].first << "," << src_dest[i][j].second << " ";
		}
		std::cout << std::endl;
	}
}

void Grid::run(const std::string &problem_txt, const std::string &solution_txt) {
	get_file_content(problem_txt);
	parse_file_content();
	print_array_grid();
	std::cerr << solution_txt << std::endl;
	//bfs(solution_txt)
}