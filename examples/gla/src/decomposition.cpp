#include <iostream>
#include <Eigen/Dense>
#include <armadillo>

#include <gla/matrix/dynamic_size.hpp>
#include <gla/backend/eigen/functional.hpp>
#include <gla/backend/armadillo/functional.hpp>
#include <gla/backend/eigen/matrix/dynamic_size.hpp>
#include <gla/backend/armadillo/matrix/dynamic_size.hpp>

namespace matrix = gla::matrix;
namespace eigen_backend = gla::backend::eigen::matrix;
namespace arma_backend = gla::backend::armadillo::matrix;

using eigen_f = gla::backend::eigen::functional;
using arma_f = gla::backend::armadillo::functional;

int main()
{
    /** eigen **/

    std::cout << "-------- eigen examples ---------" << std::endl;
    {
        typedef Eigen::Matrix<double, 5, 3> Matrix5x3;
        typedef Eigen::Matrix<double, 5, 5> Matrix5x5;

        Matrix5x3 m = Matrix5x3::Random();
        std::cout << "Here is the matrix m:" << std::endl << m << std::endl;
        Eigen::FullPivLU<Matrix5x3> lu(m);
        std::cout << "Here is, up to permutations, its LU decomposition matrix:"
            << std::endl << lu.matrixLU() << std::endl;
        std::cout << "Here is the L part:" << std::endl;
        Matrix5x5 l = Matrix5x5::Identity();
        l.block<5,3>(0,0).triangularView<Eigen::StrictlyLower>() = lu.matrixLU();
        std::cout << l << std::endl;
        std::cout << "Here is the U part:" << std::endl;
        Matrix5x3 u = lu.matrixLU().triangularView<Eigen::Upper>();
        std::cout << u << std::endl;
        std::cout << "Let us now reconstruct the original matrix m:" << std::endl;
        std::cout << lu.permutationP().inverse() * l * u * lu.permutationQ().inverse() << std::endl;
    }
    {
        Eigen::MatrixXd m = Eigen::MatrixXd::Random(5,3);
        std::cout << "Here is the matrix m:" << std::endl << m << std::endl;
        Eigen::FullPivLU<Eigen::MatrixXd> lu(m);
        std::cout << "Here is, up to permutations, its LU decomposition matrix:"
            << std::endl << lu.matrixLU() << std::endl;
        std::cout << "Here is the L part:" << std::endl;
        Eigen::MatrixXd l = Eigen::MatrixXd::Identity(5,5);
        l.block(0,0,5,3).triangularView<Eigen::StrictlyLower>() = lu.matrixLU();
        std::cout << l << std::endl;
        std::cout << "Here is the U part:" << std::endl;
        Eigen::MatrixXd u = lu.matrixLU().triangularView<Eigen::Upper>();
        std::cout << u << std::endl;
        std::cout << "Let us now reconstruct the original matrix m:" << std::endl;
        std::cout << lu.permutationP().inverse() * l * u * lu.permutationQ().inverse() << std::endl;
    }
    std::cout << "------ eigen examples end -------" << std::endl;

    /** armadillo **/
    std::cout << "-------- armadillo examples ---------" << std::endl;
    {
        arma::mat A = arma::randu<arma::mat>(5,5);
        arma::mat L, U, P;
        arma::lu(L, U, P, A);
        arma::mat B = P.t()*L*U;
        std::cout << "Here is the matrix m:" << std::endl;
        std::cout << A;
        std::cout << "Here is the L part:" << std::endl;
        std::cout << L;
        std::cout << "Here is the U part:" << std::endl;
        std::cout << U;
        std::cout << "Let us now reconstruct the original matrix m:" << std::endl;
        std::cout << B;
    }
    std::cout << "------ armadillo examples end -------" << std::endl;

    std::vector<double> test{1.,2.,3.,4.};

    std::cout << "-------- gla examples ---------" << std::endl;
    /** gla **/
    {
        std::cout << "creating 2x2 gla matrix with eigen backend" << std::endl;
        eigen_backend::dynamic<double> a(2,2);
        std::cout << "setting elements of 2x2 gla matrix with eigen backend" << std::endl;
        a.set_elements(test);
        std::cout << a << std::endl;

        {
            auto [l, u] = eigen_f::lu_decomposition(a);
            std::cout << l << std::endl;
            std::cout << u << std::endl;
        }

        std::cout << "creating 2x2 gla matrix with armadillo backend" << std::endl;
        arma_backend::dynamic<double> b(2,2);
        std::cout << "setting elements of 2x2 gla matrix with eigen backend" << std::endl;
        b.set_elements(test);
        std::cout << b;

        {
            auto [l, u] = arma_f::lu_decomposition(b);
            std::cout << l << std::endl;
            std::cout << u << std::endl;
        }
    }
    std::cout << "------ gla examples end -------" << std::endl;
}