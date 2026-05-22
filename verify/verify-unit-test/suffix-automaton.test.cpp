#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../../string/suffix-automaton.hpp"
#include "../../template/template.hpp"

using namespace Nyaan;

void test_multi_case_sorted_flag() {
  SuffixAutomaton<> a("a");
  SuffixAutomaton<> b("baa");

  assert(b.size() == 5);
  assert(b.find("b") != -1);
  assert(b.find("a") != -1);
  assert(b.find("ba") != -1);
  assert(b.find("aa") != -1);
  assert(b.find("baa") != -1);
  assert(b.find("ab") == -1);
}

void test_find_const() {
  const SuffixAutomaton<> sa("banana");

  assert(sa.find("ana") != -1);
  assert(sa.find("nana") != -1);
  assert(sa.find("banana") != -1);
  assert(sa.find("apple") == -1);
}

void test_multiple_build() {
  SuffixAutomaton<> sa;

  sa.build("a");
  assert(sa.size() == 2);
  assert(sa.find("a") != -1);
  assert(sa.find("b") == -1);

  sa.build("baa");
  assert(sa.size() == 5);
  assert(sa.find("baa") != -1);
  assert(sa.find("aa") != -1);
  assert(sa.find("aaa") == -1);
}

void Nyaan::solve() {
  test_multi_case_sorted_flag();
  test_find_const();
  test_multiple_build();

  cerr << "OK" << endl;

  int a, b;
  cin >> a >> b;
  cout << a + b << '\n';
}
