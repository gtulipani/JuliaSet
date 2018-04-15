# JuliaSet
## Description
CLI Application to generate a PGM file representing a [Julia Set](https://en.wikipedia.org/wiki/Julia_set) with the holomorphic function `f(z) = z² + s`.

## Building and Running
### Build
1. Navigate to the base folder
1. Execute `make`
### Create assembly files
1. Navigate to the base folder
1. Execute `make assembly`. This will generate the **.s** files

### Run
The application must be executed with the following syntax `./juliaSet [-argument] [-value]`
#### Parameters
The application accepts the following set of parameters:
1. `-r` or `--resolution`: sets the resolution of the image. **620x480** is the default resolution.
1. `-c` or `--center`: sets the coordinate in the complex plane where the image will be drawn from. **0+0i** is the default center.
1. `-s` or `--seed`: sets the `s` value from the holomorphic function, which will be used in the calculation for every of pixel the image. Modifying this value changes radically the resulting image. **-0.726895347709114071439+0.188887129043845954792** is the default seed.
1. `-w` or `--width`: sets the width of the image to draw. The value is divided in equals parts to the left and the right side of the center. **2** is the default width.
1. `-H` or `--height`: sets the height of the image to draw. The value is divided in equals parts to the up and the down side of the center. **2** is the default height.
1. `-o` or `--output`: sets the path of the resulting image. If this parameter is omitted or the value `-` is passed, the result will be printed by **stdout**. Otherwise, it will be used as path for the output file.

### Examples
1. Generate a PGM file with the default values. The holomorphic function will be evaluated for each point of the complex plane between `-1+i`, `-1-i`, `1+i` and `1-i` and redirect the **stdout** to a new file called `result.pgm` will be created:
   - `./juliaSet > result.pgm`
1. Zoom in an specific region centered in `0.282-0.007i`, using a square with a side of `0.005` units: 
   - `./juliaSet -c 0.282-0.007i -w 0.005 -H 0.005 -o zoomIn.pgm`

### Error Handling
The program handles a bunch of exceptions that may happen during the parse of the arguments supplied by the user:
1. Exceed the maximum supported value
   - The maximum supported `resolution` is **5120x2880**. Therefore, the program will be interrupted and a message will be displayed if this value is exceeded.
   - The `center`, `seed`, `width` and `height` arguments are floating point values. Therefore, the program will be interrupted and a message will be displayed if the maximum floating point value is exceeded.
2. Fall behind the minimum supported value
   - For logical reasons, the minimum supported `resolution` is **1x1**. Therefore, the program will be interrupted and a message will be displayed if a smaller value is provided.
3. Incorrect argument syntax
   - The `resolution` value must be conformed by the width and height pixels separated by `x` or by `,`. Therefore, the program will be interrupted and a message will be displayed if the syntax is incorrect.
   - The `center` and `seed` values are complex numbers, represented in binomial form. It's not neccesary to include both real and imaginary parts. The program will be interrupted and a message will be displayed if the syntax is incorrect.
   - The `width` and `height` values are floating point values. Therefore, the program will be interrupted and a message will be displayed if the syntax is incorrect.


### Arguments Extension
Because of the implementation of the arguments parsing, in order to include a new argument to the logic, the following steps must be followed:
 - Create a `parser` function as defined inside cArgument.h` library, with all the neccesary logic to parse the argument, update the result and the success flag, or specify an error message if anything went wrong.
 - Add a new line inside the `storeValidArguments()` function, in order to add a new element to the `SimpleList` instance inside `main.c` file, with the desired values for short description, long description and result element.

### Clean
1. Navigate to the base folder
1. Execute `make clean`. This will remove both executables, **.o** and **.s** files.

## Additional Resources
- [Fractals](https://en.wikipedia.org/wiki/Fractal)
- [Mandelbrot Set](https://en.wikipedia.org/wiki/Mandelbrot_set) (_deeply related with the Julia Set_)
- [GCC Compiler](https://gcc.gnu.org/)

