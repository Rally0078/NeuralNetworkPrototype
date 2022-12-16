#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <sciplot/sciplot.hpp>

using namespace sciplot;

template <typename Functor>
std::pair<double, double> GradientDescentIntercept(Functor functor1, double initIntercept = 0.0, double initSlope = 1.0)
{
    double learningRate = 0.01;
    long iterations = 100000l;
    std::valarray<double> intercept(initIntercept, 1);
    std::valarray<double> slope(initSlope,1);

    std::pair<std::valarray<double>, std::valarray<double>> grad = functor1(intercept, slope);

    long iterCount = 0;
    while (iterCount < iterations && (std::abs(grad.first[0]) >= 1e-6 && std::abs(grad.second[0]) >= 1e-6) )
    {
        std::cout << ++iterCount;
        std::cout << ": Intercept = " << intercept[0] << ", Slope = " << slope[0] << std::endl;
        grad = functor1(intercept, slope);
        std::cout<<"   gradient(intercept) = " << grad.first[0] << " gradient (second) = " << grad.second[0] <<std::endl;
        intercept = intercept - grad.first * learningRate;
        slope = slope - grad.second * learningRate;
    }
    return std::make_pair(intercept[0], slope[0]);
}
int main(void)
{
    std::map<double, double> heightWeight = {{0.5, 1.4}, {2.3, 1.9}, {2.9, 3.2}};
    auto residue = [](std::valarray<double> intercept, std::valarray<double> slope)
    {
        return (std::pow((1.4 - (intercept + slope * 0.5)), 2) + std::pow((1.9 - (intercept + slope * 2.3)), 2) + std::pow((3.2 - (intercept + slope * 2.9)), 2));
    };
    auto gradient = [](std::valarray<double> intercept, std::valarray<double> slope)
    {
        return std::make_pair((-2 * ((1.4 - (intercept + slope * 0.5)) + (1.9 - (intercept + slope * 2.3)) + (3.2 - (intercept + slope * 2.9)))), 
        (-2 * (0.5 * (1.4 - (intercept + slope * 0.5)) + 2.3 * (1.9 - (intercept + slope * 2.3)) + 2.9 * (3.2 - (intercept + slope * 2.9)))));
    };
    Vec x = linspace(0,3.2,100);
    
    std::pair<double, double> result = GradientDescentIntercept(gradient);
    std::cout << "Gradient descent intercept = " << result.first <<" slope = " << result.second ;
    auto line = [](double a, double b, std::valarray<double> x){
        return a*x+b;
    };
    Plot2D plot;
    plot.legend().atLeft();
    plot.drawCurve(x, line(result.second, result.first, x)).lineWidth(2).label("Best line of fit");
    Vec X = {0.5, 2.3, 2.9};
    Vec Y = {1.4, 1.9, 3.2};
    plot.drawPoints(X,Y).pointType(0).pointSize(12).label("Data points");
    Figure fig = {{plot}};
    Canvas canvas = {{fig}};
    canvas.show();
    return 0;
}