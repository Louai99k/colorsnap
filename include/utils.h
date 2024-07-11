#pragma once
#include <string>
#include <unordered_map>
#include <vector>

struct RGB {
  int r, g, b;
};

struct HSL {
  double h, s, l;
};

struct Color {
  RGB rgb;
  HSL hsl;
  std::string hex;
};

struct Args {
  std::string filename;
  int color_palette_size;
  double color_distance_threshold;
  double darkness_multiplier;
};

Args parse_args(int, char **);
HSL rgb_to_hsl(int, int, int);
std::string rgb_to_hex(int, int, int);
RGB hsl_to_rgb(double, double, double);
RGB hex_to_rgb(const std::string &);
Color rgb_to_color(int, int, int);
std::unordered_map<std::string, int> get_colors_count_map(unsigned char *, int,
                                                          int, int, double);
std::vector<std::pair<std::string, int>>
get_top_colors(const std::unordered_map<std::string, int>, int, double);
