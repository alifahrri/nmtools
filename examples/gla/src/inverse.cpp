#include <iostream>
#include <Eigen/Dense>
#include <armadillo>

#include <gla/matrix/dynamic_size.hpp>
#include <gla/backend/eigen/functional.hpp>
#include <gla/backend/armadillo/functional.hpp>
#include <gla/backend/eigen/matrix/dynamic_size.hpp>
#include <gla/backend/armadillo/matrix/dynamic_size.hpp>

namespace eigen_backend = gla::backend::eigen::matrix;
namespace arma_backend = gla::backend::armadillo::matrix;

using eigen_f = gla::backend::eigen::functional;
using arma_f = gla::backend::armadillo::functional;

int main()
{
    {
        Eigen::MatrixXf A(3,3);
        A << 1, 2, 1,
            2, 1, 0,
            -1, 1, 2;
        std::cout << "Here is the matrix A:\n" << A << std::endl;
        std::cout << "The inverse of A is:\n" << A.inverse() << std::endl;
    }

    {
        arma::mat A = {{1,2,1},{2,1,0},{-1,1,2}};
        auto B = arma::inv(A);
        std::cout << "Here is the matrix A:\n" << A;
        std::cout << "The inverse of A is:\n" << B;
    }

    std::vector<float> test{
        1, 2, 1,
        2, 1, 0,
        -1, 1, 2
    };
    
    /* gla */
    {
        {
            arma_backend::dynamic<float> A(3,3);
            A.set_elements(test);
            auto B = arma_f::inverse(A);
            std::cout << "Here is the matrix A:\n" << A;
            std::cout << "The inverse of A is:\n" << B;
        }
        {
            eigen_backend::dynamic<float> A(3,3);
            A.set_elements(test);
            auto B = eigen_f::inverse(A);
            std::cout << "Here is the matrix A:\n" << A << std::endl;
            std::cout << "The inverse of A is:\n" << B << std::endl;
        }
    }
}