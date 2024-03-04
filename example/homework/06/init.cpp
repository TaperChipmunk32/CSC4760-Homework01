#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
using namespace std;
// Create a program that does matrix addition between a 2D View and a 1D View with at least one loop of parallelism.
// For a test case:
// a = [130, 147, 115]   b = [221]
//     [224, 158, 187]       [12]
//     [ 54, 158, 120]       [157]
// Extra credit: make a function and check for correct shape/dimensions

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
    // Make View and add values
    Kokkos::View<int**> a("a", 3, 3);
    Kokkos::View<int*> b("b", 3);
    
    a(0, 0) = 130; a(0, 1) = 147; a(0, 2) = 115;
    a(1, 0) = 224; a(1, 1) = 158; a(1, 2) = 187;
    a(2, 0) = 54;  a(2, 1) = 158; a(2, 2) = 120;
    
    b(0) = 221;
    b(1) = 12;
    b(2) = 157;

    if(a.extent(0) != b.extent(0) || a.extent(1) != b.extent(0)){
      cout << "Error: dimensions do not match" << endl;
      return 1;
    }
  
    // Do a matrix add
    Kokkos::parallel_for("MatrixAdd", 3, KOKKOS_LAMBDA(int i) {
      Kokkos::parallel_for("MatrixAdd", 3, KOKKOS_LAMBDA(int j) {
      a(i, j) += b(j);
    });
    });
  
    // Output addition
    cout << "a = [" << a(0, 0) << " " << a(0, 1) << " " << a(0, 2) << endl;
    cout << a(1, 0) << " " << a(1, 1) << " " << a(1, 2) << endl;
    cout << a(2, 0) << " " << a(2, 1) << " " << a(2, 2) << "]" << endl;
  }
  Kokkos::finalize();
}
