# Visualization Model

Codec Cipher's intended visualization model is "cubes within cubes": a nested dimensional network that can be inspected at multiple levels of detail. Visualization is a first-class part of the project because the structure is expected to become difficult to understand from raw values alone.

The first versions do not need rich graphics. Text output, outlines, and ASCII diagrams are acceptable and useful while the network model is still changing. SVG or graphical output can come later after the core concepts stabilize.

## Goals

- Show how data becomes structure.
- Show how repeated runs refine that structure.
- Show cubes, nested cubes, and relationships between cube regions.
- Show what changed between snapshots.
- Help reason about recovery difficulty by making sequence and context visible.

## Basic Cube View

A simple cube can be shown as a labeled region with nodes at corners or positions:

```text
Cube A

    n1 ------- n2
   /|          /|
 n3 ------- n4 |
 | |         | |
 | n5 ------|-n6
 |/         |/
 n7 ------- n8
```

This does not need to be geometrically perfect. The purpose is to make the structural grouping visible enough for inspection.

## Nested Cube View

A nested cube can be shown as an outer cube containing inner cube regions:

```text
Outer Cube A

+--------------------------------+
|                                |
|  Inner Cube A.1                |
|  +----------+                  |
|  | n1 -- n2 |                  |
|  | |     |  |                  |
|  | n3 -- n4 |                  |
|  +----------+                  |
|                                |
|  Inner Cube A.2                |
|  +----------+                  |
|  | n5 -- n6 |                  |
|  | |     |  |                  |
|  | n7 -- n8 |                  |
|  +----------+                  |
|                                |
+--------------------------------+
```

The inner cubes may represent refined regions created by later runs. Their meaning depends on both their internal nodes and their placement inside the outer cube.

## Network View

Cubes can also be connected to other cubes through edges, making the full model a network rather than a stack of isolated objects:

```text
[Cube A]
   |  refinement edge
   v
[Cube B] ---- similarity edge ---- [Cube C]
   |
   | contains
   v
[Cube B.1]
```

This style is useful when the important detail is relationship and sequence, not spatial projection.

## Run Sequence View

Repeated runs can be shown as a timeline of structural refinement:

```text
Run 001        Run 002             Run 003
input data --> Cube A ---------> Cube A
               8 nodes            8 nodes
               12 edges           18 edges
                                  contains Cube A.1
```

A later run may add edges, split a region, create an inner cube, or mark a snapshot. Visualization should make those changes visible.

## Snapshot Comparison

Snapshots can be compared with compact text summaries before graphical diffing exists:

```text
Snapshot S1
- cubes: 1
- nested cubes: 0
- edges: 12
- max depth: 1

Snapshot S2
- cubes: 2
- nested cubes: 1
- edges: 18
- max depth: 2
- change: Cube A gained Inner Cube A.1
```

## Path Toward Graphical Output

The project can begin with terminal output because ASCII views are easy to generate, inspect, and version in documentation. Once the network concepts are stable, the same model can support richer outputs such as:

- SVG diagrams for cube and network layouts.
- Layered views for nested cube depth.
- Timeline views for run sequences.
- Snapshot diff views.
- Recovery difficulty overlays that highlight missing context or high-complexity regions.
