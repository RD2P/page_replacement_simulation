# Page Replacement Simulation

A small C++ simulator for an enhanced second-chance page replacement algorithm.
The simulation models virtual pages, physical frames, reference bits, and
modified (dirty) bits. Page references and read/write operations are generated
with a deterministic random seed (`42`).

## Requirements

- GNU Make
- A C++ compiler with C++11 support

## Build

Build the simulator with:

```sh
make
```

The executable is created at `build/bin/main`, and `make` also creates a
`main` symlink in the project root.

To remove build artifacts:

```sh
make clean
```

## Run

Run the simulator directly with:

```sh
./main <num_pages> <num_frames> <num_cycles>
```

For example:

```sh
./main 10 5 10
```

Show command-line help with:

```sh
./main --help
```

The short form `-h` is also supported. The simulator requires exactly three
integer positional arguments and rejects invalid values.

The arguments must satisfy:

- `num_pages > 0`: number of virtual pages
- `num_frames > 0`: number of physical frames
- `num_cycles >= 0`: number of simulated page references

The included script builds and runs the example configuration:

```sh
./scripts/run.sh
```

## Algorithm

Each frame stores:

- The page currently loaded in the frame
- A reference bit
- A modified bit indicating that the page has been written

When a referenced page is already resident, its reference bit is set. On a
page fault, an unused frame is filled until all frames are occupied. After
that, the replacement algorithm scans frames from a rotating clock-hand
position:

1. An unreferenced, unmodified page is selected immediately.
2. A referenced, modified page is written back conceptually by clearing its
	modified bit.
3. A referenced, unmodified page has its reference bit cleared.
4. An unreferenced, modified page is written back conceptually by clearing its
	modified bit.

The scan wraps around until an unreferenced, unmodified victim is found. The
program prints page faults, page references, victim selection, and conceptual
write-back operations as it runs.