#include "utils.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

int main(int argc, char **argv) {
  // retrieve args
  auto args = parse_args(argc, argv);
  auto filename = args.filename;

  // read the image
  int x, y, n;
  unsigned char *image_data = stbi_load(filename, &x, &y, &n, 0);

  if (image_data == NULL) {
    std::cerr << "Error reading image"
              << "\n";

    exit(1);
  }

  // get the required data for clustering algorithm
  auto colors_map =
      get_colors_count_map(image_data, x, y, n, args.color_distance_threshold);
  auto top_colors = get_top_colors(colors_map, args.color_palette_size);

  for (const auto &el : top_colors) {
    std::cout << el.first << "\n";
  }

  // free image data
  stbi_image_free(image_data);
}
