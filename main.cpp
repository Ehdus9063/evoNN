#include <string>
#include <sstream> // istringstream
#include <fstream> // ifstream
#include <unistd.h> // opterr
#include "World.hpp"
//#include <ctime>

#define EPOCHS 100
#define GENERATIONS 50
#define MIN_SUS 0.0
#define MAX_SUS 50.0

using namespace std;


// Function to read in the map, given the name of the csv file
vector< vector<double> > readMap(string inputName) {

	// We are saving the map into a vector of vector of double
	vector< vector<double> > inputMap;

	// Open ifstream
	ifstream inputFile(inputName.c_str());
	int i = 0;

	while (inputFile) {
		i++;
		string s;
		
		// Skip empty lines
		if (!getline(inputFile, s)) break;

		// If the line is not a comment (#)
		if (s[0] != '#') {
			// Open stringstream
			istringstream ss (s);
			vector<double> row;

			// While stringstream
			while (ss) {
				string curr;

				// Skip ","
				if (!getline(ss, curr, ',')) break;

				// Append the word to the row
				try {
					row.push_back(stof(curr));
				} catch (const invalid_argument e) {
					cout << "NaN found in file " << inputName << endl;
					e.what();
				}				
			}
			// Append the row to the map
			inputMap.push_back(row);
		}
	}

	// Check that the file is valid	
	if (!inputFile.eof()) {
		cerr << "Could not read file " << inputName << "\n";
		__throw_invalid_argument("File not found");
	}

	return inputMap;
}

// Function to output usage for the user
void usage (char* program) {
	cout << program << " usage: " << endl;
	string usage;
	
	usage = "\n\t{filename}: The map to load"	
		"\n\tOptional:"
			"\n\t-c {number of creatures}: The number of creatures per generation (default = 1)"
			"\n\t-e {epochs}: The number of epochs per generation (default = " + to_string(EPOCHS) + ")"
			"\n\t-g {generations}: The number of generations of creatures (default = " + to_string(GENERATIONS) + ")"
			"\n\t-l {learning rate}: Learning rate for weight adjustment (default = 0.5)"
			"\n\t-m {minimum sustainability}: The minimum sustainability score possible for each tile (default = 0.0)"
			"\n\t-M {maximum sustainability}: The maximum sustainability score possible for each tile (default = 50.0)"
			"\n\t-s {shift}: Shift in node activation function (default = 0.3)"
			"\n\t-w {weights}: Initial range of connection strength (default = 0.15)"
			"\n\n\t Example: ./evoNN  10x10_0x50.csv -c 10 -e 50 -g 50 -l 0.9 -m 0.0 -M 20.0 \n";

	cout << usage << endl;
	exit(1);
}

void getArgs(int argc, char** argv, string& input, int& numCreature, int& epochs, int& generations, double& learningRate, double& minS, double& maxS, double& shift, double& weight) {
	learningRate = epochs = -1;
	
	opterr = 1;
	char c;

	input = argv[1];

	while ((c = getopt(argc, argv, "c:e:l:m:M:s:w:g")) >= 0) {
		switch(c) {
			case 'c':
				numCreature = atoi(optarg);
				break;	
			case 'e':
				epochs = atoi(optarg);
				break;
			case 'g':
				generations = atoi(optarg);
				break;	
			case 'l':
				learningRate = atof(optarg);
				break;
			case 'm':
				minS = atof(optarg);
				break;
			case 'M':
				maxS = atof(optarg);
				break;
			case 's':
				shift = atof(optarg);
				break;
			case 'w':	
				weight = atof(optarg);
				break;
			case '?':
				usage(argv[0]);
				break;
			default:
				exit(1);	
		}
	}
}


int main(int argc, char** argv) {

	int epochs = EPOCHS;
	int numCreature = DEFAULT_POP;
	int generations = GENERATIONS;
	double learningRate = DEF_LRATE;
	double minS = MIN_SUS;
	double maxS = MAX_SUS;
	double shift = SHIFT_DEFAULT;
	double weight = EDGE_INIT;
	string input;
	
	if (argc == 1) usage(argv[0]);
		
	getArgs(argc, argv, input, numCreature, epochs, generations, learningRate, minS, maxS, shift, weight);
	// clock_t start;
	// double duration;
	
	vector< vector<double> > inputMap = readMap("10x10_0x50.csv");

	// Output the inital map
	for (auto l: inputMap) {
		for (auto x : l) {
			printf("%2.2lf ", x);
		}
		cout << endl;
	}

	/*
	int m,f,c;
	m = 10;
	f = 30;
	c = 1;

	// Check for illegal world
	if (f < 1 || c < 1) {
		cout << "We need at least one food and one creature to work with." << endl;
		return -1;
	}
	else if ((m * m) < (f + c)) {
		cout << "The sum of food and creatures cannot exceed the amount of space provided in this world." << endl;
		return -1;
	} 

	World world(m, f, c);
    
	world.populateFood();
	world.populateCreature();

	cout << "Displaying a world that is " << m << " x " << m << " in size" << endl;
    world.showWorld();

	for (int i = 0; i < ITERATIONS; i++) {
		if (world.moveCreatures()) {
			cout << "Iteration " << i << endl;
			world.showWorld();
		} else {
			cout << "World terminated " << endl;
			break;
		}
	}
	*/

	return 0;

}
