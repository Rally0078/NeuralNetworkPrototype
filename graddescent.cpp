#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <sciplot/sciplot.hpp>

int main(void)
{
    std::map<double, double> heightWeight = {{0.5, 1.4},{2.3, 1.9}, {2.9, 3.2}};
    auto residue = [](std::valarray<double> input){
        return (std::pow((1.4 - (input + 0.64 * 0.5)), 2) + std::pow((1.9 - (input + 0.64 * 2.3)), 2)+ std::pow((3.2 - (input + 0.64 * 2.9)), 2));
    };
    auto derivative = [](std::valarray<double> input){
        return (-2 * ( (1.94 - (input + 0.64 * 0.5)) + (1.9 - (input + 0.64 * 2.3)) + (3.2 - (input + 0.64 * 2.9))));
    };
    sciplot::Vec x = sciplot::linspace(0,3,100);
    sciplot::Plot2D plot1;
    plot1.legend().atTop();
    plot1.drawCurve(x, residue(x)).lineWidth(1).label("residue");
    sciplot::Figure figure = {{plot1}};
    sciplot::Canvas canvas = {{figure}};
    canvas.show();
    return 0;
}