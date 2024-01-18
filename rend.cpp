//оцищение фона
internal void
clr_scr(u32 color) {
	unsigned int* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}
//рисование прямоугольника
internal void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

	x0 = clamp(0, x0, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	x1 = clamp(0, x1, render_state.width);
	y1 = clamp(0, y1, render_state.height);
	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}
//рисование круга
internal void
draw_circle_in_pixels(int x0, int y0, int x1, int y1, u32 color1, u32 color2) {
	x0 = clamp(0, x0, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	x1 = clamp(0, x1, render_state.width);
	y1 = clamp(0, y1, render_state.height);
	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			if ((x - (x1 + x0) / 2) * (x - (x1 + x0) / 2) + (y - (y1 + y0) / 2) * (y - (y1 + y0) / 2) <= ((x1 - x0) / 2) * ((x1 - x0) / 2))
				*pixel++ = color1;
			else
				*pixel++ = color2;
		}
	}
}
//масштаб
global_variable float render_scale = 0.0013f;
//края
internal void
draw_arena_borders(float arena_x, float arena_y, u32 color) {
	arena_x *= render_state.height * render_scale;
	arena_y *= render_state.height * render_scale;

	int x0 = (int)((float)render_state.width * .5f - arena_x);
	int x1 = (int)((float)render_state.width * .5f + arena_x);
	int y0 = (int)((float)render_state.height * .5f - arena_y);
	int y1 = (int)((float)render_state.height * .5f + arena_y);

	draw_rect_in_pixels(0, 0, render_state.width, y0, color);
	draw_rect_in_pixels(0, y1, x1, render_state.height, color);
	draw_rect_in_pixels(0, y0, x0, y1, color);
	draw_rect_in_pixels(x1, y0, render_state.width, render_state.height, color);
}
//переопределение прямоугольника
internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {

	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	//изменение в пиксели
	int x0 = (int)(x - half_size_x);
	int y0 = (int)(y - half_size_y);
	int x1 = (int)(x + half_size_x);
	int y1 = (int)(y + half_size_y);

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}
//переопределение круга
internal void
draw_circle(float x, float y, float half_size_x, float half_size_y, u32 color1, u32 color2) {

	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	//изменение в пиксели
	int x0 = (int)(x - half_size_x);
	int y0 = (int)(y - half_size_y);
	int x1 = (int)(x + half_size_x);
	int y1 = (int)(y + half_size_y);

	draw_circle_in_pixels(x0, y0, x1, y1, color1, color2);
}
//декодировка букв
const char* letters[][7] = {
" 00","0  0","0  0","0000","0  0","0  0","0  0",
"000","0  0","0  0","000","0  0","0  0","000",
" 000","0","0","0","0","0"," 000",
"000","0  0","0  0","0  0","0  0","0  0","000",
"0000","0","0","0000","0","0","0000",
"0000","0","0","0000","0","0","0",
" 000","0","0","0 00","0  0","0  0"," 00",
"0  0","0  0","0  0","0000","0  0","0  0","0  0",
"000"," 0"," 0"," 0"," 0"," 0","000",
"   0","   0","   0","   0","   0","0  0"," 00 ",
"0  0","0 0","0 0","00","0 0","0 0","0  0",
"0","0","0","0","0","0","0000",
"00 00","0 0 0","0 0 0","0   0","0   0","0   0","0   0",
"00  0","0 0 0","0 0 0","0 0 0","0 0 0","0 0 0","0  00",
" 00","0  0","0  0","0  0","0  0","0  0"," 00",
"000","0  0","0  0","000","0","0","0",
" 00","0  0","0  0","0  0","0  0","0  0"," 0000",
"000","0  0","0  0","000","0 0","0 0","0  0",
" 00","0","0"," 00","   0","   0"," 00",
"000"," 0"," 0"," 0"," 0"," 0"," 0",
"0  0","0  0","0  0","0  0","0  0","0  0"," 00",
"0   0","0   0","0   0"," 0 0"," 0 0"," 0 0","  0",
"0   0","0   0","0   0","0   0","0 0 0","0 0 0"," 0 0",
"0   0","0   0"," 0 0","  0"," 0 0","0   0","0   0",
"0   0","0   0"," 0 0","  0","  0","  0","  0",
"0000","   0","  0"," 0"," 0","0","0000",
"0"," 0","  0","   0","  0"," 0","0",
"   0","  0"," 0","0"," 0","  0","   0",
"   0","  00"," 0 0","   0","   0","   0","   0",
" 00","   0","   0"," 00","0","0","0000",
"","0","","","","0","",
};
//отрисовка текста
internal void
draw_text(const char* text, float x, float y, float size, u32 color) {
	float half_size = size * .5f;
	float original_y = y;

	while (*text) {
		if (*text != 32) {
			const char** letter;
			if (*text == 60) letter = letters[27];
			else if (*text == 62) letter = letters[26];
			else if (*text == 49) letter = letters[28];
			else if (*text == 50) letter = letters[29];
			else if (*text == 58) letter = letters[30];
			else letter = letters[*text - 'A'];
			float original_x = x;

			for (int i = 0; i < 7; i++) {
				const char* row = letter[i];
				while (*row) {
					if (*row == '0') {
						draw_rect(x, y, half_size, half_size, color);
					}
					x += size;
					row++;
				}
				y -= size;
				x = original_x;
			}
		}
		text++;
		x += size * 6.f;
		y = original_y;
	}
}
//чтение файла с текстуркой
u32 colors[13][6] = {
	0x2e222f, 0x3e3546, 0x625565, 0x966c6c, 0xab947a, 0x000000,
	0x694f62, 0x7f708a, 0x9babb2, 0xc7dcd0, 0xffffff, 0x000000,
	0x6e2727, 0xb33831, 0xea4f36, 0xf57d4a, 0x000000, 0x000000,
	0xae2334, 0xe83b3b, 0xfb6b1d, 0xf79617, 0xf9c22b, 0x000000,
	0x7a3045, 0x9e4539, 0xcd683d, 0xe6904e, 0xfbb954, 0x000000,
	0x4c3e24, 0x676633, 0xa2a947, 0xd5e04b, 0xfbff86, 0x000000,
	0x165a3c, 0x239063, 0x1ebc73, 0x91db69, 0xcddf6c, 0x000000,
	0x313638, 0x374e4a, 0x547e64, 0x92a984, 0xb2ba90, 0x000000,
	0x0b5e65, 0x0b8a8f, 0x0eaf9b, 0x30e1b9, 0x8ff8e2, 0x000000,
	0x323353, 0x484a77, 0x4d65b4, 0x4d9be6, 0x8fd3ff, 0x000000,
	0x45293f, 0x6b3e75, 0x905ea9, 0xa884f3, 0xeaaded, 0x000000,
	0x753c54, 0xa24b6f, 0xcf657f, 0xed8099, 0x000000, 0x000000,
	0x831c5d, 0xc32454, 0xf04f78, 0xf68181, 0xfca790, 0xfdcbb0
};
internal void
draw_file(string name, float x, float y) {
	name = "textures\\" + name + ".txt";
	ifstream fin(name);
	string array;
	int j = 0;
	while (!fin.eof()) {
		fin >> array;
#define State(a, b, c)\
case a:\
		draw_rect(x + 4 * i, y + 4 * j, 2, 2, colors[b][c]);\
break;

		for (int i = 0; i < array.length(); i++) {
			switch (array[i])
			{
				State('!', 0, 0);
				State('"', 0, 1);
				State('#', 0, 2);
				State('$', 0, 3);
				State('%', 0, 4);

				State('&', 1, 0);
				State('\'', 1, 1);
				State('(', 1, 2);
				State(')', 1, 3);
				State('*', 1, 4);

				State('+', 2, 0);
				State(',', 2, 1);
				State('-', 2, 2);
				State('.', 2, 3);

				State('/', 3, 0);
				State('0', 3, 1);
				State('1', 3, 2);
				State('2', 3, 3);
				State('3', 3, 4);

				State('4', 4, 0);
				State('5', 4, 1);
				State('6', 4, 2);
				State('7', 4, 3);
				State('8', 4, 4);

				State('9', 5, 0);
				State(':', 5, 1);
				State(';', 5, 2);
				State('<', 5, 3);
				State('=', 5, 4);

				State('>', 6, 0);
				State('?', 6, 1);
				State('@', 6, 2);
				State('A', 6, 3);
				State('B', 6, 4);

				State('C', 7, 0);
				State('D', 7, 1);
				State('E', 7, 2);
				State('F', 7, 3);
				State('G', 7, 4);

				State('H', 8, 0);
				State('I', 8, 1);
				State('J', 8, 2);
				State('K', 8, 3);
				State('L', 8, 4);

				State('M', 9, 0);
				State('N', 9, 1);
				State('O', 9, 2);
				State('P', 9, 3);
				State('Q', 9, 4);

				State('R', 10, 0);
				State('S', 10, 1);
				State('T', 10, 2);
				State('U', 10, 3);
				State('V', 10, 4);

				State('W', 11, 0);
				State('X', 11, 1);
				State('Y', 11, 2);
				State('Z', 11, 3);

				State('[', 12, 0);
				State('\\', 12, 1);
				State(']', 12, 2);
				State('^', 12, 3);
				State('_', 12, 4);
				State('`', 12, 5);
			}
		}
		j--;
	}
}
//отрисовка цифр
internal void
draw_number(int number, float x, float y) {
	int temp = number;
	int i = 0;
	while (true) {
		switch (temp % 10)
		{
		case 0:
			draw_file("0", x - 50 * i, y);
			break;
		case 1:
			draw_file("1", x - 50 * i, y);
			break;
		case 2:
			draw_file("2", x - 50 * i, y);
			break;
		case 3:
			draw_file("3", x - 50 * i, y);
			break;
		case 4:
			draw_file("4", x - 50 * i, y);
			break;
		case 5:
			draw_file("5", x - 50 * i, y);
			break;
		case 6:
			draw_file("6", x - 50 * i, y);
			break;
		case 7:
			draw_file("7", x - 50 * i, y);
			break;
		case 8:
			draw_file("8", x - 50 * i, y);
			break;
		case 9:
			draw_file("9", x - 50 * i, y);
			break;
		}
		temp /= 10;
		if (temp == 0) {
			break;
		}
		i++;
	}
}
//отрисовка определенных модулей
internal void
draw_wires(float x, float y, wires wire) {
	for (int i = 0; i < wire.Count(); i++) {
		switch (wire.get(i))
		{
		case 0:
			if (wire.IsCut(i)) {
				draw_file("w_fwhitewire", x + 20, y - 60 - 40 * i);
			}
			else {
				draw_file("w_twhitewire", x + 20, y - 60 - 40 * i);
			}
			break;
		case 1:
			if (wire.IsCut(i)) {
				draw_file("w_fredwire", x + 20, y - 60 - 40 * i);
			}
			else {
				draw_file("w_tredwire", x + 20, y - 60 - 40 * i);
			}
			break;
		case 2:
			if (wire.IsCut(i)) {
				draw_file("w_fbluewire", x + 20, y - 60 - 40 * i);
			}
			else {
				draw_file("w_tbluewire", x + 20, y - 60 - 40 * i);
			}
			break;
		case 3:
			if (wire.IsCut(i)) {
				draw_file("w_fyellowwire", x + 20, y - 60 - 40 * i);
			}
			else {
				draw_file("w_tyellowwire", x + 20, y - 60 - 40 * i);
			}
			break;
		case 4:
			if (wire.IsCut(i)) {
				draw_file("w_fblackwire", x + 20, y - 60 - 40 * i);
			}
			else {
				draw_file("w_tblackwire", x + 20, y - 60 - 40 * i);
			}
			break;
		}
	}
	if (wire.solved) {
		draw_file("solved", x + 284, y - 4);
	}
	else {
		draw_file("unsolved", x + 284, y - 4);
	}
}
internal void
draw_board(float x, float y, board boar) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if(boar.stat(2 * i + j)) draw_file("b_tbutton", x + 120 * j + 50, y - 130 * i - 65);
			else draw_file("b_fbutton", x + 120 * j + 50, y - 130 * i - 65);
			//draw_number(boar.num(2 * i + j), x + 120 * j + 66, y - 130 * i - 77);
