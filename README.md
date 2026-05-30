# Codec Cipher

Codec Cipher is an experimental, early-stage C++ dimensional laboratory for representing numeric data as geometric and hyperdimensional structures. It is a persistent sandbox where named numeric objects can be created, classified, inspected, saved, and loaded for continued experimentation.

## Project Status

**Experimental / early-stage.**

Codec Cipher is not an encryption system today. The current repository focuses on project structure, terminal interaction, object classification, and simple persistence so future research can build on a readable foundation.

## Core Concept

Codec Cipher is a persistent dimensional laboratory where numeric data can be represented as geometric and hyperdimensional structures.

A collection of numeric values is treated as a dimensional object. The number of values determines whether the object currently behaves like a square, cube, hyperdimensional object, or unstable object. Saved objects can be restored later so experiments can continue across sessions.

## Current Capabilities

- Create named dimensional objects from numeric values.
- Classify objects as square, cube, hyperdimensional, or unstable based on value count.
- Inspect object metadata, values, and binary vertex labels in a terminal UI.
- Save objects to the local `saves/` directory.
- Load saved objects back into the laboratory.
- List objects known during the current session.

## Planned Capabilities

- Mutation system for controlled object changes.
- Object state comparison and history tracking.
- Experiment logs for persistent research notes.
- Richer terminal interface for navigating objects and experiments.
- Projection tools for higher-dimensional structures.
- Stability scoring for dimensional objects.
- Reversible transformations as a long-term goal.
- Encoding, decoding, and early cipher research built on reversible dimensional experiments.

## Build Instructions

Codec Cipher uses CMake and the C++ standard library only.

```bash
cmake -S . -B build
cmake --build build
```

## Run Instructions

After building, run the executable from the repository root:

```bash
./build/codec_cipher
```

On Windows with a Visual Studio generator, the executable may be under a configuration folder such as:

```powershell
.\build\Debug\codec_cipher.exe
```

The terminal menu supports:

1. Create Object
2. Inspect Current Object
3. Save Current Object
4. Load Object
5. List Objects
6. Exit

Saved objects are written to `saves/` as `.ccobj` files. Generated save files are ignored by Git, while `saves/.gitkeep` preserves the directory.

## Repository Layout

```text
codec_cipher/
├── app/                  # Application entry point and terminal menu wiring
├── include/              # Public project headers
├── src/                  # Class implementations
├── docs/                 # Project documentation and planning notes
├── saves/                # Local generated object saves; only .gitkeep is tracked
├── CMakeLists.txt        # CMake build definition
├── CONTRIBUTING.md       # Contribution guidelines
├── LICENSE               # MIT License
└── README.md             # Project overview
```

## Development Principles

- **No external dependencies unless justified.** New dependencies should solve a clear problem that the standard library cannot reasonably solve.
- **C++ standard library first.** Prefer standard containers, algorithms, filesystem utilities, and language features before introducing third-party code.
- **Readable architecture.** Keep classes focused, names descriptive, and control flow understandable for future experimenters.
- **Persistent experimentation.** Design features so object state, experiments, and research artifacts can eventually survive across sessions.
- **Reversible transformations are a long-term goal.** Mutation, encoding, and cipher research should preserve a path toward traceable and reversible operations.

## Object Classifications

Classification is based on the number of numeric values in an object:

| Value count | Classification |
| --- | --- |
| 4 | Square |
| 8 | Cube |
| 16, 32, 64, ... | Hyperdimensional Object |
| Any non-matching count | Unstable Object |

Examples:

- `1 2 3 4` creates a `Square`.
- `1 2 3 4 5 6 7 8` creates a `Cube`.
- Sixteen values create a `Hyperdimensional Object`.
- `1 2 3 4 5` creates an `Unstable Object`.
