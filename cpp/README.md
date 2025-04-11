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
- **Execution Time Measurement:** Uses `<chrono>` to measure processing time.
- **Manual Thread Configuration:** The number of threads can be set via a command-line argument.

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

## Requirements
- **C++17 or later**
- **OpenCV 4.x**
- **CMake**

## Installation & Compilation

1. **Clone the repository:**

```sh
git clone git@github.com:KiranSingh15/CAS_703_HIRO.git
cd CAS_703_HIRO/cpp
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

For example, to use 4 threads:

```sh
./imageProcessor 4
```

By default, when you specify a number of threads, the program will ask you to confirm your choice.  
To skip this confirmation and **force your thread count**, add the `--force` flag:

```sh
./imageProcessor 4 --force
```

> ⚠️ **Note:** When using `--force`, the execution summary at the end of the program is disabled. This flag is primarily intended for automated testing.

You can also choose **not to save the processed images** to the `output/` directory by adding the `--no-save` flag:

```sh
./imageProcessor --no-save
```

Both options can be combined:

```sh
./imageProcessor 4 --force --no-save
```

If no arguments are provided, the program will automatically choose the recommended number of threads based on your system:

```sh
./imageProcessor
```

The processed images (unless `--no-save` is used) and the `metrics.log` file will be saved in the `output/` directory.

## Run tests

You can run some tests to verify the functionality and view performance metrics:

```sh
mkdir build
cd build
cmake ..
make test
```

To generate the performance graph, two Python libraries are required: `pandas` and `matplotlib`.

If you don't have them installed, you can use the provided virtual environment (optional, mostly for macOS/Linux):

```sh
source venv/bin/activate  # macOS/Linux only (optional)
```

**Windows users:**  
Instead of using `source`, activate the virtual environment with:

```sh
venv\Scripts\activate
```

The graph will be saved in the `build/` directory.

## Troubleshooting

Ensure you have OpenCV installed on your system. You can install it using:

```sh
sudo apt-get install libopencv-dev  # Linux (Ubuntu/Debian)
brew install opencv                 # macOS (Homebrew)
```

Also, make sure your images are in the `images/` folder and that there's only one image inside the folder.

## License
This code belongs to Raphaël Boutaine, Fred Kehang Chang, Eric Deng, Kiran Singh.
However, it may be freely used by Dr. Khedri for future classes, demonstrations, or experimentation.
