/* Render.cpp */

#include "Render.h"
#include <math.h>

/** Operator Empat Sekawan **/
Render::Render():screen(), terminal() {
/* Default Constructor */
}

Render::Render(const Render &R) {
/* Copy Constructor */	
	
}

Render::~Render() {

}

/**& getter and Setter **/
Canvas& Render::getScreen() {
	return (this->screen);
}

int& Render::getAssetCount() {
	return (this->asset_count);
}

void Render::drawPoint(Point P, Color C){
	if(P.getAbsis() + offset_x >= screen.getXRes() || P.getAbsis() - offset_x < 0 || P.getOrdinat() + offset_y >= screen.getYRes() || P.getOrdinat() - offset_y < 0)
		return;
	if(screen.getColorDepth() == 16){
		// x * 2 as every pixel is 2 consecutive bytes
		unsigned int pix_offset = (P.getAbsis() + offset_x) * 2 + (P.getOrdinat() + offset_y) * screen.getLineLength();
		//unsigned short c = ((r / 8) << 11) + ((g / 4) << 5) + (b / 8);
		unsigned short color = ((C.getRed() / 8) * 2048) + ((C.getGreen() / 4) * 32) + (C.getBlue() / 8);
		// write 2 bytes at once
		if(*((unsigned short*)(screen.getFrameBuffer() + pix_offset)) != color){
			*((unsigned short*)(screen.getFrameBuffer() + pix_offset)) = color;
		}
	}
	else if(screen.getColorDepth() == 24){
		// x * 3 as every pixel is 3 consecutive bytes
		unsigned int pix_offset = (P.getAbsis() + offset_x) * 3 + (P.getOrdinat() + offset_y) * screen.getLineLength();
		// now this is about the same as 'fbp[pix_offset] = value'
		if(*((char*)(screen.getFrameBuffer() + pix_offset)) != C.getBlue() || *((char*)(screen.getFrameBuffer() + pix_offset + 1)) != C.getGreen() && *((char*)(screen.getFrameBuffer() + pix_offset + 2)) != C.getRed()){
			*((char*)(screen.getFrameBuffer() + pix_offset)) = C.getBlue();
			*((char*)(screen.getFrameBuffer() + pix_offset + 1)) = C.getGreen();
			*((char*)(screen.getFrameBuffer() + pix_offset + 2)) = C.getRed();
		}
	}
	else if(screen.getColorDepth() == 32){
		 // x * 2 as every pixel is 2 consecutive bytes
		unsigned int pix_offset = (P.getAbsis() + offset_x) * 4 + (P.getOrdinat() + offset_y) * screen.getLineLength();
		unsigned int color = (C.getAlpha() << 24) + (C.getRed() << 16) + (C.getGreen() << 8) + C.getBlue();
		// write 4 bytes at once
		if(*((unsigned int*)(screen.getFrameBuffer() + pix_offset)) != color){
			*((unsigned int*)(screen.getFrameBuffer() + pix_offset)) = color;
		}
	}
}

/** Function and Procedure **/
void Render::drawLineLow(int x0, int y0, int x1, int y1, Color C){
	int dx = x1 - x0;
	int dy = y1 - y0;
  	int yi = 1;
  	if(dy < 0){
		yi = -1;
		dy = -1 * dy;
	}
  	int D = 2 * dy - dx;
  	int y = y0;
	for(int x = x0; x <= x1; ++x){
		drawPoint(Point(x, y), C);
		if(D > 0){
			y = y + yi;
			D = D - 2 * dx;
		}
		D = D + 2 * dy;
	}
}

void Render::drawLineHigh(int x0, int y0, int x1, int y1, Color C){
	int dx = x1 - x0;
	int dy = y1 - y0;
  	int xi = 1;
  	if(dx < 0){
		xi = -1;
		dx = -1 * dx;
	}
  	int D = 2 * dx - dy;
  	int x = x0;
	for(int y = y0; y <= y1; ++y){
		drawPoint(Point(x, y), C);
		if(D > 0){
			x = x + xi;
			D = D - 2 * dy;
		}
		D = D + 2 * dx;
	}
}

