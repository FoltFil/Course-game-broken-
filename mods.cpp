//сами модули
class wires {
private:
	int count;
	int color[6];//0-белый,1-красный,2-синий,3-жёлтый,4-черный
	int right;
	int white, red, blue, yellow, black;
	bool iscut[6];
public:
	bool solved;
	int Count() {
		return count;
	}
	int get(int i) {
		return color[i];
	}
	void gen(int serial) {
		solved = false;
		count = 3 + rand() % 4;
		white = 0;
		red = 0;
		blue = 0;
		yellow = 0;
		black = 0;
		right = 0;
		for (int i = 0; i < count; i++) {
			iscut[i] = false;
			color[i] = rand() % 5;
			switch (color[i])
			{
			case 0:
				white++;
				break;
			case 1:
				red++;
				break;
			case 2:
				blue++;
				break;
			case 3:
				yellow++;
				break;
			case 4:
				black++;
				break;
			}
		}
		switch (count)
		{
		case 3:
			if (red == 0) {
				right = 1;
			}
			else if (color[count-1] == 0) {
				right = 2;
			}
			else if (blue > 1) {
				for (int i = 0; i < count; i++) {
					if (color[i] == 2) {
						right = i;
					}
				}
			}
			else {
				right = 2;
			}
			break;
		case 4:
			if (red > 1 and serial == 1) {
				for (int i = 0; i < count; i++) {
					if (color[i] == 1) {
						right = i;
					}
				}
			}
			else if (color[count - 1] == 3 && red == 0) {
				right = 0;
			}
			else if (blue == 1) {
				right = 0;
			}
			else if (yellow > 1) {
				right = 3;
			}
			else right = 1;
			break;
		case 5:
			if (color[count - 1] == 4 and serial == 1) {
				right = 3;
			}
			else if (red == 1 && yellow > 1) {
				right = 0;
			}
			else if (black == 0) {
				right = 1;
			}
			else {
				right = 0;
			}
			break;
		case 6:
			if (yellow == 0 and serial == 1) {
				right = 2;
			}
			else if(yellow == 1 && white > 1){
				right = 3;
			}
			else if(red == 0){
				right = 5;
			}
			else {
				right = 3;
			}
			break;
		}
	}
	int test(int attempt) {
		if (attempt < count) {
			iscut[attempt] = true;
			if (attempt == right) {
				solved = true;
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	bool IsCut(int i) {
		return iscut[i];
	}
};

class board {
private:
	int table[4][5];
	int temp1, temp2, temp3, temp4;
	int arr[4];
	int tarr[4];
	int step;
	bool ispressed[4];
	void set() {
		table[0][0] = 2;
		table[1][0] = 4;
		table[2][0] = 3;
		table[3][0] = 1;

		table[0][1] = 1;
		table[1][1] = 2;
		table[2][1] = 5;
		table[3][1] = 3;

		table[0][2] = 4;
		table[1][2] = 5;
		table[2][2] = 1;
		table[3][2] = 2;

		table[0][3] = 1;
		table[1][3] = 3;
		table[2][3] = 4;
		table[3][3] = 5;

		table[0][4] = 5;
		table[1][4] = 2;
		table[2][4] = 4;
		table[3][4] = 3;
	}
	void sort() {
		for (int j = 1; j < 4; j++) {
			bool sorted = true;
			for (int i = 0; i < 4 - j; i++) {
				if (arr[i] > arr[i + 1]) {
					temp2 = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = temp2;
					sorted = false;
				}
			}
			if (sorted) break;
		}
	}
	void shuffle() {
		for (int i = 0; i < rand() % 5 + 5; i++) {
			temp2 = rand() % 4;
			temp3 = rand() % 4;
			//temp4 = tarr[temp2];
			//tarr[temp2] = tarr[temp3];
			//tarr[temp3] = temp4;
			swap(tarr[temp2], tarr[temp3]);
		}
	}
public:
	bool solved;
	void gen() {
		solved = false;
		set();
		step = 0;
		temp1 = rand() % 5;
		for (int i = 0; i < 4; i++) {
			arr[i] = table[i][temp1];
			tarr[i] = table[i][temp1];
			ispressed[i] = false;
		}
		shuffle();
	}
	int test(int i) {
		if (arr[step] == tarr[i]) {
			ispressed[i] = true;
			step++;
			if (step == 4) {
				solved = true;
				return 1;
			}
			return -1;
		}
		else {
			return 0;
		}
	}
	int num(int i) {
		return tarr[i];
	}
	bool stat(int i) {
		return ispressed[i];
	}
};

class memory {
private:
	int button[5][4];//клавиши
	int display[5];//число на дисплее
	int temp1 = 1, temp2 = 1;
	void shuffle() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 4; j++) {
				button[i][j] = j + 1;
			}
		}
		for (int j = 0; j < 5; j++)
		{
			for (int i = 0; i < 4; i++) {
				temp1 = button[j][i];
				temp2 = rand() % 4;
				button[j][i] = button[j][temp2];
				button[j][temp2] = temp1;
			}
		}
	}
public:
	int step;
	int mem[2][5];//0-позиция 1 - число
	bool solved;
	int m() {
		return mem[0][step];
	}
	void gen() {
		solved = false;
		step = 0;
		shuffle();
		for (int i = 0; i < 5; i++) {
			display[i] = 1 + rand() % 4;
		}
		//шаг 1
		switch (display[0])
		{
		case 1:
			mem[0][0] = 1;
			mem[1][0] = button[0][1];
			break;
		case 2:
			mem[0][0] = 1;
			mem[1][0] = button[0][1];
			break;
		case 3:
			mem[0][0] = 2;
			mem[1][0] = button[0][2];
			break;
		case 4:
			mem[0][0] = 3;
			mem[1][0] = button[0][3];
			break;
		}

		//шаг 2
		switch (display[1])
		{
		case 1:
			mem[1][1] = 4;
			for (int i = 0; i < 4; i++) {
				if (button[1][i] == 4) {
					mem[0][1] = i;
				}
			}
			break;
		case 2:
			mem[0][1] = mem[0][0];
			mem[1][1] = button[1][mem[0][1]];
			break;
		case 3:
			mem[0][1] = 0;
			mem[1][1] = button[1][0];
			break;
		case 4:
			mem[0][1] = mem[0][0];
			mem[1][1] = button[1][mem[0][1]];
			break;
		}

		//шаг 3
		switch (display[2])
		{
		case 1:
			mem[1][2] = mem[1][1];
			for (int i = 0; i < 4; i++) {
				if (button[2][i] == mem[1][2]) {
					mem[0][2] = i;
				}
			}
			break;
		case 2:
			mem[1][2] = mem[1][0];
			for (int i = 0; i < 4; i++) {
				if (button[2][i] == mem[1][2]) {
					mem[0][2] = i;
				}
			}
			break;
		case 3:
			mem[0][2] = 2;
			mem[1][2] = button[2][2];
			break;
		case 4:
			mem[1][2] = 4;
			for (int i = 0; i < 4; i++) {
				if (button[2][i] == 4) {
					mem[0][2] = i;
				}
			}
			break;
		}

		//шаг 4
		switch (display[3])
		{
		case 1:
			mem[0][3] = mem[0][0];
			mem[1][3] = button[3][mem[0][3]];
			break;
		case 2:
			mem[0][3] = 0;
			mem[1][3] = button[3][0];
			break;
		case 3:
			mem[0][3] = mem[0][1];
			mem[1][3] = button[3][mem[0][3]];
			break;
		case 4:
			mem[0][3] = mem[0][1];
			mem[1][3] = button[3][mem[0][3]];
			break;
		}

		//шаг 5
		switch (display[4])
		{
		case 1:
			mem[1][4] = mem[1][0];
			for (int i = 0; i < 4; i++) {
				if (button[4][i] == mem[1][4]) {
					mem[0][4] = i;
				}
			}
			break;
		case 2:
			mem[1][4] = mem[1][1];
			for (int i = 0; i < 4; i++) {
				if (button[4][i] == mem[1][4]) {
					mem[0][4] = i;
				}
			}
			break;
		case 3:
			mem[1][4] = mem[1][3];
			for (int i = 0; i < 4; i++) {
				if (button[4][i] == mem[1][4]) {
					mem[0][4] = i;
				}
			}
			break;
		case 4:
			mem[1][4] = mem[1][2];
			for (int i = 0; i < 4; i++) {
				if (button[4][i] == mem[1][4]) {
					mem[0][4] = i;
				}
			}
			break;
		}
	}
	int test(int place) {
		switch (step)
		{
		case 0:
			if (place == mem[0][0]) {
				step++;
				return -1;
			}
			else {
				return 0;
			}
			break;
		case 1:
			if (place == mem[0][1]) {
				step++;
				return -1;
			}
			else {
				return 0;
			}
			break;
		case 2:
			if (place == mem[0][2]) {
				step++;
				return -1;
			}
			else {
				return 0;
			}
			break;
		case 3:
			if (place == mem[0][3]) {
				step++;
				return -1;
			}
			else {
				return 0;
			}
			break;
		case 4:
			if (place == mem[0][4]) {
				solved = true;
				return 1;
			}
			else {
				return 0;
			}
			break;
		}
	}
	int num() {
		return display[step];
	}
	int butt(int i) {
		return button[step][i];
	}
	int s() {
		return step;
	}
};

