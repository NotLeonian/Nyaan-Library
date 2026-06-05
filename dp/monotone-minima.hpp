#pragma once

#include <functional>
#include <type_traits>
#include <vector>
using namespace std;

// NxN 行列がある
// m_i := argmin_j (A_{i,j}) が単調増加であるときに m_i を列挙する
// f(i, j, k) :
// A[i][j] と A[i][k] を比較 (j < k が保証されている)
// A[i][j] <= A[i][k] のとき true を返す関数を入れる (等号はどちらでもよい)
template <typename F>
auto monotone_minima(int N, int M, F&& f)
    -> enable_if_t<is_invocable_r_v<bool, F&, int, int, int>, vector<int>> {
  vector<int> res(N);
  auto dfs = [&](auto rc, int is, int ie, int l, int r) -> void {
    if (is == ie) return;
    int i = (is + ie) / 2;
    int m = l;
    for (int k = l + 1; k < r; k++) {
      if (!std::invoke(f, i, m, k)) m = k;
    }
    res[i] = m;
    rc(rc, is, i, l, m + 1);
    rc(rc, i + 1, ie, m, r);
  };
  dfs(dfs, 0, N, 0, M);
  return res;
}

// NxM 行列がある
// m_i := argmin_j (A_{i,j}) が単調増加であるときに m_i を列挙する
// A(i, j) : A[i][j] を返す関数
template <typename T, typename F>
auto monotone_minima(int N, int M, F&& A)
    -> enable_if_t<is_invocable_v<F&, int, int>, vector<int>> {
  auto f = [&](int i, int j, int k) -> bool {
    return std::invoke(A, i, j) <= std::invoke(A, i, k);
  };
  return monotone_minima(N, M, f);
}

template <typename F>
auto monotone_minima(int N, int M, F&& A)
    -> enable_if_t<!is_invocable_v<F&, int, int, int> &&
                       is_invocable_v<F&, int, int>,
                   vector<int>> {
  using T = invoke_result_t<F&, int, int>;
  return monotone_minima<T>(N, M, A);
}

/**
 * @brief monotone minima
 */
