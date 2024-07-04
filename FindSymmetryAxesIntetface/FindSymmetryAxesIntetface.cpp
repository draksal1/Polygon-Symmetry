#include "..//PolygonSymmetry/Polygon.h"
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::cout << "Hello! This program finds the axes of symmetry of convex Polygon." << std::endl;
    std::cout << "Make sure the polygon is convex." << std::endl;
    std::cout << "Please write the name of text file with points of polygon." << std::endl;
    std::cout << "For example - \"Example.txt\"." << std::endl;
    std::cout << "Write exit to close the program" << std::endl;

    std::ifstream file;
    std::string filename;

    while (true) {
        std::cout << "Enter the filename: ";
        std::cin >> filename;
        if (filename == "exit") {
            return 0;
        }
        file.open(filename);

        if (!file) {
            std::cerr << "Failed to open/find the file: " << filename << ". Please try again." << std::endl;
            file.clear();
        }
        else {
            break;
        }
    }

    std::vector<Point> points;
    float x, y;
    while (file >> x >> y) {
        points.emplace_back(Point(x, y));
    }

    file.close();

    std::cout << "Sucsessfull reading" << std::endl;

    std::vector<Axis> result;

    try {
        Polygon polygon = Polygon(points);
        result = polygon.FindAxesOfSymmetry();
    }
    catch(std::invalid_argument){
        system("cls");
        std::cout << "Bad polygon, reload program" << std::endl;
        return 0;
    }

    if (result.size() == 0){
        std::cout << "non-symmetric" << std::endl;
    }
    else {
        std::cout << "Axes of symmetry:" << std::endl;
        for (auto& it : result) {
            std::cout << it.getFirst().GetX() << " "  << it.getFirst().GetY() << " " << "--" << " "
                << it.getSecond().GetX() << " " << it.getSecond().GetY() << std::endl;
        }
    }

    return 0;
}