# Void Engine

Cross-platform composition-based OpenGL 4.6 game engine. This project is still a work in progress and is not yet fully functional.

## Features

- [Entity Component System](#entity-component-system)

## Building

This project uses Meson as its build system. To build the project, run the following commands:

```bash
meson setup build --buildtype=debugoptimized
meson compile -C build
```

## Entity Component System

To start using the ECS, you need to create a new `World` object. The `World` object is the main container for all entities and components.

```c++
World world;
```

#### Create Entities

To create a new entity, use the `create` method.

```c++
Entity entity = world.create();
```

The `create` method can also take components to add to the entity.

```c++
Entity entity = world.create<Position, Velocity>();
```

Or use brace initialization to set the initial values of the components.

```c++
Entity entity = world.create(Position{0, 0}, Velocity{1, 1});
```

#### Destroy Entities

To destroy an entity, use the `destroy` method.

```c++
world.destroy(entity);
```

#### Attach components

To attach a component to an entity, use the `attach` method.

```c++
world.attach<Position, Velocity>(entity);
```

Or use brace initialization to set the initial values of the components.

```c++
world.attach(entity, Position{0, 0}, Velocity{1, 1});
```

#### Fetch components

To fetch a component from an entity, use the `fetch` method.

```c++
Position& position = world.fetch<Position>(entity);
```

You can also use the `fetch` method to fetch multiple components.

```c++
auto [position, velocity] = world.fetch<Position, Velocity>(entity);
```

#### Detach components

To detach a component from an entity, use the `detach` method.

```c++
world.detach<Position, Velocity>(entity);
```

#### Check if an entity has components

To check if an entity has components, use the `has` method.

```c++
if (world.has<Position, Velocity>(entity)) {
    // Do something
}
```

#### Query entities

To query entities with specific components, use the `query` method.

```c++
for (Entity entity : world.query<Position, Velocity>()) {
    // Do something
}
```

You can also use the `query` method without any components to get all entities.
