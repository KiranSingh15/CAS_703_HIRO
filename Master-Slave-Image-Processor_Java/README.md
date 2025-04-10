### Image Processing with Java 
## Overview
This project performs image processing operations using java native functions for convolution, including:
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
- **Java17 or later**
- **Maven3.8.1 or later**


## Installation & Compilation
1. **Clone the repository:**

```sh
git clone git@github.com:KiranSingh15/CAS_703_HIRO.git
cd CAS_703_HIRO/Master-Slave-Image-Processor_Java 
```

2. **Run the main program**

```sh
java -cp target/classes MasterProcess
```


## Usage
Run the compiled program, specifying the number of threads in MasterProcess class
Set numberOfThreads to targeted num_threads

For example, to use 4 threads :
```sh 
int numberOfThreads = 4;
```

The processed images, as well as the `metrics.log` file will be saved in the `output/` directory.

## Troubleshooting
Ensure you have OpenCV installed on your system. You can install it using:


Also make sure your images are in the `src/main/java/assets/` folder and there are only images inside the folder.

## Project Structure
```
.
├── README.md
├── output
│   ├── laplacian_image2025-03-24 18:15:54_1367.jpg
│   ├── laplacian_image2025-03-24 18:15:54_7838.jpg
│   └── laplacian_image2025-03-24 18:15:55_1912.jpg
├── pom.xml
├── src
│   ├── main
│   │   ├── java
│   │   │   ├── GaussianBlur.java
│   │   │   ├── GrayScale.java
│   │   │   ├── ImageProcessing.java
│   │   │   ├── LaplacianFilter.java
│   │   │   ├── LogEntry.java
│   │   │   ├── MasterProcess.java
│   │   │   ├── MetricsLogger.java
│   │   │   └── assets
│   │   │       ├── imglarge.png
│   │   │       ├── imglarge_1.png
│   │   │       ├── imglarge_2.png
│   │   │       ├── imglarge_3.png
│   │   │       ├── imglarge_4.png
│   │   │       ├── imgmid.jpg
│   │   │       ├── imgmid_1.jpg
│   │   │       ├── imgmid_2.jpg
│   │   │       ├── imgmid_3.jpg
│   │   │       ├── imgmid_4.jpg
│   │   │       ├── imgsmall.jpg
│   │   │       ├── imgsmall_1.jpg
│   │   │       ├── imgsmall_2.jpg
│   │   │       ├── imgsmall_3.jpg
│   │   │       ├── imgsmall_4.jpg
│   │   │       ├── input2.png
│   │   │       ├── input3.png
│   │   │       └── input4.jpg
│   │   └── resources
│   └── test
│       └── java
└── target
    ├── classes
    │   ├── GaussianBlur.class
    │   ├── GrayScale.class
    │   ├── ImageProcessing.class
    │   ├── LaplacianFilter.class
    │   └── MasterProcess.class
    └── generated-sources
        └── annotations
```

## License
Not sure we have one
