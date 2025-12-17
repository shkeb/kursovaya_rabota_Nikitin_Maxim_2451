#include "Topological.h"
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        std::cout << "Example: kurcach.exe input.txt output.dot" << std::endl;
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    std::ifstream testFile(inputFilename);
    if (!testFile.is_open()) {
        std::cerr << "Error: Cannot open input file '" << inputFilename << "'" << std::endl;
        return 1;
    }
    testFile.close();

    std::cout << "Processing..." << std::endl;

    try {
        Graph currentGraph(inputFilename);
        std::vector<int> sortedOrder = currentGraph.TopologicalSort();

        currentGraph.WriteGraph(outputFilename, sortedOrder);

        std::cout << "Success! Topological sort completed." << std::endl;
        std::cout << "Output DOT file: " << outputFilename << std::endl;

        std::string pngFilename = "graph.png";

        std::string command = "\"\"C:\\Program Files\\Graphviz\\bin\\dot.exe\" -Tpng \"" +
            outputFilename + "\" -o \"" + pngFilename + "\"\"";

        std::cout << "Creating visualization: " << pngFilename << std::endl;

        int result = system(command.c_str());

        if (result == 0) {
            std::cout << "Visualization saved to: " << pngFilename << " (current folder)" << std::endl;
        }
        else {
            std::cerr << "Warning: Could not create PNG visualization" << std::endl;
            std::cerr << "Run manually in CMD:" << std::endl;
            std::cerr << "  \"C:\\Program Files\\Graphviz\\bin\\dot\" -Tpng \"" << outputFilename << "\" -o \"" << pngFilename << "\"" << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}