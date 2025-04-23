# Qt3D CanvasWidget – 3D Projection and Rasterizer (Software Rendering)

This C++/Qt project is a **minimal 3D rasterizer** implemented using `QPainter` in a `QWidget`. It projects 3D vertices onto a 2D screen using a custom projection matrix and simple matrix math — all without OpenGL.

## 🎯 Features

- Implements a full 3D-to-2D **perspective projection** pipeline using matrix math
- Projects vertices in **camera space** using a custom world-to-camera matrix
- Uses **QPainter** to draw vertex projections on a canvas widget
- Includes optional vertex rotation around the Z-axis using a transformation matrix
- Built using **Qt 5.7** (or higher)

## 🧱 How It Works

1. **Vertex Transformation**:
   - World → Camera via `worldToCamera` matrix
   - Camera → Clip → Raster using `Mproj` (projection matrix)

2. **Matrix Operations**:
   - Implemented via `multPointMatrix(...)` to transform vertex coordinates

3. **Drawing Logic**:
   - Vertices are projected to 2D raster space and drawn using `QPainter::drawPoint()`
   - Projected points are clamped to the canvas resolution

4. **Optional Rotation**:
   - Vertices can be rotated using a 3x3 rotation matrix (`RotM`)

## 📦 File Structure

- `canvaswidget.h/.cpp`: Main widget class with projection and rendering logic
- `vertexdata.h`: (if present) Contains vertex buffer and possibly index buffer
- `main.cpp`: Launches the Qt application

## 📐 Projection Matrix Details

The projection matrix `Mproj` is built manually:

```cpp
float scale = 1 / tan(angleOfView * 0.5 * M_PI / 180);
Mproj[0][0] = scale;
Mproj[1][1] = scale;
Mproj[2][2] = -far / (far - near);
Mproj[3][2] = -far * near / (far - near);
Mproj[2][3] = -1;
Mproj[3][3] = 0;