#define Sign(a, b)\
case a:\
draw_file(b, x + 120 * j + 66, y - 130 * i - 77);\
break;
			switch (boar.num(2 * i + j))
			{
				Sign(1, "b_sign1");
				Sign(2, "b_sign2");
				Sign(3, "b_sign3");
				Sign(4, "b_sign4");
				Sign(5, "b_sign5");
			}
		}
	}
	if (boar.solved) {
		draw_file("solved", x + 284, y - 4);
	}
	else {
		draw_file("unsolved", x + 284, y - 4);
	}
}
internal void
draw_memory(float x, float y, memory mem) {
	draw_file("m_display", x + 60, y - 40);
	draw_number(mem.num(), x + 179, y - 61);
	for (int i = 0; i < 5; i++) {
		if (i <= mem.step) {
			draw_file("m_tstep", x + 64 + 40 * i, y - 175);
		}
		else {
			draw_file("m_fstep", x + 64 + 40 * i, y - 175);
		}
	}
	for (int i = 0; i < 4;i++) {
		draw_file("m_button", x + 75 * i + 12, y - 232);
		draw_number(mem.butt(i), x + 75 * i + 28, y - 244);
	}
	//draw_file("m_button", x + 75 * mem.m() + 12, y - 300);
	if (mem.solved) {
		draw_file("solved", x + 284, y - 4);
	}
	else {
		draw_file("unsolved", x + 284, y - 4);
	}
}
internal void
draw_hwires(float x, float y, hwires hwire) {
	for (int i = 0; i < hwire.Count(); i++) {
		if (hwire.s(i)) {
			draw_file("h_tsymbol", x + 40 * i + 22, y - 240);
		}
		else {
			draw_file("h_fsymbol", x + 40 * i + 22, y - 240);
		}
		if (hwire.r(i) and hwire.b(i)) {
			if (hwire.state(i)) {
				draw_file("h_frednbluehwire", x + 40 * i + 30, y - 80);
			}
			else {
				draw_file("h_trednbluehwire", x + 40 * i + 30, y - 80);
			}
		}
		else if (hwire.r(i) and !hwire.b(i)) {
			if (hwire.state(i)) {
				draw_file("h_fredhwire", x + 40 * i + 30, y - 80);
			}
			else {
				draw_file("h_tredhwire", x + 40 * i + 30, y - 80);
			}
		}
		else if (!hwire.r(i) and hwire.b(i)) {
			if (hwire.state(i))
			{
				draw_file("h_fbluehwire", x + 40 * i + 30, y - 80);
			}
			else {
				draw_file("h_tbluehwire", x + 40 * i + 30, y - 80);
			}
		}
		else {
			if (hwire.state(i)) {
				draw_file("h_fwhitehwire", x + 40 * i + 30, y - 80);
			}
			else {
				draw_file("h_twhitehwire", x + 40 * i + 30, y - 80);
			}
		}
		if (hwire.l(i)) {
			draw_file("h_tlight", x + 40 * i + 20, y - 40);
		}
		else {
			draw_file("h_flight", x + 40 * i + 20, y - 40);
		}
		//draw_number(hwire.com[i], x + 40 * i + 15, y - 100 - 20 * i);
	}
	if (hwire.solved) {
		draw_file("solved", x + 284, y - 4);
	}
	else {
		draw_file("unsolved", x + 284, y - 4);
	}
}
//распределение отрисовок
internal void
draw_module(float x, float y, int i, int j, list arr) {
	int ind = 4 * i + j;
	if (ind < arr.Len()) {
		draw_file("wall", x, y);
		switch (arr.Get(ind)) {
		case 1:
			draw_wires(x, y, arr.w(ind));
			break;
		case 2:
			draw_board(x, y, arr.b(ind));
			break;
		case 3:
			draw_memory(x, y, arr.m(ind));
			break;
		case 4:
			draw_hwires(x, y, arr.h(ind));
			break;
		}
	}
	else {
		draw_file("block", x, y);
	}
}