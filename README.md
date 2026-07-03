# Wave Interference Simulator

An interactive 3D wave interference simulator built with C++ and SDL2. The program renders two interacting cosine waves dynamically on a 3D grid and calculates constructive and destructive interference patterns in real-time.

## 📺 Demo Video

Check out the simulation in action:
[<video src="github.com/Hayathorium/wave-interference-simulator/video-demo.mp4" width="600" controls>
</video>](https://github.com/Hayathorium/wave-interference-simulator/blob/main/video-demo.mp4)

*(Alternatively, you can access the video directly at: [https://www.youtube.com/watch?v=Z7DJ5KBYefY](https://www.youtube.com/watch?v=Z7DJ5KBYefY))*

---

## 🎮 Controls

Launch the simulator and use the following inputs to manipulate the environment:

| Input | Action |
| --- | --- |
| **`Arrow Keys`** | Move the currently selected wave source across the grid |
| **`R`** | Switch control between Wave 1 and Wave 2 |
| **`Mouse Scroll`** | Increase / Decrease the amplitude of the active wave |
| **`Hold Left Click + Drag`** | **Observation Mode:** Rotate the grid to view the 3D graph from different angles |
| **`Middle Click`** | Export the current graph data points into a `wave.csv` file |

---

## 🚀 Features

* **Real-Time Interference Calculation:** Computes the overlapping grid points dynamically using standard wave equations.
* **3D Vector Rotation:** Implements custom matrix-free `vec3` point rotation around a focal centroid.
* **Data Exporting:** Seamlessly dump simulated data coordinates into a `.csv` file format for further mathematical analysis in external tools (like MATLAB or Excel).

## 🛠️ Requirements & Compilation

To run this project locally, make sure you have an environment configured for C++ and **SDL2** (Simple DirectMedia Layer).

### Dependencies

* A C++11 (or higher) compliant compiler
* SDL2 Development Libraries

### Compilation Example (GCC/Clang)

```bash
g++ main.cpp screen.cpp -o wave_simulator -lSDL2
./wave_simulator

```

*(Ensure `screen.h` and `screen.cpp` are located in your working directory)*
