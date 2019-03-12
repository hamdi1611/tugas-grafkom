/* Render.h */

#ifndef _RENDER_H_
#define _RENDER_H_

#include "Canvas.h"
#include "Shape.h"
#include "Line.h"
#include "Point.h"
#include "Color.h"
#include "Input.h"

class Render {
	private:
		const Color BACKGROUND = Color(0, 0, 0, 0);
		Canvas screen; // Screen size
		Input terminal;
		bool isColor = false;
		Shape shapes[100];
		Color fills[100];
		Color outlines[100];
		int asset_count = 0;
		Point Pview = Point(10, 60);
		Point P_start  = Point(10, 10);
		Point P_finish = Point(1010, 710);
		void drawLineLow(int x0, int y0, int x1, int y1, Color C);
		void drawLineHigh(int x0, int y0, int x1, int y1, Color C);
		void drawLineLowNoLimit(int x0, int y0, int x1, int y1, Color C);
		void drawLineHighNoLimit(int x0, int y0, int x1, int y1, Color C);
	public:
		/* Operator Empat Sekawan */
		Render();
		Render(const Render &R);
		~Render();
		/*& getter and Setter */
		Canvas& getScreen();
		int& getAssetCount();
		void resetAssetCount();
		/* Function and Procedure */
		void drawPoint(Point P, Color C);
		void drawPointNoLimit(Point P, Color C);
		void drawLine(Line L, Color C);
		void drawLineNoLimit(Line L, Color C);
		void loadAsset(char *filename);
		void drawAll();
		void drawAsset(int idx, int x_start, int y_start);
		void doMotion();
		void bingkai();
		void skala_elements(int before, int after);
		int skala(int before, int after);
		void translate_elements(int h, int v);
		void translate(int h, int v);
		bool isOutOfView(int i);
		void map();
		void heli();
		void drawFullShape(Shape S, Color C, Color Outline, int x_start, int y_start);
		void drawEmptyShape(Shape S, Color Outline);
		void clearScreen();	
		void clearArea(int x, int x_size, int y, int y_size);
		Input& getTerminal();
		Color getBGColor();
		bool getIsColor();
		bool changeIsColor();
		void showMenu(int menu_option, bool isMenu);
};

#endif