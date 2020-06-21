#include <iostream>
#include <Eigen/Dense>
#include <armadillo>

#include <gla/matrix/dynamic_size.hpp>
#include <gla/backend/eigen/functional.hpp>
#include <gla/backend/armadillo/functional.hpp>
#include <gla/backend/eigen/matrix/dynamic_size.hpp>
#include <gla/backend/armadillo/matrix/dynamic_size.hpp>

/* namespace to eigen/armadillo matrix backend */
namespace eigen_backend = gla::backend::eigen::matrix;
namespace arma_backend = gla::backend::armadillo::matrix;

/* alias to eigen/armadillo functional tools */
using eigen_f = gla::backend::eigen::functional;
using arma_f = gla::backend::armadillo::functional;

/* helper macro for printing */
#define DESC(desc) { std::cout << desc << std::endl; }

int main()
{
    /* transpose in original eigen API */
    {
        Eigen::MatrixXf A(3,3);
        A << 1, 2, 1,
            2, 1, 0,
            -1, 1, 2;
        DESC("Here is the matrix A:");
        DESC(A);
        DESC("The transpose of A is:");
        DESC(A.transpose());
    }

    /* transpose in original armadillo API */
    {
        arma::mat A = {{1,2,1},{2,1,0},{-1,1,2}};
        auto B = A.t();
        DESC("Here is the matrix A:");
        DESC(A);
        DESC("The transpose of A is:");
        DESC(B);
    }
    
    /* unified API using gla */
    {
        {
            arma_backend::dynamic<float> A(3,3);
            A = {
                1, 2, 1,
                2, 1, 0,
                -1, 1, 2
            };
            auto B = arma_f::transpose(A);
            DESC("Here is the matrix A:");
            DESC(A);
            DESC("The transpose of A is:");
            DESC(B);
        }
        {
            eigen_backend::dynamic<float> A(3,3);
            A = {
                1, 2, 1,
                2, 1, 0,
                -1, 1, 2
            };
            auto B = eigen_f::transpose(A);
            DESC("Here is the matrix A:");
            DESC(A);
            DESC("The transpose of A is:");
            DESC(B);
        }
    }
}