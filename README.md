# Cub3D - Raycasting Engine

A Wolfenstein 3D-inspired raycasting engine built in C using MinilibX.

## 🎯 How Raycasting Works

### Basic Trigonometry Concepts

Raycasting uses simple trigonometry to convert angles into movement directions:

```
cos(angle) = horizontal movement (X)
sin(angle) = vertical movement (Y)
```

**Key Angles:**
- `0°` (East): `cos(0) = 1, sin(0) = 0` → Move right
- `90°` (South): `cos(90) = 0, sin(90) = 1` → Move down  
- `180°` (West): `cos(180) = -1, sin(180) = 0` → Move left
- `270°` (North): `cos(270) = 0, sin(270) = -1` → Move up

### DDA Algorithm Visualization

```
Ray casting from player to wall:

P = Player, # = Wall, . = Empty space

. . . # . .
. . . # . .
. P→→→# . .  ← Ray hits vertical wall
. . . # . .
. . . # . .
```

The DDA algorithm:
1. **Starts** at player position
2. **Jumps** from grid line to grid line (not every pixel!)
3. **Checks** if current grid square contains a wall
4. **Stops** when wall is found
5. **Returns** distance to that wall

### Distance to Height Conversion

The core formula for creating 3D perspective:

```c
wall_height = (SCREEN_HEIGHT * WALL_SCALE) / distance
```

**Examples:**
- Distance 1: `(1080 × 64) / 1 = 69,120` pixels (clipped to screen)
- Distance 2: `(1080 × 64) / 2 = 34,560` pixels
- Distance 4: `(1080 × 64) / 4 = 17,280` pixels

**Visual Result:**
```
Distance 1: ████████████████ (fills screen)
Distance 2: ████████████     (half height)  
Distance 4: ██████           (quarter height)
Distance 8: ███              (small wall)
```

### Field of View (FOV)

For each screen column (0 to 1919):
1. Calculate ray angle for that column
2. Cast ray using DDA
3. Convert distance to wall height
4. Draw vertical line

```
Screen columns:    Ray results:
 |  |  |  |  |      ████ ████ ████ ████
 0  1  2  3  4      ████ ████ ████ ████  
 ↓  ↓  ↓  ↓  ↓      ████ ████ ████ ████    
                    ████ ████ ████ ████
```

## 🚀 Implementation Steps

### 1. Basic DDA Function
```c
float dda_cast_ray(t_config *config, float ray_angle)
{
    // Convert angle to direction
    float ray_dir_x = cos(ray_angle);
    float ray_dir_y = sin(ray_angle);
    
    // DDA magic happens here...
    
    return distance_to_wall;
}
```

### 2. Render Loop
```c
for (int x = 0; x < SCREEN_WIDTH; x++)
{
    float ray_angle = calculate_ray_angle(x);
    float distance = dda_cast_ray(config, ray_angle);
    int wall_height = (SCREEN_HEIGHT * WALL_SCALE) / distance;
    draw_wall_column(x, wall_height);
}
```

## 📊 Project Structure

```
cub3d/
├── src/
│   ├── main.c              # Entry point
│   ├── parsing/            # Map and config parsing
│   │   ├── parse_file.c
│   │   ├── parse_map.c
│   │   └── validate_textures.c
│   ├── raycasting/         # Core 3D engine
│   │   └── raycasting.c
│   └── game/              # Game loop and rendering
│       └── game_loop.c
├── maps/                  # .cub map files
├── textures/             # Wall texture files
└── README.md
```

## 🎮 Controls

- **WASD**: Move player
- **Arrow Keys**: Rotate view
- **ESC**: Exit game

## 🔧 Building

```bash
make
./cub3d maps/map.cub
```

## 📚 Key Concepts Learned

1. **DDA Algorithm**: Efficient grid traversal
2. **Trigonometry**: Converting angles to directions
3. **Perspective Projection**: Distance → screen height
4. **Real-time Rendering**: 1920 rays per frame
5. **Memory Management**: Proper cleanup and validation

## 🎯 Features

- ✅ Complete .cub file parsing
- ✅ Map validation (walls, player position)  
- ✅ Texture loading and validation
- ✅ DDA raycasting implementation
- ✅ Perspective rendering
- ✅ Floor/ceiling colors
- 🔄 Wall texturing (in progress)
- 🔄 Player movement (in progress)

---

*This project recreates the classic Wolfenstein 3D raycasting technique, providing hands-on experience with 3D graphics programming fundamentals.*