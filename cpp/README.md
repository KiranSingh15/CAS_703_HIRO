### Image Processing with OpenCV
## Overview
This project performs image processing operations using OpenCV, including:
- Converting an image to grayscale
- Applying a Gaussian filter
- Applying a Laplacian filter

## Features
- **Convert to Grayscale:** Converts an RGB image to grayscale.
- **Apply Gaussian Filter:** Smooths the image to reduce noise.
- **Apply Laplacian Filter:** Detects edges after Gaussian smoothing.
- **Execution Time Measurement:** Uses <chrono> to measure processing time.

## Requirements
- **C++17 or later**
- **OpenCV 4.x**
- **CMake**

## Installation & Compilation
1. **Clone the repository:**

```sh
git clone <repository_url>
cd ImageProcessingProject
```

2. **Build the project using CMake:**

```sh
mkdir build && cd build
cmake ..
make
```

## Usage
Run the compiled program:

```sh
./imageProcessor
```

The processed images will be saved in the `output/` directory.

## Troubleshooting
Ensure you have OpenCV installed on your system. You can install it using:

```sh
sudo apt-get install libopencv-dev  # Linux (Ubuntu/Debian)
brew install opencv                 # macOS (Homebrew)
```

## Compilation
Compile the project using `g++` and `pkg-config`:

```sh
g++ -c src/imageOperations.cpp -o imageOperations.o `pkg-config --cflags opencv4` --std=c++17
g++ -c src/main.cpp -o main.o `pkg-config --cflags opencv4` --std=c++17
g++ main.o imageOperations.o -o imageProcessor `pkg-config --libs opencv4`
```

Make sure to place the input image in the `images/` directory.

## Project Structure
```
project_root/
│── include/
│   ├── imageOperations.hpp
│── src/
│   ├── imageOperations.cpp
│   ├── main.cpp
│── images/
│── output/
│── README.md
│── Makefile
```

## Troubleshooting
If you encounter linking errors, ensure OpenCV is correctly installed and linked.

## License
Not sure we have one
