# Codec Cipher

Codec Cipher is a persistent dimensional laboratory for representing information as geometric structures. It is a CMake-based C++ sandbox where numeric data can become named dimensional objects that are classified, inspected, saved, and loaded over time.

Codec Cipher is not an encryption system today. The foundation is designed to support future experiments with object mutation, object evolution, dimensional transformations, visualization, reversible transformations, and encryption research.

## Project Structure

```text
codec_cipher/
├── app/
│   └── main.cpp
├── include/
│   ├── DimensionalObject.h
│   ├── Laboratory.h
│   ├── Persistence.h
│   └── TerminalView.h
├── src/
│   ├── DimensionalObject.cpp
│   ├── Laboratory.cpp
│   ├── Persistence.cpp
│   └── TerminalView.cpp
├── saves/
├── docs/
│   └── vision.md
├── README.md
└── CMakeLists.txt
```

## Build Instructions

```bash
cmake -S . -B build
cmake --build build
```

## Run Instructions

```bash
./build/codec_cipher
```

The terminal menu supports:

1. Create Object
2. Inspect Current Object
3. Save Current Object
4. Load Object
5. List Objects
6. Exit

Saved objects are written to the `saves/` directory as `.ccobj` files. The directory is created automatically when the persistence layer is initialized.

## Example Object Classifications

Classification is based on the number of numeric values in an object:

| Value count | Classification |
| --- | --- |
| 4 | Square |
| 8 | Cube |
| 16, 32, 64, ... | Hyperdimensional Object |
| Any non-matching count | Unstable Object |

For example:

- `1 2 3 4` creates a `Square`.
- `1 2 3 4 5 6 7 8` creates a `Cube`.
- `1 2 3 ... 16` creates a `Hyperdimensional Object`.
- `1 2 3 4 5` creates an `Unstable Object`.
