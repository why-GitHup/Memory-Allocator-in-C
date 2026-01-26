# Project

Small C data-structures & memory allocator project.

## Overview

This repository implements several foundational data structures and a simple memory allocator in C. It contains implementations for a linked list, an AVL tree, and a custom memory allocator, plus a small test harness for exercising the code.

## Features

- Simple custom memory allocator implemented in [src/memAllo.c](src/memAllo.c) / [src/memAllo.h](src/memAllo.h).
- Singly/doubly linked list utilities in [src/LL.c](src/LL.c) / [src/LL.h](src/LL.h).
- AVL tree implementation in [src/avl.c](src/avl.c) / [src/avl.h](src/avl.h).
- Test program in [src/testDSA.c](src/testDSA.c) and a compiled helper binary in [bin/memAllo](bin/memAllo).

## Requirements

- A C compiler (GCC/Clang) and `make` are recommended.
- Docker (optional) to build and run in a container.

## Build

Prefer the provided `Makefile` if present:

```sh
make
```

This should compile the sources and place binaries in `bin/` (if configured).

Manual build example (adjust paths as needed):

```sh
gcc -o bin/memAllo src/memAllo.c src/LL.c src/avl.c src/testDSA.c -Isrc
```

To build with Docker:

```sh
docker build -t project-dsa .
```

## Run

Run the test harness or compiled binary:

```sh
./bin/memAllo
```

Or run the test program directly if not built into the binary:

```sh
./testDSA   # or ./bin/testDSA if built there
```

## File map

- [src/memAllo.c](src/memAllo.c) / [src/memAllo.h](src/memAllo.h): custom memory allocator implementation.
- [src/LL.c](src/LL.c) / [src/LL.h](src/LL.h): linked list utilities.
- [src/avl.c](src/avl.c) / [src/avl.h](src/avl.h): AVL tree implementation.
- [src/testDSA.c](src/testDSA.c): small test harness exercising the data structures.
- [bin/memAllo](bin/memAllo): compiled helper binary (if present).
- [Makefile](Makefile): build convenience.
- [Dockerfile](Dockerfile): optional container build.

## Testing

There are no formal unit tests included. Use the `testDSA` program to exercise functionality and validate behavior.

## Contributing

Contributions are welcome. Suggested workflow:

1. Fork the repository.
2. Create a topic branch for your change.
3. Add tests or small examples demonstrating the change.
4. Open a pull request describing the intent and impact.

## License

This repository does not include a license file. Add a `LICENSE` if you intend to make the code reusable under a specific license.

## Contact

If you have questions or want help running the project, open an issue or reach out to the repository maintainer.
