# Void Engine

Cross-platform composition-based OpenGL 4.6 game engine. This project is still a work in progress and is not yet fully functional.

## Features

- [Entity Component System](#entity-component-system)

## Building

This project uses XMake as its build system. To build the project, simply run `xmake` in the root directory of the project.

## Entity Component System

To start using the ECS, you need to create a new `World` object. The `World` object is the main container for all entities and components.

```c++
using namespace void_engine::ECS;

World world;
```

#### Create Entities

To create a new entity, use the `create` method.

```c++
Entity entity = world.create();
```

The `create` method can also take components to add to the entity, by providing the types of the components as template arguments.

```c++
Entity entity = world.create<Position, Velocity>();
```

Or by using brace initialization to set the initial values of the components.

```c++
Entity entity = world.create(Position{0, 0}, Velocity{1, 1});
```

#### Destroy Entities

To destroy an entity, use the `destroy` method, and provide it with the entity you want to destroy.

```c++
world.destroy(entity);
```

#### Attach components

To attach a component to an entity, use the `attach` method, and provide it with the entity and the components you want to attach as template arguments.

```c++
world.attach<Position, Velocity>(entity);
```

Or by using brace initialization to set the initial values of the components.

```c++
world.attach(entity, Position{0, 0}, Velocity{1, 1});
```

#### Fetch components

To fetch a component from an entity, use the `fetch` method, and provide it with the entity and the component type as a template argument.

```c++
Position& position = world.fetch<Position>(entity);
```

You can also use the `fetch` method to fetch multiple components, by providing it multiple component types. The `fetch` method will return a tuple of the components.

```c++
auto [position, velocity] = world.fetch<Position, Velocity>(entity);
```

#### Detach components

To detach a component from an entity, use the `detach` method, and provide it with the entity and the components you want to detach as template arguments.

```c++
world.detach<Position, Velocity>(entity);
```

#### Check if an entity has components

To check if an entity has components, use the `has` method, and provide it with the entity and the components you want to check as template arguments.

```c++
if (world.has<Position, Velocity>(entity)) {
    // Do something
}
```

#### Query entities

To query entities with specific components, use the `query` method, and provide it with the types of the components you want to query as template arguments.

```c++
for (Entity entity : world.query<Position, Velocity>()) {
    // Do something
}
```

You can also use the `query` method without any components to get all entities.
