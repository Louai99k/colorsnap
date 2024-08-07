#include "utils.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

int main(int argc, char **argv) {
  // parse the app's args
  Args args = parse_args(argc, argv);

  // read the image
  int image_width, image_height, image_channels;
  unsigned char *image_data = stbi_load(args.filename.c_str(), &image_width,
                                        &image_height, &image_channels, 0);

  if (image_data == nullptr) {
    std::cerr << "Error reading image"
              << "\n";

    exit(1);
  }

  // get the required data for clustering algorithm
  auto colors_map =
      get_colors_count_map(image_data, image_width, image_height,
                           image_channels, args.color_distance_threshold);
  auto top_colors = get_top_colors(colors_map, args.color_palette_size,
                                   args.darkness_multiplier);

  for (const auto &color : top_colors) {
    std::cout << color.first << "\n";
  }

  // free image data
  stbi_image_free(image_data);
}
