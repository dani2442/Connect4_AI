#pragma once
#include <vector>
#include <iostream>

#define None 99
class array2D {
public:
	array2D(int r=6, int c=7):board(r*c),r(r),c(c) {}
	array2D(std::vector<int>& b,int r,int c) :board(b),r(r),c(c){}
	int MAX_DEPTH=8;
	static int m;

	void print() { 
		for (int i = r-1; i >= 0; i--) {
			for (int j = 0; j < c;j++) {
				std::cout << get(j, i) << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	int& get(const int& x,const int& y) { return board[x + y * c]; }
	void set(const int &x,const int &y,const int& val) { board[x + y * c] = val; }

	int _input(const int& x) {
		int y = 0;
		while (board[x + y * c] != 0) y++;
		return y;
	}

	int input(const int& x, const int& val) {
		int y = _input(x);
		board[x + y * c] = val;
		return y;
	}

	float _recurrence(int depth) {
		float sum1 = 0; int count1 = 0;
		if (depth > MAX_DEPTH || depth+m==c*r) return 0;
		float max = -None, min = None;
		for (int i = 0; i < c; i++) {
			if (depth + 1 + m == c * r || get(i,r-1)!=0) continue;
			if (check_new_move(i,1)) { return 1; }
			min = None;
			int y = input(i, 1);
			bool b_win2 = false;
			float sum2 = 0; int count2 = 0;
			for (int j = 0; j < c; j++) {
				if (get(j, r - 1) != 0) continue;
				else if (check_new_move(j, 2)) {
					b_win2 = true;
					break;
				}
				else {
					array2D new_board(board, r, c);
					new_board.input(j, 2);
					float r = new_board._recurrence(depth + 2);
					if (r==-1) {
						b_win2 = true;
						break;
					}
					else if(r<min) min = r;
					sum2 += r; count2++;
				}
			}
			set(i, y, 0);
			if (b_win2) {
				sum1 += -1;
			}
			else {
				sum2 /= count2;
				if (sum2 == -1) return -1;
				else if (max < sum2) max = sum2;
				sum1 += sum2;
			}
			count1++;
		}
		return sum1/count1;
	}

	int recurrence() {
		int index = -1;
		double min = None;
		for (int i = 0; i < c; i++) {
			if (get(i, r - 1) != 0) continue;
			if (check_new_move(i, 2)) { return i; }
			else {
				array2D a(board,r,c);
				a.input(i,2);
				double val=a._recurrence(1);
				if (val < min) {
					min = val;
					index = i;
				}
			}
		}
		return index;
	}

	int start_game() {
		array2D::m = 0;
		while (array2D::m < r * c) {
			int x,r;
			if (array2D::m % 2 == 0) {
				std::cin >> x;
				r = check_new_move(x - 1, 1);
				input(x-1, 1);
			}
			else {
				x=recurrence();
				r = check_new_move(x, 2);
				input(x, 2);
			}			
			print();
			if (r) return m % 2 + 1;
			array2D::m++;
		}

	}

	int check_new_move(int x, int val) {
		int y = _input(x);
		int i=0, j = 0;
		while (x + i + 1 < c && get(x + i + 1,y) == val) i++;
		while (0 <= x - j - 1 && get(x - j - 1, y) == val) j++;
		if (i + j + 1 >= 4) return 1;
		i = 0; j = 0;
		while (y + 1 + i < r && get(x,y + i + 1) == val) i++;
		while (0 <= y - 1 - j && get(x, y - 1 - j) == val) j++;
		if (i + j + 1 >= 4) return 1;
		i = 0; j = 0;
		while (0 <= x - 1 - i && y + 1 + i < r && get(x - i - 1, y + 1 + i) == val) i++;
		while (x + 1 + j < c && 0 <= y - 1 - j && get(x + 1 + j, y - 1 - j) == val) j++;
        if (i + j + 1 >= 4) return 1;
		i = 0; j = 0;
		while (x + 1 + i < c && y + 1 + i < r && get(x + i + 1, y + 1 + i) == val) i++;
		while (0 <= x - 1 - j && 0 <= y - 1 - j && get(x-1-j,y - 1 - j) == val) j++;
        if (i + j + 1 >= 4) return 1;
		return 0;
	}
private:
	std::vector<int> board;
	int r, c;
};

int array2D::m = 0;