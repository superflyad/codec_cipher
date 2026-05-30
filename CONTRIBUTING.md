# Contributing to Codec Cipher

Thank you for helping improve Codec Cipher. The project is experimental and early-stage, so contributions should keep the foundation simple, readable, and dependency-free.

## Branch Naming

Use short, descriptive branch names with a category prefix:

- `chore/add-foundation-docs`
- `docs/update-roadmap`
- `feature/object-history`
- `fix/save-load-validation`

Preferred prefixes include `chore/`, `docs/`, `feature/`, `fix/`, `refactor/`, and `test/`.

## Commit Style

Use Conventional Commit-style messages:

```text
<type>: <short summary>
```

Examples:

- `chore: add repository foundation files`
- `docs: expand dimensional roadmap`
- `fix: validate empty save names`

Common types include `chore`, `docs`, `feature`, `fix`, `refactor`, and `test`.

## Build Before Submitting

Build the project from the repository root before opening a change request:

```bash
cmake -S . -B build
cmake --build build
```

If you need a clean build, remove the build directory first:

```bash
rm -rf build
cmake -S . -B build
cmake --build build
```

## Keep Changes Focused

Prefer small, focused changes that are easy to review. A change should usually address one concern: documentation, build configuration, persistence behavior, terminal UI, or one object-model concept.

Avoid mixing feature logic with formatting, documentation, or repository administration unless the connection is necessary and clearly explained.

## Dependency Policy

Do not add external dependencies without justification. Codec Cipher should prefer:

1. The C++ standard library.
2. Clear in-repository code.
3. External libraries only when they solve a specific problem that would be unreasonable to maintain locally.

Any dependency proposal should explain why it is needed, what alternatives were considered, and how it affects build portability.
