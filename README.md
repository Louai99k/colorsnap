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

2. **Build the Project:**
   There is a script called `build.sh` that is shipped with the project. You just need to call it.
   ```sh
   ./build.sh
   ```
3. If you get a (Permission denied) message you need to run this before the build command:
   ```sh
   chmod +x ./build.sh
   ```

## Usage

Run the `colorsnap` executable with the required arguments:
```sh
colorsnap <filename> [<color_palette_size>] [<color_distance_threshold>]
```

- `<filename>`: The path to the image file.
- `<color_palette_size>` (optional): The number of top colors to extract. Default is 8.
- `<color_distance_threshold>` (optional): The threshold for color clustering. Default is 2.0.

### Example

```sh
colorsnap ./image.jpg 5 1.5
```
This command processes `image.jpg`, extracting the top 5 colors with a clustering threshold of 1.5.

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
