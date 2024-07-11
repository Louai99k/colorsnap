# ColorSnap

ColorSnap is a command-line tool designed to extract the most prominent colors from an image. It leverages the STB image library to load image data and employs a clustering algorithm to identify the dominant colors. This tool is useful for designers, developers, and anyone interested in color analysis of images.

## Features

- Load and read images using the STB image library.
- Convert RGB color values to HSL and Hexadecimal formats.
- Cluster similar colors based on configurable thresholds.
- Output the most prominent colors in an image.

## Requirements

- `cmake`
- `make`

## Installation

1. **Clone the Repository:**

   ```sh
   git clone https://github.com/Louai99k/colorsnap.git
   cd colorsnap
   ```
   
2. **Make `build.sh` executable:**

   There is a script called `build.sh` that is shipped with the project. Run this command to make it executable.
   ```sh
   chmod +x ./build.sh
   ```
   
3. **Build the Project:**
   
   ```sh
   ./build.sh
   ```
   
   #### After this, a folder called `release` will be created and you will see the binary file called `colorsnap` inside it. If you want to install the binary in your `/usr/bin` folder to call it from anywhere in the system you can follow the next steps otherwise ignore them.

4. **Navigate to the `release` folder:**
   
   ```sh
   cd release/
   ```
   
5. **Install the binary:**

   Run the following command and the binary should be installed on the `/usr/bin` folder
   ```sh
   sudo make install
   ```

## Usage

Run the `colorsnap` executable with the required options:
```sh
colorsnap -f <filename> [-s|--size color_palette_size] [-r|--threshold color_threshold] [-d|--darkness darkness_multiplier] 
```

### Available options

- `-f, --file`: The path to the image file.
- `-s, --size` (optional): The number of top colors to extract. Default is 8.
- `-r, --threshold` (optional): The threshold for color clustering. Default is 2.0.
- `-d, --darkness` (optional): This is an option that accepts values between -1 and 1. Values less than zero will make the colors lighter by the precentage you apply. values greater than zero will make the colors darker. Default is 0.0.

### Example

```sh
colorsnap -f ./image.jpg -s 5 --threshold 1.5 -d 0.1
```
This command processes `image.jpg`, extracting the top 5 colors with a clustering threshold of 1.5 and make the color darker by 10%.

It will output the following:
```
FF00FF
AABBCC
...
```
so you can pipe it with other commands to make it useful. Or you can just copy and paste 😁.

## License

This project is licensed under the MIT License. See the [LICENSE](https://github.com/Louai99k/colorsnap/blob/master/LICENSE) file for more details.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue to discuss improvements or bug fixes.

## Acknowledgments

- [STB Image Library](https://github.com/nothings/stb) for image loading functionality.
- [CLI11 Library](https://github.com/CLIUtils/CLI11) for parsing the args.
