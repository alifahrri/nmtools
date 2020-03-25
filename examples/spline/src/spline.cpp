#include "nmtools/curvefit/spline.hpp"
#include <vector>
#include <iostream>

int main(int argc, char **argv)
{
    std::vector<double> t_data{
        0.0, 0.1, 0.2, 0.35, 0.5, 0.65, 0.8, 0.9, 1.0
    };
    std::vector<double> z_data{
        0.0, 0.2, 0.4, 0.7, 1.0, 0.4, 0.2, 0.2, 0.0
    };
    std::vector<double> y_data{
        0.0, 0.1, 0.2, 0.35, 0.5, 0.65, 0.8, 0.9, 1.0
    };
    std::vector<double> x_data{
        0.0, 0.125, 0.25, 0.4375, 0.625, 0.8125, 1.0, 1.0, 1.0
    };
    auto [e, f, g, r] = nmtools::curvefit::helper::tridiag(t_data, y_data);
    assert(
        std::size(e)==std::size(f) &&
        std::size(f)==std::size(g) &&
        std::size(g)==std::size(r)
    );
    auto x_results = nmtools::curvefit::cubic_spline(t_data, x_data, t_data);
    auto y_results = nmtools::curvefit::cubic_spline(t_data, y_data, t_data);
    auto z_results = nmtools::curvefit::cubic_spline(t_data, z_data, t_data);

    assert(std::size(x_results)==std::size(y_results));
    assert(std::size(x_results)==std::size(z_results));

    for (size_t i=0; i<std::size(x_results); i++)
        std::cout << x_results[i] << ", " << y_results[i] << ", " << z_results[i] << std::endl;
    return 0;
}