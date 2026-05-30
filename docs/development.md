# Development Guide

Codec Cipher is a CMake-based C++ project that currently depends only on the C++ standard library.

## Local Build Commands

From the repository root:

```bash
cmake -S . -B build
cmake --build build
```

Run the application after a successful build:

```bash
./build/codec_cipher
```

For multi-configuration generators such as Visual Studio, build a specific configuration and run the matching executable location:

```powershell
cmake -S . -B build
cmake --build build --config Debug
.\build\Debug\codec_cipher.exe
```

## Clean Build Commands

Remove generated build output and configure again:

```bash
rm -rf build
cmake -S . -B build
cmake --build build
```

On Windows PowerShell:

```powershell
Remove-Item -Recurse -Force build
cmake -S . -B build
cmake --build build --config Debug
```

## Expected CMake Workflow

1. Configure with `cmake -S . -B build`.
2. Build with `cmake --build build`.
3. Run the executable from the generated build directory.
4. Keep generated build files out of version control.
5. Update `CMakeLists.txt` when adding new source files.

The project should remain portable and dependency-free unless a dependency is explicitly justified.

## Directory Responsibilities

- `app/` contains the application entry point and command-line interaction wiring.
- `include/` contains project headers and class declarations.
- `src/` contains class implementations.
- `docs/` contains design notes, development guidance, and planning documents.
- `saves/` is the local persistence directory for generated object save files. The directory is preserved with `.gitkeep`, but generated saves are ignored.

## Adding a New Class Cleanly

1. Choose a focused class name that describes one responsibility.
2. Add the class declaration to `include/<ClassName>.h`.
3. Add the implementation to `src/<ClassName>.cpp`.
4. Include only the headers the class needs.
5. Prefer standard library types and algorithms before introducing new abstractions.
6. Add the new `.cpp` file to the executable source list in `CMakeLists.txt`.
7. Keep persistence, terminal UI, and object-model concerns separated when possible.
8. Build with CMake before submitting the change.
