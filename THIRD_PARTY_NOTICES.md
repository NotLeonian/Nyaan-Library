# Third-party notices

## Library Checker random generator
This repository includes the following third-party source code:

- File: [`random_graph/random.hpp`](random_graph/random.hpp)
- Source: [`yosupo06/library-checker-problems/common/random.h`](https://github.com/yosupo06/library-checker-problems/blob/1e3da4fd4135f4f3cb3a6d76b51c827f7d987942/common/random.h)
- Project: [Library Checker Problems](https://github.com/yosupo06/library-checker-problems)
- Copyright: 2024 Kohei Morita
- License: Apache-2.0
- License text: [`LICENSES/Apache-2.0.txt`](LICENSES/Apache-2.0.txt)
- Changes:
  - Adapted as [`random_graph/random.hpp`](random_graph/random.hpp).
  - Moved `#pragma once` to the first line for oj-bundle compatibility.
  - Made the header self-contained by adding missing standard library
    includes: `<cstddef>`, `<string>`, `<utility>`, and `<vector>`.
  - Removed the unused `<random>` include.
  - changed uses of `size_t` to `std::size_t`.

The Apache-2.0 license text is included in [`LICENSES/Apache-2.0.txt`](LICENSES/Apache-2.0.txt).

## hitonanode/cplib-cpp rectangle add rectangle sum
This repository includes the following third-party source code:

- File: [`data-structure-2d/rectangle-add-rectangle-sum.hpp`](data-structure-2d/rectangle-add-rectangle-sum.hpp)
- Source: [`hitonanode/cplib-cpp/data_structure/rectangle_add_rectangle_sum.hpp`](https://github.com/hitonanode/cplib-cpp/blob/99e4d0494958b4176c449c28c80a985b12b6791b/data_structure/rectangle_add_rectangle_sum.hpp)
- Project: [`hitonanode/cplib-cpp`](https://github.com/hitonanode/cplib-cpp)
- Copyright: 2019 Ryotaro Sato
- License: MIT
- License text: [`LICENSES/MIT.txt`](LICENSES/MIT.txt)
- Changes:
  - Adapted as [`data-structure-2d/rectangle-add-rectangle-sum.hpp`](data-structure-2d/rectangle-add-rectangle-sum.hpp).
  - Made the header self-contained by adding missing standard library
    includes: `<algorithm>`, `<tuple>`, and `<utility>`.
  - Adjusted names and style to match this repository.

The MIT license text is included in [`LICENSES/MIT.txt`](LICENSES/MIT.txt).

## Twemoji favicon
This repository includes the following third-party asset:

- File: [`.verify-helper/docs/static/favicon.svg`](.verify-helper/docs/static/favicon.svg)
- Source: [Twemoji `assets/svg/1f4c4.svg` (Page Facing Up)](https://raw.githubusercontent.com/jdecked/twemoji/main/assets/svg/1f4c4.svg)
- Project: [Twemoji](https://github.com/twitter/twemoji)
- Copyright: 2014-2021 Twitter, 2022-present Jason Sofonia & Justine De Caires
- License: CC BY 4.0
- License text: [`LICENSES/CC-BY-4.0.txt`](LICENSES/CC-BY-4.0.txt)
- Changes: None

Twemoji graphics are licensed under CC BY 4.0.
