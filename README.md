
# Real-Time Video Processor (OpenCV)

A high-performance C++ application designed for real-time video manipulation. This project uses the OpenCV library to process video frames, allowing for dynamic adjustments to visual properties through an interactive interface.

## Technical Features

* **C++ Core**: Optimized for low-latency frame processing.
* **HSV Color Manipulation**: Advanced color space conversion for precise saturation and value control.
* **Dynamic UI**: Integrated OpenCV trackbars for real-time parameter tuning.
* **Build System**: Managed via **CMake** for efficient compilation and dependency linking.

## Prerequisites

Before running this project, ensure you have the following installed:

* **OpenCV** (C++ version)
* **CMake**
* **G++ Compiler** (supporting C++11 or higher)

## Build and Execution

To run the program, follow these steps in your terminal:

1. **Navigate to the Build Directory**:
```bash
cd build

```


2. **Compile the Project**:
```bash
make

```


3. **Run the Application**:
```bash
./VideoPlayer

```


4. **Load a Video**:
When the program starts, it will ask for a video file path.
* To test quickly: Copy and paste the path for `test.mp4` (which is located inside the build folder).
* Alternatively: Enter the full path to any other `.mp4` file on your system.



## Controls

* **Trackbars**: Use the sliders on the window to adjust the brightness and color levels in real-time.
* **Exit**: Press the `ESC` key or `q` to close the application and stop processing.
