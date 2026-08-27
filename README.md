# Falling Sand Simulation
A simple falling sand simulation written in C++ using [raylib](https://www.raylib.com/).

This project was inspired by [Jason McGhee's Falling Sand Simulation](https://jason.today/falling-sand) and was build as a small learning project to explore raylib and real-time rendering and C++.

## Building

### Requirements

- C++ compiler with C++17 support
- `make`
- `git`

### Build

Build the project:
```bash
make
```

Run the project:
```bash
make run
```

Clean generated build files:
```bash
make clean
```

## Controls

| Input | Action |
|---|---|
| `Left Mouse Button` | Place sand |
| `+` | Increase brush size |
| `-` | Decrease brush size |
| `C` | Toggle rainbow color mode |
| `R` | Reset simulation |
| `ESC` | Close application |