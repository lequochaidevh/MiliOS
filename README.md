# MiliOS

- HarisTinyOS ![Version](https://img.shields.io/badge/Version-v0.0.1-informational)
- Build tool ![Version](https://img.shields.io/badge/Version-v0.0.1-informational)

**MiliOS** is a lightweight, minimalist Real-Time Operating System (RTOS) skeleton designed for microcontrollers with extremely limited resources. It is specifically optimized for the **STM32** and **x86_64** simulation series, focusing on a tiny Flash ROM footprint.

---

## Project Goals

Built with a "Less is More" philosophy, MiliOS adheres to these core principles:

*  **Clean & Readable:** A codebase that is easy to audit and understand.
*  **Highly Reusable:** Modular architecture that can be ported to various small-scale projects.
*  **Resource Efficient:** Designed to run on MCUs with very little Flash and RAM.
*  **Low-Level Control:** Direct hardware interaction through low-layer libraries for maximum performance.
*  **C-Compatible C++:** Leveraging C++ structures while maintaining C-style linkage for seamless driver compatibility.

---

## Directory Structure

The project is organized to separate the core kernel logic from the hardware abstraction and user applications:

```text
MiliOS
├── HarisTinyOS                 # Main OS Workspace
│   ├── source                  # Source Code
│   │   ├── application         # User-level tasks and logic
│   │   ├── common              # Shared utilities and type definitions
│   │   ├── core                # Kernel engine (Scheduler, IPC, etc.)
│   │   ├── platform            # MCU-specific drivers (STM32F1)
│   │   ├── test                # Unit tests and simulation scenarios
│   │   └── CMakeLists.txt      # Build configuration
│   ├── build_and_run.sh        # Automation script for building and flashing
│   └── <build_artifacts>       # Compiled binaries and object files
├── reference                   # Datasheets and technical documentation
├── LICENSE                     # MIT License file
└── README.md                   # Project documentation
```

---

## 🚀 Getting Started

### Prerequisites
*   **Toolchain:** 
ARM: `arm-none-eabi-gcc`
LINUX simutaltion: `gcc & g++ (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0`

*   **Build System:** `CMake` (version 3.10+)
*   **Hardware:**:
STM32F1l series development board.
STM32F4 series development board.
x86_64 debug and simulation series development.

### Build Instructions
To compile the project, simply use the provided shell script:

```bash
cd HarisTinyOS
chmod +x build_and_run.sh
./build_and_run.sh
```

---

## Tech Stack

*   **Languages:** C (Core Logic), C++ (Structure & Compatibility).
*   **Hardware Abstraction:** STM32 LL (Low-Layer) Libraries.
*   **Build Tools:** CMake, GNU Arm Embedded Toolchain.

---

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. 
1. Fork the Project.
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`).
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the Branch (`git push origin feature/AmazingFeature`).
5. Open a Pull Request.

---

## License

Distributed under the **MIT License**. See `LICENSE` for more information.

---
*MiliOS is under active development. If you find this project useful, please consider giving it a ⭐!*