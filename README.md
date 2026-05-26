*This project has been created as part of the 42 curriculum by plepercq*

# So Long

[Subject](https://cdn.intra.42.fr/pdf/pdf/199959/en.subject.pdf)

## Description

`so_long` is a small 2D game built in C using the MiniLibX graphical library.
The player controls a character on a tile-based map, collecting all collectibles before reaching the exit. The project covers core graphics programming concepts: window management, texture rendering, event handling, and basic game logic.

**Rules:**
- Collect all `C` tiles on the map
- Reach the exit `E` to win
- Cannot move through walls `1`
- Movement count is displayed in the shell at every move

**Map tile legend:**

| Tile | Meaning |
|------|---------|
| `0`  | Ground |
| `1`  | Wall |
| `C`  | Collectible |
| `E`  | Exit |
| `P`  | Player starting position |

---

## Instructions

### Compilation

```bash
make
```

This will compile the project and produce the `so_long` executable.

### Usage

```bash
./so_long maps/<map_name>.ber
```

**Example:**
```bash
./so_long maps/map.ber
```

### Controls

| Key | Action |
|-----|--------|
| `W` / `↑` | Move up |
| `S` / `↓` | Move down |
| `A` / `←` | Move left |
| `D` / `→` | Move right |
| `ESC` | Quit the game |

### Map format

Maps must follow these rules:
- Extension must be `.ber`
- Must have a minimum size of 3x3
- Must be rectangular
- Must be fully enclosed by walls
- Must contain exactly 1 `P`, 1 `E`, and at least 1 `C`
- Must have a valid path from `P` to `E` and all `C` tiles

### Cleanup

```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Recompile from scratch
```

---

## Resources

### Documentation & References

- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)

### AI Usage

- **Debugging:** Used AI to understand error messages from GCC and Valgrind
- **Concepts:** Asked AI to explain MiniLibX functions
- **No code generation:** All code was written and understood by me personally
