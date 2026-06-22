/**
 * @file Parser.cpp
 * @details src\Parser\Parser.cpp
 *
 * @author Tabouret
 * @date 05/06/2026 11:20
 */

#include "Parser.hpp"

Parser::Parser() {}

void Parser::init(std::string path) {
    filePath = path;
    std::ifstream fileStream(filePath);

    if (!fileStream.is_open()) {
        std::cerr << "Error: Could not open file: " << filePath << std::endl;
        return;
    }

    std::stringstream buf;
    buf << fileStream.rdbuf();
    fileContent = buf.str();

    parse();
}

void Parser::printContent() { std::cout << fileContent; }

std::vector<Shape*> Parser::getShapes() { return shapes; }

void Parser::parse() {
    std::istringstream stream(fileContent);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream ls(line);
        std::string token;
        ls >> token;

        if (token == "v") {
            double x, y, z;
            if (ls >> x >> y >> z)
                vertices.push_back(Point(x, y, z));

        } else if (token == "f") {
            std::vector<int> indices;
            std::string vtok;

            while (ls >> vtok) {
                // Each face token can be "v", "v/vt", "v//vn", or "v/vt/vn"
                // We only need the vertex index (the first number).
                int idx = std::stoi(vtok.substr(0, vtok.find('/')));

                // OBJ indices are 1-based; negative means relative to end.
                if (idx < 0)
                    idx = (int)vertices.size() + idx;
                else
                    idx -= 1;

                indices.push_back(idx);
            }

            // Fan triangulation: (0,1,2), (0,2,3), (0,3,4), ...
            int n = (int)vertices.size();
            for (int i = 1; i + 1 < (int)indices.size(); i++) {
                int a = indices[0], b = indices[i], c = indices[i + 1];
                if (a >= 0 && a < n && b >= 0 && b < n && c >= 0 && c < n)
                    shapes.push_back(new Triangle(vertices[a], vertices[b], vertices[c]));
            }
        }
    }
}
