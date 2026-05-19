---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/verify-yuki/yuki-1323.test.cpp
    title: verify/verify-yuki/yuki-1323.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"shortest-path/bfs-restore.hpp\"\n\nvector<pair<int, int>>\
    \ bfs_restore(vector<vector<int>>& g, int st = 0) {\n  vector<pair<int, int>>\
    \ d(g.size(), make_pair(-1, -1));\n  d[st] = make_pair(0, -1);\n  queue<int> Q;\n\
    \  Q.push(st);\n  while (!Q.empty()) {\n    int cur = Q.front();\n    Q.pop();\n\
    \    int cd = d[cur].first;\n    for (auto&& dst : g[cur]) {\n      if (d[dst].first\
    \ == -1) {\n        d[dst].first = cd + 1;\n        d[dst].second = cur;\n   \
    \     Q.push(dst);\n      }\n    }\n  }\n  return d;\n}\n"
  code: "#pragma once\n\nvector<pair<int, int>> bfs_restore(vector<vector<int>>& g,\
    \ int st = 0) {\n  vector<pair<int, int>> d(g.size(), make_pair(-1, -1));\n  d[st]\
    \ = make_pair(0, -1);\n  queue<int> Q;\n  Q.push(st);\n  while (!Q.empty()) {\n\
    \    int cur = Q.front();\n    Q.pop();\n    int cd = d[cur].first;\n    for (auto&&\
    \ dst : g[cur]) {\n      if (d[dst].first == -1) {\n        d[dst].first = cd\
    \ + 1;\n        d[dst].second = cur;\n        Q.push(dst);\n      }\n    }\n \
    \ }\n  return d;\n}"
  dependsOn: []
  isVerificationFile: false
  path: shortest-path/bfs-restore.hpp
  requiredBy: []
  timestamp: '2026-05-19 18:11:32+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/verify-yuki/yuki-1323.test.cpp
documentation_of: shortest-path/bfs-restore.hpp
layout: document
redirect_from:
- /library/shortest-path/bfs-restore.hpp
- /library/shortest-path/bfs-restore.hpp.html
title: shortest-path/bfs-restore.hpp
---
