#define PROBLEM "https://yukicoder.me/problems/no/502"
//
#include "template/template.hpp"
//
#include "modint/montgomery-modint.hpp"
using mint = LazyMontgomeryModInt<1000000007>;
//
#include "modulo/factorial.hpp"
//
using namespace Nyaan;

void Nyaan::solve() {
  ini(n);
  if (n >= (int)mint::get_mod()) die(0);
  out(factorial<mint>(n));
}
