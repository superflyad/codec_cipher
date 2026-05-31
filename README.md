# Codec Cipher

Codec Cipher is an experimental, early-stage C++ dimensional laboratory for exploring how data can become structure, structure can become geometry, and geometry can evolve through deterministic runs. Its v2 direction is nested cube networks: networks of nodes and relationships that form cubes, grow into cubes within cubes, and preserve the sequence that created them.

## Project Status

**Experimental / early-stage.**

Codec Cipher is not an encryption system today. The current repository includes the original terminal dimensional-object sandbox plus v2 core library systems for networks, cubes, nested cube hierarchies, deterministic runs, refinement, visualization, persistence, experiment comparison, and complexity research.

## Core Concept

Codec Cipher is a persistent nested dimensional network laboratory where data becomes structure. Numeric input can begin as simple values or dimensional objects, but the project direction is to let repeated runs refine those values into a connected network of nodes, edges, cubes, and cubes within cubes.

Each run should add context: what was processed, what changed, how cube regions were refined, and how the resulting structure relates to earlier snapshots. Over time, the same experiment may deepen into nested cube networks whose meaning depends on sequence and surrounding context, not only on the final visible shape.

Recovery is therefore a research question. Reconstructing data, structure, or meaning may depend on run order, saved snapshots, available metadata, and the context that created each nested region. Codec Cipher is a sandbox for exploring these ideas; it is not a finished encryption system.

The current terminal implementation still treats a collection of numeric values as a dimensional object. The number of values determines whether the object currently behaves like a square, cube, hyperdimensional object, or unstable object. Saved objects can be restored later so experiments can continue across sessions.

## Current Capabilities

Core library:

- Create networks from nodes, edges, relationships, and traversal utilities.
- Generate cube primitives with 8 vertices, 12 edges, inspection helpers, and metrics.
- Build nested cube hierarchies with parent-child relationships, depth tracking, and recursive traversal.
- Record deterministic runs with snapshots, history, and replay.
- Apply node, edge, cube, nested cube, and topology refinement operations.
- Render ASCII network, nested cube, and run timeline views, plus an SVG network export prototype.
- Serialize and deserialize networks, snapshots, and replayable run sequences.
- Manage experiment sessions, notes, comparisons, complexity metrics, and recovery difficulty estimates.

Terminal application:

- Create named dimensional objects from numeric values.
- Classify objects as square, cube, hyperdimensional, or unstable based on value count.
- Inspect object metadata, values, and binary vertex labels in a terminal UI.
- Save objects to the local `saves/` directory.
- Load saved objects back into the laboratory.
- List objects known during the current session.

## Continuing Work

- Expose the v2 core systems through richer terminal workflows.
- Expand visualization beyond the current ASCII and SVG prototypes.
- Harden persistence formats as experiments become more complex.
- Refine complexity and recovery difficulty metrics through research sessions.
- Explore reversible transformations as a long-term research goal.
- Build encoding, decoding, and early cipher research on traceable dimensional network experiments.

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
- **Run history matters.** Refinement, replay, encoding, and cipher research should preserve the sequence that produced a structure, not only the final form.

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