void Render::drawLine(Line L, Color C) {
	int x0 = L.getP1().getAbsis();
	int x1 = L.getP2().getAbsis();
	int y0 = L.getP1().getOrdinat();
	int y1 = L.getP2().getOrdinat();
	if(abs(y1 - y0) < abs(x1 - x0)){
		if(x0 > x1){
			drawLineLow(x1, y1, x0, y0, C);
		}
		else{
			drawLineLow(x0, y0, x1, y1, C);
		}
	}
	else{
		if(y0 > y1){
			drawLineHigh(x1, y1, x0, y0, C);
		}
		else{
			drawLineHigh(x0, y0, x1, y1, C);
		}
	}
}

void Render::loadAsset(char *filename){
	int shape_count, line_count;
	char asset_type;
	FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        perror("Error opening the file.\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fp, "%d", &shape_count);
	//std::cout << shape_count << std::endl << "\r";
	for(int i = 0; i < shape_count; ++i){
		int r, g, b, a;
		fscanf(fp, "\n%c", &asset_type);
		fscanf(fp, "%d", &line_count);
		//std::cout << asset_type << ", " << line_count << std::endl << "\r";
		fscanf(fp, "%d", &a);
		fscanf(fp, "%d", &r);
		fscanf(fp, "%d", &g);
		fscanf(fp, "%d", &b);
		//std::cout << a << ", " << r << ", " << g << ", " << b << std::endl << "\r";
		Color Outline(a, r, g, b);
		// fscanf(fp, "%d", &a);
		// fscanf(fp, "%d", &r);
		// fscanf(fp, "%d", &g);
		// fscanf(fp, "%d", &b);
		//std::cout << a << ", " << r << ", " << g << ", " << b << std::endl << "\r";
		// Color C(a, r, g, b);
		if(asset_type == 'S'){
			int x0, x1, y0, y1;
			shapes[asset_count].setAmount(line_count);
			for(int j = 0; j < line_count; ++j){
				fscanf(fp, "%d", &x0);
				fscanf(fp, "%d", &y0);
				fscanf(fp, "%d", &x1);
				fscanf(fp, "%d", &y1);
				//std::cout << x0 << ", " << y0 << ", " << x1 << ", " << y1 << std::endl << "\r";
				shapes[asset_count].addLine(Line(Point(x0, y0), Point(x1, y1)));
			}
			// fills[asset_count] = C;
			outlines[asset_count] = Outline;
		}
		asset_count++;
		//std::cout << std::endl << "\r";
	}
    fclose(fp);
	
}

void Render::drawAsset(int idx, int x, int y){
	drawFullShape(shapes[idx], fills[idx], outlines[idx], x, y);
}

void Render::drawFullShape(Shape S, Color C, Color Outline, int x_start, int y_start) {
	/* if(!S.isClosed()){
		return;
	} */
	for(int i = 0; i < S.getNeff(); ++i){
		Point P_1(S.getLineAt(i).getP1().getAbsis()+x_start, S.getLineAt(i).getP1().getOrdinat()+y_start);
		Point P_2(S.getLineAt(i).getP2().getAbsis()+x_start, S.getLineAt(i).getP2().getOrdinat()+y_start);

		drawLine(Line(P_1, P_2), Outline);
	}
	// Line L = S.getExtremeLine();
	// Point P1(0, 0);
	// Point P2(700, 700);
	// Line L1(P1, P2);
	//std::cout << L.getP1().getAbsis() << ", " << L.getP1().getOrdinat() << std::endl << "\r";
	//std::cout << L.getP2().getAbsis() << ", " << L.getP2().getOrdinat() << std::endl << "\r";
// 	for(int y = L.getP1().getOrdinat() + 1 +y_start; y < L.getP2().getOrdinat()+y_start && y < screen.getYRes(); ++y){
// 		bool inside = false;
// 		int meetLine = 0;
// 		for(int x = L.getP1().getAbsis()+x_start; x < L.getP2().getAbsis()+x_start && x < screen.getXRes(); ++x){
// 			if(meetLine == 1){
// 				inside = true;
// 			}
// 			if(screen.getColorDepth() == 16){
// 				// x * 2 as every pixel is 2 consecutive bytes
// 				unsigned int pix_offset = (x + offset_x) * 2 + (y + offset_y) * screen.getLineLength();
// 				unsigned short out_color = ((Outline.getRed() / 8) * 2048) + ((Outline.getGreen() / 4) * 32) + (Outline.getBlue() / 8);
// 				if(*((unsigned short*)(screen.getFrameBuffer() + pix_offset)) == out_color){
// 					meetLine++;
// 				}
// 			}
// 			else if(screen.getColorDepth() == 24){
// 				// x * 3 as every pixel is 3 consecutive bytes
// 				unsigned int pix_offset = (x + offset_x) * 3 + (y + offset_y) * screen.getLineLength();
// 				if(*((char*)(screen.getFrameBuffer() + pix_offset)) == Outline.getBlue() && *((char*)(screen.getFrameBuffer() + pix_offset + 1)) == Outline.getGreen() && *((char*)(screen.getFrameBuffer() + pix_offset + 2)) == Outline.getRed()){
// 					meetLine++;
// 				}
// 			}
// 			else if(screen.getColorDepth() == 32){
// 				// x * 2 as every pixel is 4 consecutive bytes
// 				unsigned int pix_offset = (x + offset_x) * 4 + (y + offset_y) * screen.getLineLength();
// 				unsigned int out_color = (Outline.getAlpha() << 24) + (Outline.getRed() << 16) + (Outline.getGreen() << 8) + Outline.getBlue();
// 				if(*((unsigned int*)(screen.getFrameBuffer() + pix_offset)) == out_color){
// 					meetLine++;
// 				}
// 			}
// 			if(meetLine == 2){
// 				break;
// 			}
// 			if(inside){
// 				drawPoint(Point(x, y), C);
// 			}
// 		}
// 	}
}

void Render::drawEmptyShape(Shape S, Color Outline){
	for(int i = 0; i < S.getNeff(); ++i){
		drawLine(S.getLineAt(i), Outline);
	}
}

void Render::clearScreen(){
	memset(screen.getFrameBuffer(), 0, (screen.getColorDepth() / 8 * screen.getXRes() * screen.getYRes()));
}

void Render::clearArea(int x, int x_size, int y, int y_size){
	for(int j = y; j < y + y_size; ++j)
		memset(screen.getFrameBuffer() + j * screen.getLineLength() + screen.getColorDepth() / 8 * x, 0, screen.getColorDepth() / 8 * x_size);
}

void Render::bingkai(){
	Color c = Color(0, 255, 255, 255);
	int pad = 0;

	Point P1 = Point(P_start.getAbsis()-pad,P_start.getOrdinat()-pad);
	Point P2 = Point(P_finish.getAbsis()+pad,P_start.getOrdinat()-pad);
	Point P3 = Point(P_finish.getAbsis()+pad,P_finish.getOrdinat()+pad);
	Point P4 = Point(P_start.getAbsis()-pad,P_finish.getOrdinat()+pad);

	drawLine(Line(P1, P2), c);
	drawLine(Line(P2, P3), c);
	drawLine(Line(P3, P4), c);
	drawLine(Line(P4, P1), c);
}

void Render::skala_elements(int before, int after){
	// std::cout<<shapes[0].getLineAt(2).getP1().getAbsis() ;
	// std::cout<<( (shapes[0].getLineAt(2).getP1().getAbsis())/before*after);
	for(int i = 0; i < asset_count; ++i){
        for(int j = 0; j < shapes[i].getNeff(); j++){
			Line new_line = Line(
				Point(
					(shapes[i].getLineAt(j).getP1().getAbsis())/before*after, 
					(shapes[i].getLineAt(j).getP1().getOrdinat())/before*after), 
				Point(
					(shapes[i].getLineAt(j).getP2().getAbsis())/before*after, 
					(shapes[i].getLineAt(j).getP2().getOrdinat())/before*after)
				);
			shapes[i].setLineAt(j, new_line);
		}
    }
}

int Render::skala(int before, int after){
	int original_x_finish = screen.getXRes() - 10;
	int original_y_finish = screen.getYRes() - 10;
	int s;

	// Getting and validating new finish point
	int y_new = (P_finish.getOrdinat() - P_start.getOrdinat())/before*after + P_start.getOrdinat();
	int x_new = (P_finish.getAbsis() - P_start.getAbsis())/before*after + P_start.getAbsis();
	if ((y_new > original_y_finish) || (x_new > original_x_finish)) {
		// do nothing
		return 1;
	}
	else {
		// updating Render condition
		P_finish.setAbsis(x_new);
		P_finish.setOrdinat(y_new);

		clearScreen();

		skala_elements(before, after);
		bingkai();
		for(int i = 0; i < asset_count; i++){
			drawAsset(i, P_start.getAbsis(), P_start.getOrdinat());
		}
		return 0;
	}
}

void Render::translate_elements(int h, int v) {
	for(int i = 0; i < asset_count; i++){
        for(int j = 0; j < shapes[i].getNeff(); j++){
			Line new_line = Line(
				Point(
					(shapes[i].getLineAt(j).getP1().getAbsis() + h), 
					(shapes[i].getLineAt(j).getP1().getOrdinat() + v)), 
				Point(
					(shapes[i].getLineAt(j).getP2().getAbsis() + h), 
					(shapes[i].getLineAt(j).getP2().getOrdinat() + v))
				);
			shapes[i].setLineAt(j, new_line);
			// std::cout<< (shapes[i].getLineAt(j).getP1().getAbsis() + h) << " " << (shapes[i].getLineAt(j).getP1().getOrdinat() + v) << "...";
		}
    }
}

void Render::translate(int h, int v){
	// Getting and validating new horizontal position
	int x_start_new = P_start.getAbsis() + h;
	int x_finish_new = P_finish.getAbsis() + h;
	if (x_start_new < 10) {
		x_start_new = 10;
		x_finish_new = P_finish.getAbsis() + (x_start_new - P_start.getAbsis());
	}
	else if (x_finish_new > screen.getXRes()-10){
		x_finish_new = screen.getXRes()-10;
		x_start_new = P_start.getAbsis() + (x_finish_new - P_finish.getAbsis());
	}

	// Getting and validating new vertical position
	int y_start_new = P_start.getOrdinat() + v;
	int y_finish_new = P_finish.getOrdinat() + v;
	if (y_start_new < 10) {
		y_start_new = 10;
		y_finish_new = P_finish.getOrdinat() + (y_start_new - P_start.getOrdinat());
	}
	else if (y_finish_new > screen.getYRes()-10){
		y_finish_new = screen.getYRes()-10;
		y_start_new = P_start.getOrdinat() + (y_finish_new - P_finish.getOrdinat());
	}

	if ((x_start_new == P_start.getAbsis()) && (y_start_new == P_start.getOrdinat())) {
		// do nothing
		// because the position is the same as before
		// std::cout<<x_start_new << " " << y_start_new <<std::endl<<"\r";
	}
	else {
		P_start.setAbsis(x_start_new);
		P_start.setOrdinat(y_start_new);
		P_finish.setAbsis(x_finish_new);
		P_finish.setOrdinat(y_finish_new);

		// NANTI DI SINI UPDATE SEMUA ELEMEN

		clearScreen();
		
		// translate_elements(h, v);
		bingkai();
		for(int i = 0; i < asset_count; i++){
			drawAsset(i, P_start.getAbsis(), P_start.getOrdinat());
		}
	}
}

void Render::map(){
	clearScreen();
	bingkai();
	for(int i = 0; i < asset_count; ++i){
        drawAsset(i, P_start.getAbsis(), P_start.getOrdinat());
    }
	int s = 10; // Skala
	for(;;){
        if(terminal.getIsInput() == (int)State::RECEIVED){
			char input = terminal.getInput();
            switch (input){
				case 'w': // up
					translate(0, -10);
					break;
                case 'a': // left
					translate(-10, 0);
                    break;
                case 's': // down
					translate(0, 10);
                    break;
				case 'd': // right
					translate(10, 0);
                    break;
				case 'i': // smaller
					s--;
					if (s < 1) {
						s = 1;
					}
					else {
						if(skala(s+1, s)) {
							s++;
						}
					}
                    break;
				case 'o': // bigger
					s++;
					if (s > 10) {
						s = 10;
					}
					else {
						if(skala(s-1, s)) {
							s--;
						}
					}
                    break;
                default:
                    break;
            }
            terminal.setIsInput(State::WAITING);
        }
        else if(terminal.getIsInput() == (int)State::STOP){
            terminal.exit();
            break;
        }
    }
}

void Render::heli(){
	int coor_x = 850;
	Point P(230, 230);
	for(;;){
		clearScreen();
		for(int i = 0; i < 4; ++i){
				shapes[i].rotateShape(P, 20.0);
		}
		for(int i = 0; i < asset_count; ++i){
			drawAsset(i, coor_x, screen.getYRes()/4);
		}
		for (int i = 0; i < 900000; i++) {}

		if (coor_x >= 5) {
			coor_x -= 1;
		}
		else {
			coor_x = 850;
		}

        if(terminal.getIsInput() == (int)State::RECEIVED){
			char input = terminal.getInput();
            terminal.setIsInput(State::WAITING);
        }
        else if(terminal.getIsInput() == (int)State::STOP){
            terminal.exit();
            break;
        }
    }
}

void Render::doMotion(){
	clearScreen();
	int x_ship = screen.getXRes() / 3, y_ship = screen.getYRes() / 2, x_plane = screen.getXRes() - 300, y_plane = screen.getYRes() / 8;
	int x_bullet, y_bullet;
	bool bullet = false, ship = true;
	for(int i = 1; i < 7; ++i){
        drawAsset(i, x_ship, y_ship);
    }
	for(int i = 7; i < asset_count; ++i){
        drawAsset(i, x_plane, y_plane);
    }
	for(;;){
		if(bullet){
			clearArea(x_bullet, 20, y_bullet, 20);
			y_bullet -= 10;
			drawAsset(0, x_bullet, y_bullet);
		}
		clearArea(x_plane, 400, y_plane, 250);
		x_plane--;
		if(x_plane < 0){
			x_plane = screen.getXRes() - 300;
		}
		if(y_bullet < 0){
			clearArea(x_bullet, 20, 0, 20);
			bullet = false;
		}
		for(int i = 7; i < asset_count; ++i){
				drawAsset(i, x_plane, y_plane);
		}
        if(terminal.getIsInput() == (int)State::RECEIVED){
            clearArea(x_ship - 50, 450, y_ship - 50, 350);
			char input = terminal.getInput();
            switch (input)
            {
				case 'B':
					if(!bullet){
						bullet = true;
						x_bullet = x_ship + 150;
						y_bullet = y_ship - 30;
					}
					break;
                case 'C':
					ship = true;
                    x_ship += 10;
                    break;
                case 'D':
				ship = true;
                    x_ship -= 10;
                    break;
                default:
                    break;
            }
			if(ship){
				for(int i = 1; i < 7; ++i){
					drawAsset(i, x_ship, y_ship);
				}
			}
            terminal.setIsInput(State::WAITING);
        }
        else if(terminal.getIsInput() == (int)State::STOP){
            terminal.exit();
            break;
        }
    }
}

Input& Render::getTerminal(){
	return terminal;
}

Color Render::getBGColor(){
	return BACKGROUND;
}

void Render::doRotate(){
	float degree = 10;
	clearScreen();
	for(int i = 0; i < asset_count; ++i){
		drawAsset(i, 0, 0);
	}
	Point P(30, 30);
	for(;;){
		if(terminal.getIsInput() == (int)State::RECEIVED){
			char input = terminal.getInput();
            switch (input)
            {
				case 'a':
					degree = 10;
					break;
                case 'd':
                    degree = -10;
                    break;
                default:
                    break;
            }
            for(int i = 0; i < asset_count; ++i){
				shapes[i].rotateShape(P, degree);
			}
			clearScreen();
			for(int i = 0; i < asset_count; ++i){
				drawAsset(i, 0, 0);
			}
            terminal.setIsInput(State::WAITING);
        }
        else if(terminal.getIsInput() == (int)State::STOP){
            terminal.exit();
            break;
        }
	}
}