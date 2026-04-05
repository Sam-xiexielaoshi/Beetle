# 🐞 Beetle Engine

![Beetle](/Branding/beetle.png?raw=true "Beetle")

A modern **C++ Game Engine** built from scratch while following the philosophy and learning approach of The Cherno's engine. This project is both an **educational journey** and a **practical implementation** of real-world engine architecture.

Beetle is currently in an **early development stage**, where core systems are being built step-by-step with a strong focus on understanding _why things are designed a certain way_, not just how to implement them.

---

## 🚀 Overview

**Beetle Engine** is a learning-focused game engine project designed to explore how real engines work under the hood.

Unlike using existing engines like Unity or Unreal, this project intentionally builds everything from the ground up. This includes designing systems such as event handling, application flow, logging, and eventually rendering and resource management.

The goal is not speed — but **deep understanding and clean architecture**.

---

## 🎯 Goals

The purpose of Beetle is two-fold:

1. To build a functional and scalable game engine
2. To deeply understand engine architecture and low-level systems

This project emphasizes:

- Writing **clean, maintainable C++ code**
- Understanding **engine design patterns**
- Learning **debugging and system-level thinking**
- Building systems that scale like real-world engines

---

## 🧱 Core Features

### ✅ Implemented

- Logging system (**spdlog**) for debug output and diagnostics
- Event system with type identification and category-based filtering
- Core application framework
- Multi-project setup using Premake

### 🔄 In Progress

- Layer system (stack-based architecture for handling updates/events)
- Input abstraction system

### 🔜 Planned

- OpenGL Rendering system
- ImGui integration for debugging UI
- Entity Component System (ECS)
- Physics system
- Asset and resource management

---

## 🧠 Engine Architecture

### 🔹 Event System

The event system is one of the foundational components of the engine. It is designed to be flexible, extensible, and efficient.

Each event consists of:

- **Event Type** → identifies the exact event (e.g., KeyPressed)
- **Event Category** → groups events using bitmasks (e.g., Input, Mouse)
- **Dispatcher** → routes events to appropriate handlers

This allows the engine to process events in a structured and scalable way.

```cpp
if (event.IsInCategory(EventCategoryKeyboard))
{
    // Handle keyboard input
}
```

---

### 🔹 Clean Include System

The project follows a clean include structure similar to production engines.

Instead of using relative paths, headers are included from a root directory:

```cpp
#include "Beetle/Core.h"
#include "Beetle/Events/Event.h"
```

This is enabled by configuring include directories:

```
$(ProjectDir)src
```

This approach improves scalability and keeps includes consistent across projects.

---

## 📁 Project Structure

```
Beetle/
├── Beetle/                    # Engine
│   ├── src/
│   │   └── Beetle/
│   │       ├── Core.h
│   │       ├── Events/
│   │       │   ├── Event.h
│   │       │   ├── KeyEvent.h
│   │       │   └── MouseEvent.h
│   │       ├── Application/
│   │       ├── Layer/
│   │       └── ...
│   └── vendor/               # Third-party libraries
│       └── spdlog/
│
├── Sandbox/                  # Client application (testing ground)
│   └── main.cpp
│
├── premake5.lua
└── README.md
```

The **Sandbox** project acts as a client application used to test and interact with the engine during development.

---

## ⚙️ Build Instructions

### 🔧 Requirements

- Visual Studio 2022
- Premake5

---

### 🛠️ Setup

```bash
git clone https://github.com/yourusername/beetle-engine.git
cd beetle-engine
premake5 vs2022
```

---

### ▶️ Build

- Open `Beetle.sln`
- Select configuration: **Debug / Release**
- Build the solution
- Run **Sandbox**

---

## 💡 Key Concepts Learned

This project explores several important concepts in modern C++ and engine development:

- Event-driven architecture
- Bitmasking using macros (`BIT(x)`)
- Virtual functions and polymorphism
- Friend classes for controlled access
- Multi-project build systems using Premake

---

## 🧪 Example Code

```cpp
class KeyPressedEvent : public Event
{
public:
    EVENT_CLASS_TYPE(KeyPressed)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
};
```

---

## 📌 Development Notes

- Distinction between **filters (virtual folders)** and real filesystem folders
- Use of include directories instead of relative paths
- Designed to scale into a full engine architecture

---

## 🤝 Contributing

This is primarily a personal learning project, but feedback and suggestions are always welcome.

Feel free to fork the repository and experiment with your own features.

---

## 👨‍💻 Author

**Samagra Singh**

---

## ⭐ Support

If you find this project interesting or helpful:

- ⭐ Star the repository
- 🍴 Fork it
- 🧠 Learn along with it

---

## 🪶 License

This project is licensed under the **MIT License**
