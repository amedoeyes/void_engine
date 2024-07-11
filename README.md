# Void Engine

Cross-platform composition-based OpenGL 4.6 game engine. This project is still a work in progress and is not yet fully functional.

## Features

- [Entity Component System](#entity-component-system)
- [Event Management](#event-management)

## Building

This project uses XMake as its build system. To build the project, simply run `xmake` in the root directory of the project.

## Entity Component System

To start using the ECS, you need to create a new `World` object. The `World` object is the main container for all entities and components.

```c++
using namespace void_engine::ecs;

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

## Event Management

First, create an `EventManager` object.

```c++
using namespace void_engine::event;

EventManager events;
```

#### Adding a listener

To add a listener to an event, use the `add_listener` method, and provide it with the event type as a template argument, and a lambda function that takes the event type as an argument.

```c++
events.add_listener<KeyDownEvent>([](const KeyDownEvent& event) {
    // Do something
});
```

#### Removing a listener

To remove a listener from an event, use the `remove_listener` method, and provide it the listener you want to remove.

```c++
auto* listener = events.add_listener<KeyDownEvent>([](const KeyDownEvent& event) {});
events.remove_listener(listener);
```

#### Emitting an event

To emit an event, use the `emit` method, and provide it with the event object.

```c++
events.emit(KeyboardKeyEvent{key, scancode, action, mods});
```

Or if the event does not have any data, you can use the `emit` method without any arguments, but you need to provide the event type as a template argument.

```c++
events.emit<WindowRefreshEvent>();
```

#### Remove Event

To remove an event from the event queue, use the `remove` method, and provide it with the event type as a template argument.

```c++
events.remove<KeyDownEvent>();
```

#### Polling events

To poll events, use the `poll` method.

```c++
events.poll();
```
