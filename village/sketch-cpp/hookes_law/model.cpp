#include <iostream>
#include <vector>

double hookes_fit(std::vector<std::vector<double>>& data) {
    size_t N = data.size() + 1;
    double Σx, Σy, Σxy, Σx²;

    Σx = Σy = Σxy = Σx² = 0.0;

    for (auto datum : data) {
        double x = datum[0];
        double y = datum[1];
        
        Σx += x;
        Σy += y;
        Σxy += (x * y);
        Σx² += (x * x);
    }
    
    double xbar = Σx / N;
    double ybar = Σy / N;
    double k = (Σxy - (N * xbar * ybar)) / (Σx² - (N * xbar * xbar));
    // double b = ybar - (k * xbar);
    
    return k;
}

// 门槛不算高，但是极其折磨人
int main(int 参数数量, char* 参数小组[]) {
    printf("Hooke's Law Fit: %s\n", 参数小组[0]);

    std::vector<std::vector<double>> data = {
        { 20.0, 3.0 },
        { 40.0, 7.0 },
        { 60.0, 10.0 },
        { 80.0, 13.0 },
        { 100.0, 16.0 }
    };
    
    printf("k = %lf\n", hookes_fit(data));

    return 0;
}
