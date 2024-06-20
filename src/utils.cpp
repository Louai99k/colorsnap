#include "utils.h"
#include <algorithm>
#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

const double DEFAULT_COLOR_DISTANCE_THRESHOLD = 2.0;
const int DEFAULT_COLOR_PALETTE_SIZE = 8;

Args parse_args(int argc, char **argv) {
  Args args;

  char *filename = argv[1];

  // check for filename if it's provided or not
  if (argv[1] == nullptr) {
    std::cerr << "No File Name Provided"
              << "\n";
    exit(1);
  }
  // store filename
  args.filename = argv[1];

  // check if the color palette size is provided and valid or not. if not then
  // set it to default palette size
  bool invalid_color_palette_size = false;
  if (argv[2] == nullptr) {
    invalid_color_palette_size = true;
  } else {
    try {
      args.color_palette_size = std::stoi(argv[2]);
    } catch (const std::exception &e) {
      invalid_color_palette_size = true;
    }
  }

  if (invalid_color_palette_size) {
    args.color_palette_size = DEFAULT_COLOR_PALETTE_SIZE;
  }

  // the color distance threshold represents how much the colors should be far
  // from each other on hue wheel. do the same as palette size if not provided
  // or if it's invalid
  bool invalid_color_distance_threshold = false;
  if (argv[3] == nullptr) {
    invalid_color_distance_threshold = true;
  } else {
    try {
      args.color_distance_threshold = std::stod(argv[3]);
    } catch (const std::exception &e) {
      invalid_color_distance_threshold = true;
    }
  }

  if (invalid_color_distance_threshold) {
    args.color_distance_threshold = DEFAULT_COLOR_DISTANCE_THRESHOLD;
  }

  return args;
}

HSL rgb_to_hsl(int _r, int _g, int _b) {
  double r = _r / 255.0;
  double g = _g / 255.0;
  double b = _b / 255.0;

  double max = std::max({r, g, b});
  double min = std::min({r, g, b});

  double h, s, l;

  l = (max + min) / 2.0;

  if (max == min) {
    h = s = 0;
  } else {
    double d = max - min;
    s = (max - min) / (1 - (std::abs((2 * l) - 1)));

    if (max == r) {
      h = (g - b) / d + (g < b ? 6 : 0);
    } else if (max == g) {
      h = (b - r) / d + 2;
    } else {
      h = (r - g) / d + 4;
    }

    h *= 60;
  }

  return {h, s, l};
};

std::string rgb_to_hex(int r, int g, int b) {
  std::stringstream ss;
  ss << std::uppercase << std::setfill('0') << std::setw(6) << std::hex;
  ss << (r << 16 | g << 8 | b);
  return ss.str();
};

RGB hex_to_rgb(const std::string &hex) {
  if (hex.size() != 6) {
    return {0, 0, 0};
  }

  RGB rgb;
  long hex_decimal = std::stol(hex, NULL, 16);

  rgb.r = (hex_decimal >> 16) & 0xFF;
  rgb.g = (hex_decimal >> 8) & 0xFF;
  rgb.b = hex_decimal & 0xFF;

  return rgb;
}

Color rgb_to_color(int r, int g, int b) {
  RGB rgb = {r, g, b};
  HSL hsl = rgb_to_hsl(r, g, b);
  std::string hex = rgb_to_hex(r, g, b);
  return {rgb, hsl, hex};
}

std::unordered_map<std::string, int>
get_colors_count_map(unsigned char *image_data, int image_width,
                     int image_height, int image_channels,
                     double color_distance_threshold) {

  std::unordered_map<std::string, int> colors_map;
  double min_hue_diff = 10.0 * color_distance_threshold;
  double min_lumination_diff = 0.1 * color_distance_threshold;

  int image_size = image_width * image_height * image_channels;
  for (unsigned char *p = image_data; p != image_data + image_size;
       p += image_channels) {
    // Extract the RGB values from the current pixel
    int r = (int)p[0];
    int g = (int)p[1];
    int b = (int)p[2];

    // Convert the RGB values to a color object with HSL and hex representations
    Color color = rgb_to_color(r, g, b);

    if (colors_map.find(color.hex) != colors_map.end()) {
      // If the color is already in the map, increment its count
      colors_map[color.hex] += 1;
    } else {
      bool is_valid = true;
      // Check if the current color is sufficiently unique compared to the
      // colors already in the map
      for (auto &hex_count_pair : colors_map) {
        RGB rgb = hex_to_rgb(hex_count_pair.first);
        HSL hsl = rgb_to_hsl(rgb.r, rgb.g, rgb.b);
        double h_diff = std::abs(hsl.h - color.hsl.h);
        double l_diff = std::abs(hsl.l - color.hsl.l);
        // Determine if the current color is too similar to any existing color
        // in the map by comparing their hue and lumination differences against
        // thresholds
        if (h_diff < min_hue_diff && l_diff < min_lumination_diff) {
          is_valid = false;
          hex_count_pair.second += 1;
          break;
        }
      }

      // If the current color is unique enough, add it to the map
      if (is_valid) {
        colors_map[color.hex] = 1;
      }
    }
  }

  return colors_map;
}

std::vector<std::pair<std::string, int>>
get_top_colors(const std::unordered_map<std::string, int> colors_map,
               int color_palette_size) {

  std::vector<std::pair<std::string, int>> top_colors;

  // transform colors from map to vector to be able to sort it later
  for (const auto &hex_count_pair : colors_map) {
    top_colors.push_back(hex_count_pair);
  }

  // sort the vector based on the count of the colors
  std::sort(
      top_colors.begin(), top_colors.end(),
      [](const std::pair<std::string, int> &a,
         const std::pair<std::string, int> &b) { return a.second > b.second; });

  // resize the vector so it match how much the user want colors in his palette
  if (top_colors.size() > color_palette_size) {
    top_colors.resize(color_palette_size);
  }

  return top_colors;
}