class hwires {
private:
	int count;
	int wire[4][6];//0-красный 1-синий 2-метка 3-светодиод
	int cut;
	int tocut;
	bool iscut[6];
	int temp;
	int light;
	int star;
public:
	int com[6];
	bool solved;
	bool comb[6];
	int Count() {
		return count;
	}
	void gen(int serial, int battery) {
		solved = false;
		light = 0;
		star = 0;
		temp = 0;
		tocut = 0;
		cut = 0;
		count = 3 + rand() % 4;
		for (int i = 0; i < count; i++) {
			com[i] = 0;
			temp = 0;
			iscut[i] = false;
			for (int j = 0; j < 4; j++) {
				wire[j][i] = rand() % 2;
				temp += (int)(wire[j][i] * pow(2, j));
			}
			com[i] += temp;
			if (wire[3][i]) {
				light++;
			}
			if (wire[2][i]) {
				star++;
			}
		}
		for (int i = 0; i < count; i++) {
			switch (com[i])
			{
			case 0:
			case 4:
			case 5:
				comb[i] = true;
				tocut++;
				break;
			case 6:
			case 8:
			case 15:
				comb[i] = false;
				break;
			case 1:
			case 2:
			case 3:
			case 11:
				if (serial == 0) {
					comb[i] = false;
				}
				else {
					comb[i] = true;
					tocut++;
				}
				break;
			case 7:
			case 10:
			case 14:
				comb[i] = true;
				tocut++;
				break;
			case 9:
			case 12:
			case 13:
				if (battery > 1) {
					comb[i] = true;
					tocut++;
				}
				else {
					comb[i] = false;
				}
				break;
			}
		}
		for (int i = 0; i < count; i++) {
			if (comb[i]) {
				break;
			}

			if (i == (count - 1)) {
				comb[2] = true;
				tocut++;
			}
		}
	}
	int test(int attempt) {
		iscut[attempt] = true;
		if (comb[attempt]) {
			cut++;
			if (cut == tocut) {
				solved = true;
				return 1; 
			}
			return -1;
		}
		else {
			return 0;
		}
	}
	bool state(int i) {
		return iscut[i];
	}
	bool r(int i) {
		return wire[0][i];
	}
	bool b(int i) {
		return wire[1][i];
	}
	bool s(int i) {
		return wire[2][i];
	}
	bool l(int i) {
		return wire[3][i];
	}
	bool c(int i) {
		return comb[i];
	}
};

