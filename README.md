Wrapper Template Library
========================

**Table of Contents**

- [Motivation](#design)
- [License](#license)

## Motivation

The C++ Standard Template Library forms the basis of modern C++ design, however, it mandates ownership of the underlying pointers. This can be costly for code that routinely interfaces with C APIs, requiring data copying to recreate C++ containers. The Wrapper Template Library therefore provides unowned, STL-like containers for types with contiguous representation in memory (vector, string).

## License

BSD-like or MIT, see [license](LICENSE.md).
