#define is_down(b) input->buttons[b].is_down//упрощение условий
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

//некоторые необхожимые переменные
float arena_half_size_x, arena_half_size_y;
float curd = 2;
list *arrs = new list();
int amount = 5;
int x, y, a;
int mod_x, mod_y;
int mcur_x, mcur_y;
int pos, ind, type;
int health, max_health(3);
Gamemode current_gamemode;
int wtime = 0;
//обработка модулей
internal void
process_wires(int count) {
	if (mcur_x >= 22 and mcur_x <= 258) {
		if (mcur_y >= 60 and mcur_y <= 72) {
			draw_file("w_col", 19 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 58 - 364 * mod_y);
			pos = 1;
		}
		else if (mcur_y >= 100 and mcur_y <= 112) {
			draw_file("w_col", 19 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 98 - 364 * mod_y);
			pos = 2;
		}
		else if (mcur_y >= 140 and mcur_y <= 152) {
			draw_file("w_col", 19 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 138 - 364 * mod_y);
			pos = 3;
		}
		else if (mcur_y >= 180 and mcur_y <= 192 and count > 3) {
			draw_file("w_col", 19 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 178 - 364 * mod_y);
			pos = 4;
		}
		else if (mcur_y >= 220 and mcur_y <= 232 and count > 4) {
			draw_file("w_col", 19 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 218 - 364 * mod_y);
			pos = 5;
		}
		else if (mcur_y >= 260 and mcur_y <= 272 and count > 5) {
			draw_file("w_col", 19 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 258 - 364 * mod_y);
			pos = 6;
		}
		else {
			pos = 0;
		}
	}
	else {
		pos = 0;
	}
}
internal void
process_board() {
	if (mcur_x >= 52 and mcur_x <= 120) {
		if (mcur_y >= 66 and mcur_y <= 172) {
			draw_file("b_col", 49 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 64 - 364 * mod_y);
			pos = 1;
		}
		else if (mcur_y >= 195 and mcur_y <= 303) {
			draw_file("b_col", 49 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 193 - 364 * mod_y);
			pos = 3;
		}
		else {
			
		}
	}
	else if (mcur_x >= 172 and mcur_x <= 240) {
		if (mcur_y >= 66 and mcur_y <= 172) {
			draw_file("b_col", 169 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 64 - 364 * mod_y);
			pos = 2;
		}
		else if (mcur_y >= 195 and mcur_y <= 303) {
			draw_file("b_col", 169 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 193 - 364 * mod_y);
			pos = 4;
		}
		else {
			pos = 0;
		}
	}
	else {
		pos = 0;
	}
}
internal void
process_memory() {
	if (mcur_y >= 232 and mcur_y <= 340) {
		if (mcur_x >= 14 and mcur_x <= 82) {
			draw_file("b_col", 11 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 230 - 364 * mod_y);
			pos = 1;
		}
		else if (mcur_x >= 89 and mcur_x <= 157) {
			draw_file("b_col", 86 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 230 - 364 * mod_y);
			pos = 2;
		}
		else if (mcur_x >= 165 and mcur_x <= 232) {
			draw_file("b_col", 162 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 230 - 364 * mod_y);
			pos = 3;
		}
		else if (mcur_x >= 239 and mcur_x <= 307) {
			draw_file("b_col", 236 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 230 - 364 * mod_y);
			pos = 4;
		}
		else {
			pos = 0;
		}
	}
	else {
		pos = 0;
	}
}
internal void
process_hwires(int count) {
	if (mcur_y >= 81 and mcur_y <= 235) {
		if (mcur_x >= 34 and mcur_x <= 46) {
			draw_file("h_col", 28 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 79 - 364 * mod_y);
			pos = 1;
		} 
		else if (mcur_x >= 74 and mcur_x <= 86) {
			draw_file("h_col", 68 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 79 - 364 * mod_y);
			pos = 2;
		}
		else if (mcur_x >= 114 and mcur_x <= 126) {
			draw_file("h_col", 108 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 79 - 364 * mod_y);
			pos = 3;
		}
		else if (mcur_x >= 154 and mcur_x <= 166 and count > 3) {
			draw_file("h_col", 148 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 79 - 364 * mod_y);
			pos = 4;
		}
		else if (mcur_x >= 194 and mcur_x <= 206 and count > 4) {
			draw_file("h_col", 188 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 79 - 364 * mod_y);
			pos = 5;
		}
		else if (mcur_x >= 234 and mcur_x <= 246 and count > 5) {
			draw_file("h_col", 228 + 321 * mod_x - arena_half_size_x, arena_half_size_y - 79 - 364 * mod_y);
			pos = 6;
		}
		else {
			pos = 0;
		}
	}
	else {
		pos = 0;
	}

}
internal void
process(int cur_x, int cur_y) {
	ind = clamp(0, 4 * mod_y + mod_x, arrs->Len());
	type = arrs->Get(ind);
	wires mod1;
	hwires mod4;
	mcur_x = cur_x + arena_half_size_x - curd;
	mcur_y = cur_y - arena_half_size_y - curd;
	mcur_x = mcur_x - arena_half_size_x + 2 - 321 * mod_x + (mod_x >= 2 ? 1 : 0);
	mcur_y = mcur_y + arena_half_size_y + 2 + 364 * mod_y;
	//draw_rect(mcur_x, mcur_y, curd, curd, 0xffffff);
	mcur_x = abs(642 + mcur_x);
	mcur_y = abs(360 - mcur_y);
	//draw_number(mcur_x, 0, 0);
	//draw_number(mcur_y, 0, -100);
	switch (type)
	{
	case 1:
		mod1 = arrs->w(ind);
		process_wires(mod1.Count());
		break;
	case 2:
		process_board();
		break;
	case 3:
		process_memory();
		break;
	case 4:
		mod4 = arrs->h(ind);
		process_hwires(mod4.Count());
		break;
	}
	//draw_number(pos, 200, 0);
}

