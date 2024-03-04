#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
using namespace std;
// Create a program that compares a parallel for loop and a standard for loop for summing rows of a View with Kokkos Timer.

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
    // Make View and create values
    int numRows = 100;
    int numCols = 100;
    Kokkos::View<double**> view("view", numRows, numCols);
    
    for (int i = 0; i < numRows; ++i) {
      for (int j = 0; j < numCols; ++j) {
        view(i, j) = i + j;
      }
    }
    
    // sum loops
    Kokkos::Timer timer;
    Kokkos::parallel_for("parallel_for", numRows, KOKKOS_LAMBDA(const int i) {
      int sum = 0;
      for (int j = 0; j < numCols; ++j) {
        sum += view(i, j);
      }
    });
    double parallelForTime = timer.seconds();
    
    timer.reset();
    for (int i = 0; i < numRows; ++i) {
      int sum = 0;
      for (int j = 0; j < numCols; ++j) {
        sum += view(i, j);
      }
    }
    double standardForTime = timer.seconds();
    
    // Output times
    cout << "Parallel For Time: " << parallelForTime << " seconds" << endl;
    cout << "Standard For Time: " << standardForTime << " seconds" << endl;
  }
  Kokkos::finalize();
}
