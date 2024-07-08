# Void Engine

Cross-platform composition-based OpenGL 4.6 game engine. This project is still a work in progress and is not yet fully functional.

## Building

This project uses Meson as its build system. To build the project, run the following commands:

```bash
meson setup build -Dglad:api=gl:core=4.6 -Dglfw:display-api=x11 --buildtype=debugoptimized
meson compile -C build
```
