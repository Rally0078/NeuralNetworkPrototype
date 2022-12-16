#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <sciplot/sciplot.hpp>

template<typename Functor>
double GradientDescentIntercept(Functor functor1, double initIntercept = 0.0)
{
    double learningRate = 0.1;
    std::valarray<double> intercept(initIntercept, 1);
    std::valarray<double> slope = functor1(intercept);
    int iterCount = 0;
    while(std::abs(slope[0]) >=1e-4)
    {
        std::cout<<++iterCount;
        std::cout<<": Intercept = "<<intercept[0] << ", Slope = " << slope[0] << std::endl;
        slope = functor1(intercept);
        intercept = intercept - (slope * learningRate);
    }
    return intercept[0];
}
int main(void)
{
    std::map<double, double> heightWeight = {{0.5, 1.4},{2.3, 1.9}, {2.9, 3.2}};
    auto residue = [](std::valarray<double> input){
        return (std::pow((1.4 - (input + 0.64 * 0.5)), 2) + std::pow((1.9 - (input + 0.64 * 2.3)), 2)+ std::pow((3.2 - (input + 0.64 * 2.9)), 2));
    };
    auto derivative = [](std::valarray<double> input){
        return (-2 * ( (1.4 - (input + 0.64 * 0.5)) + (1.9 - (input + 0.64 * 2.3)) + (3.2 - (input + 0.64 * 2.9))));
    };
    sciplot::Vec x = sciplot::linspace(0,3,100);
    sciplot::Plot2D plot1;
    std::cout<<"Gradient descent intercept = " << GradientDescentIntercept(derivative);
    plot1.legend().atTop();
    plot1.drawCurve(x, residue(x)).lineWidth(1).label("residue");
    sciplot::Figure figure = {{plot1}};
    sciplot::Canvas canvas = {{figure}};
    canvas.show();
    return 0;
}