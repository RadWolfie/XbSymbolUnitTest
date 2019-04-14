# Xbox Symbol Unit Test

XbSymbolUnitTest is a console application, which has two options available.
1. Run by itself will perform XbSymbolDatabase's internal tests.
2. Give the path to xbe file in the argument to verify...
  * xbe does have full library compiled.
  * none of the existing OOVPA scan doesn't report false positive.

Designed for cross-platform support by using CMakeLists.txt project.

If there is an error, the console will not terminate until you press enter key.

# Windows
* Project Generator

  To generate project, we recommended to launch "__ Native Tools Command Prompt for VS ___" by Visual Studio. Then navigate to the project's folder to use `gen-wins-project.cmd` batch. Run the batch file for target platform options.

* Building Project

  Once project solution is generated, you can use `build-wins.cmd` batch file with target options to start building release build.

# Linux/Unix

TODO: Need instructions...
