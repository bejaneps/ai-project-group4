#include "header.hpp"

int main(int argc, char *argv[]) {
	if(argc < 3) {
		std::cerr << "Usage ./main path_to_probles.txt path_to_solution.txt" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	Grid gr{};
	gr.run(static_cast<std::string>(argv[1]), static_cast<std::string>(argv[2]));

	std::exit(EXIT_SUCCESS);
}