//основной список
class mod {
private:
	int type;//1 - провода, 2 - клавиатура, 3 - память, 4 - сложные провода
	wires * module1;
	board * module2;
	memory* module3;
	hwires* module4;
public:
	void set_type(int tipe) {
		switch (tipe)
		{
		case 1:
			module1 = new wires();
			break;
		case 2:
			module2 = new board();
			break;
		case 3:
			module3 = new memory();
			break;
		case 4:
			module4 = new hwires();
			break;
		}
		type = tipe;
	}
	int get_type() {
		return type;
	}
	bool stat() {
		switch (type)
		{
		case 1:
			return module1->solved;
			break;
		case 2:
			return module2->solved;
			break;
		case 3:
			return module3->solved;
			break;
		case 4: 
			return module4->solved;
			break;
		}
	}
};
class list {
private:
	u32 count;
	mod* Arr;
	wires* mod1;
	board* mod2;
	memory* mod3;
	hwires* mod4;
	int serial;
	int battery;
	void clear() {
		for (u32 i = 0; i < count; i++) {
			Arr[i].set_type(1 + rand() % 4);
			switch (Arr[i].get_type())
			{
			case 1:
				mod1[i].gen(serial);
				break;
			case 2:
				mod2[i].gen();
				break;
			case 3:
				mod3[i].gen();
				break;
			case 4:
				mod4[i].gen(serial, battery);
				break;
			}
		}
	}
public:
	list(unsigned N = 0) {
		serial = rand() % 2;
		battery = rand() % 4;
		if (N) {
			Arr = (mod*)malloc(sizeof(mod)*N);
			mod1 = (wires*)malloc(sizeof(wires) * N);
			mod2 = (board*)malloc(sizeof(board) * N);
			mod3 = (memory*)malloc(sizeof(memory) * N);
			mod4 = (hwires*)malloc(sizeof(hwires) * N);
		}
		else{
			Arr = 0;
		}
		count = N;
		clear();
	}
	int Get(u32 Ind) {
		if (Ind > count) {
			return -1;
		}
		else {
			return Arr[Ind].get_type();
		}
	}
	wires w(int i) {
		return mod1[i];
	}
	wires* pw(int i) {
		return &mod1[i];
	}
	board b(int i) {
		return mod2[i];
	}
	board* pb(int i) {
		return &mod2[i];
	}
	memory m(int i) {
		return mod3[i];
	}
	memory* pm(int i) {
		return &mod3[i];
	}
	hwires h(int i) {
		return mod4[i];
	}
	hwires* ph(int i) {
		return &mod4[i];
	}
	unsigned Len() {
		return count;
	};
	int ser() {
		return serial;
	}
	int bat() {
		return battery;
	}
	bool stat() {
		for (int i = 0; i < count; i++) {
			switch (Arr[i].get_type())
			{
			case 1:
				if (!mod1[i].solved) return 0;
				break;
			case 2:
				if (!mod2[i].solved) return 0;
				break;
			case 3:
				if (!mod3[i].solved) return 0;
				break;
			case 4:
				if (!mod4[i].solved) return 0;
				break;
			}
		}
		return 1;
	}
};
