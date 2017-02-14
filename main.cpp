#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>

#define MAXR 1000
#define MAXC 1000
#define OBSTC 1
#define KUTSAL 2

struct spot {
	short x;
	short y;
	int F;
	int H;
	int G;
	struct spot* parent_;

	bool operator==(spot& s) {
		return s.x == x && s.y == y;
	}
};

bool comparator(spot s1, spot s2);
bool findmein(std::vector<spot>&vec, spot& s2);

int main()
{
	bool isFound = false;
	int satir = 2, sutun = 2;
	scanf("%d %d", &satir, &sutun);

	int arr[MAXR][MAXC] = { { 0 } };
	bool closed_list[MAXR][MAXC] = { { false } };
	std::vector<spot> open_list;
	spot kutsal = { 0,0,0,0,0,NULL };
	spot startpoint = { 0,0,0,0,0,NULL };
	int result = 0;

	for (size_t irow = 0; irow < satir; irow++) {
		scanf(" %d", &arr[irow][0]);
		if (arr[irow][0] == KUTSAL) {
			startpoint.x = irow;
			startpoint.y = 0;
		}
		for (size_t jcolmn = 1; jcolmn < sutun; jcolmn++) {
			scanf(" %d", &arr[irow][jcolmn]);
			if (arr[irow][jcolmn] == KUTSAL) {
				startpoint.x = irow;
				startpoint.y = jcolmn;
			}
		}
	}

	open_list.push_back(kutsal);
	int gc = 1;
	do {
		std::sort(open_list.begin(), open_list.end(), comparator);
		spot curr = { open_list[0].x, open_list[0].y, open_list[0].F, open_list[0].H, open_list[0].G, open_list[0].parent_ };

		closed_list[curr.x][curr.y] = true;
		open_list.erase(open_list.begin());//delete curr from open list

		if (closed_list[startpoint.x][startpoint.y]) {
			isFound = true;
			while (!(curr.x == 0 && curr.y == 0)) {

				if (curr.parent_->x == 0 && curr.parent_->y == 0) {
					if (curr.x == 1 && curr.y == 0)
						result++;
				}

				spot tempt = curr;
				curr = *curr.parent_;

				if (curr.parent_ != NULL &&  std::abs(tempt.x - curr.parent_->x) == 1 && 1 == std::abs(tempt.y - curr.parent_->y)) {
					result++;
				}
			}

			break;
		}

		std::vector<spot> adj_spots;
		if ((curr.x + 1) < satir && arr[curr.x + 1][curr.y] != OBSTC) {
			adj_spots.push_back({ curr.x + 1, curr.y , 0,0,0, NULL });
		}

		if ((curr.x - 1) >= 0 && arr[curr.x - 1][curr.y] != OBSTC) {
			adj_spots.push_back({ curr.x - 1, curr.y , 0,0,0, NULL });
		}

		if ((curr.y + 1) < sutun && arr[curr.x][curr.y + 1] != OBSTC) {
			adj_spots.push_back({ curr.x, curr.y + 1 , 0,0,0, NULL });
		}

		if ((curr.y - 1) >= 0 && arr[curr.x][curr.y - 1] != OBSTC) {
			adj_spots.push_back({ curr.x, curr.y - 1 , 0,0,0, NULL });
		}

		std::vector<spot>::iterator it = adj_spots.begin();
		while (it != adj_spots.end()) {

			if (closed_list[it->x][it->y]) {
				it++;
				continue;
			}

			if (!findmein(open_list, *it)) {

				if (it->x == 0 && it->y == 3)
					std::cout << "";

				it->G = curr.G + 1;
				it->F = it->G + std::abs(startpoint.x - it->x) + std::abs(startpoint.y - it->y);
				it->parent_ = new spot{curr.x, curr.y, curr.F, curr.H, curr.G, curr.parent_};

				open_list.push_back((*it));
			}
			else {
				if (curr.G + 1 >= it->G) {
					it->G = gc;
					it->parent_ = new spot{curr.x, curr.y, curr.F, curr.H, curr.G, curr.parent_};
				}
			}

			it++;
		}

		gc++;

	} while (!open_list.empty());


	if (!isFound)
		std::cout << -1;
	else
		std::cout << result << std::endl;

	return 0;
}

bool comparator(spot s1, spot s2) {
	return s1.F < s2.F;
}

bool findmein(std::vector<spot>&vec, spot& s2) {
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec.at(i) == s2)	return true;
	}
	return false;
}


