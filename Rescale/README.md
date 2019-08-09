# Resize

Resizes a BMP image

## Getting Started

### Prerequisites 

This program is written in C, so you must compile it before you can run it.

In order to do this, you need a compiler. If you don't have one or don't know if you do, complete the following steps:

For PC:

1. Open Command Prompt and type
```
gcc -v
```
If gcc is installed then it should display a host of information starting with the sentence “Using built-in specs”.44

2. If you don't have gcc and are determined to run this in your Command Prompt, go to [this](https://preshing.com/20141108/how-to-install-the-latest-gcc-on-windows/ "Install GCC") link and follow the instructions to install gcc. However, the easier route would be to just use VScode.

For Mac:

```
...
```

## Run Program

1. First we must compile the program by entering the following into the Command Prompt:

For PC:

```
gcc -o rescale rescale.c
```

2. Run code by entering the following into the Command Prompt, where <ratio> is a number ( which can be a decimal ) that represent the size we want to increase/decrease the image by (eg. 2 doubles the image, .5 halves it):

For PC:

```
rescale <ratio> <input_file> <output_file>
```
