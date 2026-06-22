/**
 * @file Parser.hpp
 * @details Located in src\Parser\Parser.hpp
 *
 * @author Tabouret
 * @date 05/06/2026 11:16
 */

#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../Shapes/Shapes.hpp"

class Parser {
  private:
    std::string filePath;
    std::string fileContent;

    std::vector<Point> vertices;
    std::vector<Shape*> shapes;

    void parse();

  public:
    Parser();

    void init(std::string path);
    void printContent();

    std::vector<Shape*> getShapes();
};

#endif  // PARSER_H
