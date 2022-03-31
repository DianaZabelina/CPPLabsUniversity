#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <cerrno>
#include <cmath>

constexpr int IMG_WIDTH = 1024;
constexpr int IMG_HEIGHT = 768;

constexpr double XSCALE = 20.0;
constexpr double YSCALE = 20.0;
constexpr double ZSCALE = 300.0;
constexpr double XMIN = -15.0;
constexpr double XMAX = 15.0;
constexpr double YMIN = -15.0;
constexpr double YMAX = 15.0;
constexpr double BIGSTEP = 0.5;
constexpr double SMALLSTEP = 0.001;
constexpr double Pi = acos(-1);

constexpr uint32_t COL_BLACK = 0xff000000;
constexpr uint32_t COL_WHITE = 0xffffffff;

#pragma pack(push, 1)

struct TGAHeader {
	uint8_t id_len; //длина идентификатора
	uint8_t pal_type; //тип палитры
	uint8_t img_type;
	uint8_t pal_desc[5];
	uint16_t pos_x;
	uint16_t pos_y;
	uint16_t width;
	uint16_t height;
	uint8_t depth;
	uint8_t img_desc;

};
struct BMPFileHeader {
	uint16_t signature;
	uint32_t file_size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t img_offset;
};
struct BMPInfoHeader {
	uint32_t header_length;
	uint32_t width;
	uint32_t height;
	uint16_t planes; //кол-во плоскостей
	uint16_t depth;
	uint32_t compression;
	uint32_t img_length; //размер изображения
	uint32_t xppm;
	uint32_t yppm;
	uint32_t colors; //доступные цвета
	uint32_t colors_important; //используемые цвета
};

#pragma pack(pop)

double sinc(double x) {
	if (x == 0.0)
		return 1.0;
	return sin(x) / x;
}

double my_func(double x, double y) {
	return sinc(hypot(x, y));
}

void fill_rect(std::vector<uint32_t> &image, int x0, int y0, int w, int h,
		uint32_t color) {
	for (int x = x0; x < x0 + w; ++x)
		for (int y = y0; y < y0 + h; ++y)
			image[y * IMG_WIDTH + x] = color;
}

void draw_pixel(std::vector<uint32_t> &image, int x, int y, uint32_t color) {
	if (x < 0 or x >= IMG_WIDTH or y < 0 or y >= IMG_HEIGHT)
		return;
	image[y * IMG_WIDTH + x] = color;
}

void draw_pixel_2(std::vector<uint32_t> &image, std::vector<int> &horizon,
		int x, int y, uint32_t color) {
	if (x < 0 or x >= IMG_WIDTH)
		return;
	if (y >= horizon[x])
		return;
	horizon[x] = y;
	if (y >= IMG_HEIGHT)
		return;
	image[y * IMG_WIDTH + x] = color;
}

void convert_isometry(double x, double y, double z, int &px, int &py) {
	px = int(
			IMG_WIDTH / 2 -
			XSCALE * cos(Pi / 6.0) * x +
			YSCALE * cos(Pi / 6.0) * y);
	py = int(
			IMG_HEIGHT / 2 +
			XSCALE * sin(Pi / 6.0) * x +
			YSCALE * sin(Pi / 6.0) * y - ZSCALE * z);
}

int main() {
	std::vector<uint32_t> image;
	std::vector<int> horizon;
	image.resize(IMG_WIDTH * IMG_HEIGHT);
	horizon.resize(IMG_WIDTH);

	//покраска фона
	for (auto &&p : image)
		p = COL_BLACK;

	//fill_rect(image, 64, 64, 96, 96, 0xffffff00);
	//fill_rect(image, 80, 80, 96, 96, 0xffff00ff);
	//fill_rect(image, 128, 128, 96, 96, 0xff00ffff);

	double y, x, z;
	int px, py;
	for (auto &&y : horizon)
		y = IMG_HEIGHT;
	//линии рисуются параллельно XZ
	for (y = YMAX; y >= YMIN; y -= BIGSTEP)
		for (x = XMAX; x >= XMIN; x -= SMALLSTEP) {
			z = my_func(x, y);
			convert_isometry(x, y, z, px, py);
			draw_pixel_2(image, horizon, px, py, COL_WHITE);
		}
	for (auto &&y : horizon)
			y = IMG_HEIGHT;
	//линии рисуются пареллельно YZ
	for (x = XMAX; x >= XMIN; x -= BIGSTEP)
		for (y = YMAX; y >= YMIN; y -= SMALLSTEP) {
			z = my_func(x, y);
			convert_isometry(x, y, z, px, py);
			draw_pixel_2(image, horizon, px, py, COL_WHITE);
		}

	TGAHeader header { };
	std::ofstream tga_file { "output.tga", std::ios::binary };
	header.img_type = 2;
	header.width = IMG_WIDTH;
	header.height = IMG_HEIGHT;
	header.depth = 32;
	header.img_desc = 0b00101000;

	if (not tga_file) {
		std::cerr << "Error" << strerror(errno) << std::endl;
		return 1;
	}
	tga_file.write(reinterpret_cast<char*>(&header), sizeof(header));
	tga_file.write(reinterpret_cast<char*>(&image[0]),
			image.size() * sizeof(image[0]));
	tga_file.close();

	BMPFileHeader bmpf { };
	BMPInfoHeader bmpi { };
	std::ofstream bmp_file { "output.bmp", std::ios::binary };
	bmpf.signature = 0x0001 * 'B' + 0x0100 * 'M';
	bmpf.img_offset = sizeof(bmpf) + sizeof(bmpi);
	bmpf.file_size = bmpf.img_offset + image.size() * sizeof(image[0]);

	bmpi.header_length = sizeof(bmpi);
	bmpi.width = IMG_WIDTH;
	bmpi.height = -IMG_HEIGHT;//?
	bmpi.depth = 32;
	bmpi.img_length = image.size() * sizeof(image[0]);
	bmpi.planes = 1;

	bmp_file.write(reinterpret_cast<char*>(&bmpf), sizeof(bmpf));
	bmp_file.write(reinterpret_cast<char*>(&bmpi), sizeof(bmpi));
	bmp_file.write(reinterpret_cast<char*>(&image[0]),
			image.size() * sizeof(image[0]));
	bmp_file.close();

	return 0;

}
