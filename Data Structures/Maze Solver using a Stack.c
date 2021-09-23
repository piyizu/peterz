#include <stdio.h>
#include <string.h>

#define A 10

/**
 * This program uses a stack to solve maze puzzles.
 * The default maze input should be like
 *  ##########
	#s       #
	#        #
	#        #
	#        #
	#  #######
	#    #####
	#  #######
	#       e#
	##########
 * Here '#' stands for wall block and 's' means starting point,
	'e' ending point.
   The solution marked the right path using '&'
   If no solution is found, it will prints 'No solution!'

   This program can be further optimised using recursion and a queue.
   BFS should be applied in such a problem. But as an exercise, it should only use stacks.
*/

typedef struct Position{
	int x, y;
	int dir; // used to store the next direction index for point (x, y)
} Position;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int main() {
	int Maze[A][A], MazeDontGo[A][A], Ans[A][A];
	Position Path[A*A], StartPoint, EndPoint;
	int PathTop = 0;

	for(int i = 0; i < A; ++i) {
		for(int j = 0; j < A; ++j) {
			char ch = getchar();
			if(ch == '#') {
				Maze[j][i] = 0;
				MazeDontGo[j][i] = 1;
			}
			else {
				Maze[j][i] = 1;
				MazeDontGo[j][i] = 0;
				if(ch == 's') {
					StartPoint.x = j;
					StartPoint.y = i;
				}
				else if(ch == 'e') {
					EndPoint.x = j;
					EndPoint.y = i;
				}
			}
		}
		getchar(); // clear newline character
	} //Statements above process the input

	Path[0].x = StartPoint.x;
	Path[0].y = StartPoint.y;
	Path[0].dir = 0;
	memset(Ans, 0, sizeof(Ans));
	Ans[StartPoint.x][StartPoint.y] = 1;

	while(PathTop >= 0) {
		if(Path[PathTop].x == EndPoint.x && Path[PathTop].y == EndPoint.y) {
			putchar('\n');
			for(int i = 0; i < A; ++i) {
				for(int j = 0; j < A; ++j) {
					if(Maze[j][i] == 0) putchar('#');
					else if(Ans[j][i]) putchar('&');
					else putchar(' ');
				}
				putchar('\n');
			}
			break;
		} // Code block above prints one found solution
		else {
			putchar('\n');
			for(int i = 0; i < A; ++i) {
				for(int j = 0; j < A; ++j) {
					if(Maze[j][i] == 0) putchar('#');
					else if(Ans[j][i]) putchar('&');
					else putchar(' ');
				}
				putchar('\n');
			}

			for(; Path[PathTop].dir < 4; ++Path[PathTop].dir) {
				if(Maze[Path[PathTop].x + dx[Path[PathTop].dir]][Path[PathTop].y + dy[Path[PathTop].dir]] 
					&& !MazeDontGo[Path[PathTop].x + dx[Path[PathTop].dir]][Path[PathTop].y + dy[Path[PathTop].dir]] 
					&& !Ans[Path[PathTop].x + dx[Path[PathTop].dir]][Path[PathTop].y + dy[Path[PathTop].dir]] ) {

					Path[PathTop+1].x = Path[PathTop].x + dx[Path[PathTop].dir];
					Path[PathTop+1].y = Path[PathTop].y + dy[Path[PathTop].dir];
					Path[PathTop+1].dir = 0;
					++PathTop;
					Ans[Path[PathTop].x][Path[PathTop].y] = 1;
					break; // Move on to the next position
				}
			}
			if(Path[PathTop].dir == 4) { 
				// If all directions have been tested and no solution is found, mark this point as 'Don't Go'.
				// Then move back in the path;
				Ans[Path[PathTop].x][Path[PathTop].y] = 0;
				MazeDontGo[Path[PathTop].x][Path[PathTop].y] = 1;
				--PathTop;
			}
		}
	}
	if(PathTop < 0) printf("No solution!\n");

	return 0;
}