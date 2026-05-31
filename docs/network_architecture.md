# Network Architecture

Codec Cipher is moving toward a nested dimensional network model. The project treats data as material that can become structure, then studies how repeated runs refine that structure over time. This document defines the main concepts at a planning level; it is intentionally conceptual rather than implementation-heavy.

## Node

A node is a point of meaning inside the network. A node may begin as a numeric value, a derived value, a label, or a structural marker. Nodes are the smallest named pieces that other structures can connect to, group, inspect, or preserve in a snapshot.

## Edge

An edge is a relationship between nodes or larger structures. Edges make the model a network instead of a loose collection of values. An edge may represent adjacency, transformation history, containment, sequence order, similarity, dependency, or another relationship discovered during experimentation.

## Cube

A cube is a coherent structural region of the network. At the simplest level, it can be imagined as a group of connected nodes with cube-like organization. A cube is not just a visual shape; it is a unit that can be inspected, refined, nested, saved, and compared across runs.

## Nested Cube

A nested cube is a cube that contains smaller cube structures or references to cube-like regions inside itself. Nesting lets the project model "cubes within cubes," where local structure exists inside broader structure. Nested cubes make sequence and context important because the meaning of an inner cube may depend on the outer cube that contains it and on the runs that created it.

## Network

A network is the full structure under study. It contains nodes, edges, cubes, nested cubes, run history, snapshots, and metadata. The network is the primary long-term subject of Codec Cipher experiments. Standalone dimensional objects may still be useful, but the roadmap now treats them as building blocks or views into a larger network.

## Run

A run is one execution of a transformation, analysis, refinement, import, or visualization step. A run has inputs and context, acts on the current network state, and produces changes or observations. Runs should be recorded because later interpretation may depend on the exact order and conditions that produced the structure.

## Run Sequence

A run sequence is an ordered set of runs. Repeated runs are expected to refine the network by adding edges, reorganizing cube regions, deepening nested cubes, or producing snapshots. The same data may lead to different structures if the run sequence changes, so sequence is a first-class part of the model.

## Snapshot

A snapshot is a saved view of the network at a specific point in a run sequence. Snapshots allow experiments to be compared, replayed, branched, or recovered. A snapshot may include structural data, metadata, run identifiers, and enough context to explain how that state was reached.

## Visualization

Visualization is the way humans inspect the network. Early visualization can be text-based, including tables, outlines, and ASCII cube diagrams. Later visualization may include SVG or graphical output. Visualization should help answer practical questions: what changed, where are cubes nested, which edges matter, and how difficult would recovery be with the available context?

## Recovery Difficulty

Recovery difficulty describes how hard it is to reconstruct data, structure, or meaning from the current artifacts. Difficulty may depend on nesting depth, edge density, missing snapshots, incomplete run history, altered run order, or unavailable context. Codec Cipher may eventually study reversible transformations, but it should remain clear that the project is not currently a finished encryption system.
