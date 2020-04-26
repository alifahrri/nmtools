#include <iostream>
#include <Eigen/Dense>
#include <armadillo>

#include <gla/matrix/dynamic_size.hpp>
#include <gla/functional/backend/eigen.hpp>
#include <gla/functional/backend/armadillo.hpp>
#include <gla/matrix/backend/eigen/dynamic_size.hpp>
#include <gla/matrix/backend/armadillo/dynamic_size.hpp>

namespace eigen_backend = gla::matrix::backend::eigen;
namespace arma_backend = gla::matrix::backend::armadillo;

using eigen_f = gla::functional::backend::eigen::functional;
using arma_f = gla::functional::backend::armadillo::functional;

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
            gla::matrix::dynamic<arma_backend::dynamic,float> A(3,3);
            A.set_elements(test);
            auto B = arma_f::inverse(A);
            std::cout << "Here is the matrix A:\n" << A;
            std::cout << "The inverse of A is:\n" << B;
        }
        {
            gla::matrix::dynamic<eigen_backend::dynamic,float> A(3,3);
            A.set_elements(test);
            auto B = eigen_f::inverse(A);
            std::cout << "Here is the matrix A:\n" << A << std::endl;
            std::cout << "The inverse of A is:\n" << B << std::endl;
        }
    }
}