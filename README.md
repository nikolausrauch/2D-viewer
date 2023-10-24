# 2D Viewer

This repository contains a small viewer library (C++ and OpenGL2) encapsulating window, and input handling, primitive, and graphical user interface (ImGui/ImPlot) rendering.   
I wrote it originally for visualizing physically based simulation approaches (mass-spring systems, rigid-bodies, SPH, etc.).
Over the years it has been used for teaching purposes, e.g. practical assignments, at my university.

It has the following in-source external dependencies: **glfw, glm, imgui, implot, stb_image**.

## Minimal Example

The **Viewer class** provides the interface to configure window/render behaviour and to register callbacks for the following events:
- **init**: is called after the opengl context is initialized
- **shutdown**: is called right before the opengl context is destroyed
- **key**: triggered if a key is pressed or released
- **mouseButton**: triggered if a mouse button is pressed or released
- **update**: called before rendering (once per frame)
- **draw**: used to submit render calls (points, lines, quads, triangles, circles, ...)
- **gui**: used to draw/respond to user-interface via ImGui and ImPlot

```cpp
    Viewer viewer;
    viewer.mWindow.title = "Example";
    viewer.mWindow.width = 1280;
    viewer.mWindow.height = 720;
    viewer.mWindow.vsync = true;
    viewer.mWindow.mHDPI = false;

    /* install callback functions for events */
    viewer.onUpdate([](Window& window, double dt){ });
    viewer.onDraw([](Window& window, double dt){ });
    viewer.onGui([](Window& window, double dt){ });
    viewer.onMouseButton([](Window& window, Mouse& mouse, int button, int mod, bool press){ });
    viewer.onKey([](Window& window, Keyboard& keyboard, int key, int mod, bool press){ });
 
    /* start viewer (OpenGL context is created, use drawcommands and loading functions only in callbacks) */
    viewer.run();
```

See **demo/demo.cpp** for a detailed overview of the libraries functionalities. 

## Examples

Assignments for a physically-based simulation course (mass-spring systems, rigid-body simulation, stable fluid, finite element method).
![viewer_examples](https://github.com/nikolausrauch/2d_viewer/assets/13553309/8b0d8fe7-20cf-4016-8a98-259ebae130c4)