//логика всей игры
internal void
simulate_game(Input* input, float dt) {
	srand(rand());
	arena_half_size_x = render_state.width * .5f + 2;
	arena_half_size_y = render_state.height * .5f + 2;
	GetCursorPos(&Cursor);
	clr_scr(0x2e222f);
	int cur_y = (int)(-Cursor.y + arena_half_size_y);
	int cur_x = (int)(Cursor.x - arena_half_size_x);
	cur_x = clamp((int)(-arena_half_size_x + curd), cur_x, (int)(arena_half_size_x - curd));
	cur_y = clamp((int)(-arena_half_size_y + curd), cur_y, (int)(arena_half_size_y - curd));
	draw_arena_borders(arena_half_size_x, arena_half_size_y, 0xb2ba90);
	//draw_text("ESC", -91, 48, .3f, 0x7c3f58);
	if (pressed(BUTTON_ESC)) {
		exit(0);
	}
	//сама игра
	//меню
	if(current_gamemode == GM_MENU) {
		if (wtime > 0)wtime--;
		else wtime = 0;
		draw_number(amount, 175, -85);
		draw_file("menu", -160, 80);
		draw_file("name", -315, 260);
		draw_file("amount", -300, -60);
		draw_file("info", -634, -290);
		//draw_rect(0,0, 2, arena_half_size_y, 0xffffff);
		if (pressed(BUTTON_ENTER)) {
			health = 3;
			arrs = new list(amount);
			current_gamemode = GM_GAMEPLAY;
			cur_x = 0;
			cur_y = 0;
			wtime = 5;
		}
		if (pressed(BUTTON_UP)) {
			if (amount < 8) amount++;
		}
		if (pressed(BUTTON_DOWN)) {
			if (amount > 1) amount--;
		}
	}

	if (current_gamemode == GM_GAMEPLAY) {
		//draw_module(cur_x, cur_y, 1, *arrs);
		//if (arrs->stat()) {
		//	draw_file("solved", arena_half_size_x, arena_half_size_y);
		//}
		//else {
		//	draw_file("unsolved", arena_half_size_x + 8, arena_half_size_y + 15);
		//}
		if (wtime > 0)wtime--;
		else wtime = 0;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				draw_module(-arena_half_size_x + 2 + 321 * j + (j >= 2 ? 1 : 0), arena_half_size_y - 2 - 364 * i, i, j, *arrs);
			}
		}

		draw_file(arrs->ser() ? "serial1" : "serial2", -arena_half_size_x + 2, -arena_half_size_y - 2);
		for (int i = 0; i < 3; i++) {
			if (i < arrs->bat()) {
				draw_file("tbattery", -arena_half_size_x - 35, -60 * i);
			}
			else {
				draw_file("fbattery", -arena_half_size_x - 35, -60 * i);
			}
		}
		for (int i = 0; i < max_health; i++) {
			if (i < health) {
				draw_file("theart", arena_half_size_x + 2, -60 * i);
			}
			else {
				draw_file("fheart", arena_half_size_x + 2, -60 * i);
			}
		}

		if (cur_x < -arena_half_size_x + 323) {
			mod_x = 0;
		}
		else if (cur_x < -arena_half_size_x + 644) {
			mod_x = 1;
		}
		else if (cur_x < arena_half_size_x - 319) {
			mod_x = 2;
		}
		else {
			mod_x = 3;
		}

		if (cur_y > 0) {
			mod_y = 0;
		}
		else {
			mod_y = 1;
		}
		//draw_file("wall", -arena_half_size_x + 2 + 321 * mod_x + (mod_x >= 2 ? 1 : 0), arena_half_size_y - 2 - 364 * mod_y);
		
		process(cur_x, cur_y);
		//draw_rect((float)cur_x, (float)cur_y, curd, curd, 0xffffff);

		if (released(BUTTON_ENTER) and pos) {
			switch (type)
			{
			case 1:
				if(!arrs->pw(ind)->solved)
				a = arrs->pw(ind)->test(pos - 1);
				break;
			case 2:
				if(!arrs->pb(ind)->solved)
				a = arrs->pb(ind)->test(pos - 1);
				break;
			case 3:
				if (!arrs->pm(ind)->solved)
				a = arrs->pm(ind)->test(pos - 1);
				break;
			case 4:
				if (!arrs->ph(ind)->solved)
				a = arrs->ph(ind)->test(pos - 1);
				break;
			}
			if (a == 0) health--;
		}

		if (health == 0) {
			current_gamemode = GM_LOSE;
			wtime = 5;
		}

		if (arrs->stat()) {
			current_gamemode = GM_WIN;
			wtime = 5;
		}
	}

	if (current_gamemode == GM_LOSE) {
		if (wtime > 0)wtime--;
		else wtime = 0;
		if (released(BUTTON_ENTER) and !wtime) {
			current_gamemode = GM_MENU;
			wtime = 5;
		}
	}
	
	if (current_gamemode == GM_WIN) {
		if (wtime > 0)wtime--;
		else wtime = 0;
		if (released(BUTTON_ENTER)) {
			current_gamemode = GM_MENU;
			wtime = 5;
		}
	}
	draw_rect((float)cur_x, (float)cur_y, curd, curd, 0xffffff);
	//draw_rect((float)cur_x, (float)cur_y, curd, curd, 0xd24040);

	//курсор
	#if 0
		draw_number((int)cur_x, 0, 10, 4, 0xf9a875);
		draw_number((int)-cur_x, 0, 10, 4, 0xf9a875);
		draw_number((int)cur_y, 0, -10, 4, 0xf9a875);
		draw_number((int)-cur_y, 0, -10, 4, 0xf9a875);

		draw_number((int)arena_half_size_x, 0, 100, 4, 0xf9a875);
		draw_number((int)-arena_half_size_x, 0, 100, 4, 0xf9a875);
		draw_number((int)arena_half_size_y, 0, 70, 4, 0xf9a875);
		draw_number((int)-arena_half_size_y, 0, 70, 4, 0xf9a875);
	#endif
}