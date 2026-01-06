# Flappy Bird (Feature-Complete Gameplay)

This branch represents the **feature-complete gameplay version** of the Flappy Bird clone built with **C++ and SFML**.

At this stage, **all core gameplay systems are fully implemented and stable**.  
The game is playable end-to-end using placeholder visuals (shapes instead of textures).

This branch is intentionally **frozen** and will not receive further gameplay changes.  
It exists as a reference implementation for debugging, learning, and comparison with future versions.

---

## 🎮 Current Game State

> **Gameplay: Feature-Complete**  
> **Visuals: Placeholder / Debug**

📸 ![Gameplay screenshot](debug_ver_pic.png)

---

## ✅ Implemented Features

- Game loop with delta time
- Player physics (gravity & jump)
- Procedural pipe generation
- Collision detection
- Score system (one point per pipe pair)
- Game-over state
- Restart functionality
- State machine (`PLAYING`, `GAME_OVER`)
- On-screen score rendering
- Game-over UI text

All gameplay logic is complete and functional.

---

## 🧠 Purpose of This Branch

This branch serves as a **stable gameplay milestone**:

- Reference for future refactors
- Debug-friendly version (no textures or assets)
- Learning checkpoint to revisit core systems
- Baseline for adding visuals, audio, and polish

Further development (textures, sprites, animations, sound, etc.) continues on the `main` branch.

---

## 🛠️ Controls

- **Space** — Jump
- **R** — Restart (after Game Over)
- **Close Window** — Exit game

---

## 🧱 Tech Stack

- **Language:** C++
- **Library:** SFML (Graphics, Window, System)

---

## 📌 Notes

- Visuals are intentionally simple to keep focus on gameplay logic.
- This branch will remain unchanged to preserve the feature-complete state.
- Future versions may diverge significantly in structure and presentation.

---

## 🚀 Next Steps (on `main` branch)

- Replace shapes with textures
- Add background and ground sprites
- Add sound effects
- Add animations and polish
- Possible refactor into a `Game` class

---

**Branch:** `feature-complete`  
**Status:** Gameplay complete, visuals pending
