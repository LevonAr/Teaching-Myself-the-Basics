# Rescale

Rescales a BMP image.

## Getting Started

### Prerequisites 

#### Get Compiler

This program is written in C, so you must compile it before you can run it.

In order to do this, you need a compiler. If you don't have one or don't know if you do, complete the following steps to install GCC:

#### For PC

##### Using Visual Studio Code (Recommended):

1. Open the '/Rescale' folder.

2. Install the C/C++ extension so we can compile the program.


##### Using Command Prompt:

1. Open Command Prompt and type
```
gcc -v
```
If gcc is installed then it should display a host of information starting with the sentence “Using built-in specs”

2. If you don't have gcc and are determined to run this in your Command Prompt, go to [this](https://preshing.com/20141108/how-to-install-the-latest-gcc-on-windows/ "Install GCC") link and follow the instructions to install gcc. However, the easier route would be to just use VScode.

#### For Mac:

Follow the installation instructions to [here](https://www.mkyong.com/mac/how-to-install-gcc-compiler-on-mac-os-x/ "Install GCC") to install GCC on your terminal.

## Compile program 

First we must compile the program by doing the following:

#### For PC:

##### Using Visual Studio Code

```
make rescale
```

##### Using Command Prompt

```
gcc -o rescale rescale.c
```

#### Using Mac Terminal
```
gcc -o rescale rescale.c
```

## Run Program

Run code by entering the following, where "ratio" is a number ( which can be a decimal ) that represent the size we want to increase/decrease the image by (eg. 2 doubles the image, .5 halves it):

#### For PC (both VScode and CMD prompt):

```
rescale <ratio> <input_file> <output_file>
```

#### For Mac:

```
./rescale <ratio> <input_file> <output_file>
```
