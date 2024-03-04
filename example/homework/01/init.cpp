#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
using namespace std;
// Problem: Link and run program with Kokkos where you initialize a View and print out its name with the $.label()$ method.

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
    // Make View
    Kokkos::View<int*> view1("The View", 10);

    // Print name
    cout << "View name: " << view1.label() << endl;
  }
  Kokkos::finalize();
}