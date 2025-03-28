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
- **Manual Thread Configuration:** The number of threads can be set via a command-line argument.

## Requirements
- **C++17 or later**
- **OpenCV 4.x**
- **CMake**

## Installation & Compilation
1. **Clone the repository:**

```sh
git clone git@github.com:KiranSingh15/CAS_703_HIRO.git
cd CAS_703_HIRO 
```

2. **Build the project using CMake:**

```sh
mkdir build && cd build
cmake ..
make
```


## Usage
Run the compiled program, specifying the number of threads as an argument if you want to set it manually:

```sh
./imageProcessor <num_threads>
```

For example, to use 4 threads :
```sh 
./imagePrecessor 4
```

The processed images, as well as the `metrics.log` file will be saved in the `output/` directory.

## Troubleshooting
Ensure you have OpenCV installed on your system. You can install it using:

```sh
sudo apt-get install libopencv-dev  # Linux (Ubuntu/Debian)
brew install opencv                 # macOS (Homebrew)
```

Also make sure your images are in the `images/` folder and there are only images inside the folder.

## Project Structure
```
cpp/
│── include/
│   ├── imageOperations.hpp
│   ├── logs.hpp
│   ├── master.hpp
│   ├── taskQueue.hpp
│   ├── worker.hpp
│── src/
│   ├── imageOperations.cpp
│   ├── logs.cpp
│   ├── main.cpp
│   ├── master.cpp
│   ├── taskQueue.cpp
│   ├── worker.cpp
│── build/
│── images/
│── output/
│── README.md
│── CMakeLists.txt 
```

## License
Not sure we have one
