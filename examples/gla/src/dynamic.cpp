#include <iostream>
#include <Eigen/Dense>
#include <armadillo>

#include <gla/matrix/dynamic_size.hpp>
#include <gla/backend/eigen/matrix/dynamic_size.hpp>
#include <gla/backend/armadillo/matrix/dynamic_size.hpp>

using Eigen::MatrixXd;
using Eigen::Matrix2d;

namespace matrix = gla::matrix;
namespace eigen_backend = gla::backend::eigen::matrix;
namespace arma_backend = gla::backend::armadillo::matrix;

int main()
{
    std::cout << "creating 2x2 eigen matrix" << std::endl;
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;
    std::cout << "resizing eigen matrix to 3x3" << std::endl;
    m.resize(3,3);
    std::cout << m.cols() << "x" << m.rows() << std::endl;

    std::cout << "creating 2x2 armadillo matrix" << std::endl;
    arma::mat A(2,2);
    A(0,0) = 3;
    A(1,0) = 2.5;
    A(0,1) = -1;
    A(1,1) = A(1,0) + A(0,1);
    std::cout << A;
    std::cout << "resizing eigen matrix to 3x3" << std::endl;
    A.resize(3,3);
    std::cout << A.n_cols << "x" << A.n_rows << std::endl;

    std::vector<double> test{1.,2.,3.,4.};
    std::vector<double> test3{1.,2.,3.,4.,5.,6.,7.,8.,9.};

    std::cout << "creating 2x2 gla matrix with eigen backend" << std::endl;
    eigen_backend::dynamic<double> a(2,2);
    std::cout << a.n_rows() << "x" << a.n_cols() << std::endl;
    std::cout << a << std::endl;
    std::cout << "setting elements of 2x2 gla matrix with eigen backend" << std::endl;
    a.set_elements(test);
    std::cout << a << std::endl;
    std::cout << "resizing gla matrix with eigen backend to 3x3" << std::endl;
    a.resize(3,3);
    std::cout << "setting elements of 2x2 gla matrix with eigen backend" << std::endl;
    std::cout << a.n_rows() << "x" << a.n_cols() << std::endl;
    a.set_elements(test3);
    
    std::cout << "creating 2x2 gla matrix with armadillo backend" << std::endl;
    arma_backend::dynamic<double> b(2,2);
    std::cout << b.n_rows() << "x" << b.n_cols() << std::endl;
    std::cout << b;
    std::cout << "setting elements of 2x2 gla matrix with eigen backend" << std::endl;
    b.set_elements(test);
    std::cout << b;
    std::cout << "resizing gla matrix with armadillo backend to 3x3" << std::endl;
    b.resize(3,3);
    std::cout << b.n_rows() << "x" << b.n_cols() << std::endl;
    b.set_elements(test3);
}