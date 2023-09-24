# WindowsAPIProject (Instructions from Chris Finch)

## Pre-requisites

- Visual Studio 2019 or later (CMake is bundled with Visual Studio)
- [vcpkg](https://github.com/microsoft/vcpkg) for package management

## Setup and Build

### Installing spdlog using vcpkg

To install `spdlog`, you can use [vcpkg](https://github.com/microsoft/vcpkg), a C++ package manager. If you haven't installed vcpkg, follow the [official installation instructions](https://github.com/microsoft/vcpkg#quick-start).

Once vcpkg is installed:

1. Open a terminal and navigate to your `vcpkg` installation directory.
2. Run the following command to install `spdlog`:

    ```bash
    ./vcpkg install spdlog
    ```

3. To integrate vcpkg with your Visual Studio environment, run:

    ```bash
    ./vcpkg integrate install
    ```

This will enable Visual Studio to automatically detect libraries installed via vcpkg, making it easier to manage your project dependencies.

### Building the Project with CMake and Visual Studio

1. Clone this repository to your local machine.
2. Open Visual Studio and go to `File > Open > CMake...` and select the `CMakeLists.txt` file in your cloned repository.
3. Select your build configuration (usually `Debug` or `Release`).
4. Build the project by going to `Build > Build All`.
5. To run the project, go to `Debug > Start Debugging`.


------


# Introduction
This repository contains a skeleton C++ project for an application with a GUI that runs on Windows. The application was written by one of the engineers at Mirada who would like support in taking the application further.

# Brief
This technical challenge consists of two tasks.

## Part 1: Review the code
Review the code in this repository, and provide feedback and suggestions for the developer. You may wish to do this in the form of comments on a pull request or feedback in an email.

We will be looking at your assessment and suggestions for the code, as well as how the feedback is communicated to the engineer. 

## Part 2: Expand the functionality
We would like you to add the following to the provided application:
- Logging to a log file.
- Functionality for user configuration of the size and position of the GUI window via a configuration file. The file should be created if it does not yet exist; it should be read on start of the program to set the initial window size and position; it should be updated with the final size and position of the Window before it is destroyed.
- Handling of various Windows messages to enforce minimum dimensions on the window and prevent any part of the window from being moved off-screen.

Assume that the entire project is editable. 

We will be looking for
- Awareness of crucial information for troubleshooting
- Consideration of the user experience
- Effective event handling and suitable error handling
- Clean and maintainable C++ code

# Getting started
- Please either fork or download a copy of this repository
- Visual Studio should be installed with the Desktop development with C++ workload. If you haven't already installed Visual Studio, go to https://visualstudio.microsoft.com/downloads/ to install Visual Studio Community for free. If you need to install the workload but already have Visual Studio, go to Tools > Get Tools and Features... to open the Visual Studio Installer, then choose Desktop development with C++ workload and Modify.
- Open the project in Visual Studio Community from its .vcxproj file.
- If prompted to target the latest Microsoft toolset, retarget the Windows SDK Version and platform toolset for the project.
- Click the left margin to set a breakpoint. Start the debugger by presssing F5 (Debug > Start Debugging) or the Start Debugging button (green triangle) in the Debug Toolbar.
- Put any assumptions, notes or instructions into your README.md. 
- When finished, provide us with a link to your repo or a zip of its contents 
- If choosing to provide written feedback, please put it in a text document in the repo 

We're eager to see you showcase your initiative and skills in your submission. Please get in touch if you need any help. Good luck with your test!