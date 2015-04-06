#ifndef SAMEGAME_H
#define SAMEGAME_H

class SameGame{
	public:
		SameGame();


	void delete_group(int pos_x, int pos_y, int old_value, int new_value){
	    if ((pos_x < fil && pos_y < colum) && (pos_x>=0 && pos_y>=0)){
	        int value = tablero[pos_x][pos_y];

	        if(value == old_value)
	        {
	            tablero[pos_x][pos_y] = new_value;
	            delete_group(pos_x+1,pos_y,old_value,new_value);
	            delete_group(pos_x-1,pos_y,old_value,new_value);
	            delete_group(pos_x,pos_y+1,old_value,new_value);
	            delete_group(pos_x,pos_y-1,old_value,new_value);
	        }
	    }
	}

	bool find_next(int pos_x, int pos_y, int value){
	    int x1,y1,x2,y2,x3,y3,x4,y4;

	    x1 = pos_x + 1;
	    y1 = pos_y;

	    x2 = pos_x - 1;
	    y2 = pos_y;

	    x3 = pos_x;
	    y3 = pos_y + 1;

	    x4 = pos_x;
	    y4 = pos_y - 1;

	    if ((x1 < fil && y1 < colum) && (x1>=0 && y1>=0) && (tablero[x1][y1] == value)) return true;
	    if ((x2 < fil && y2 < colum) && (x2>=0 && y2>=0) && (tablero[x2][y2] == value)) return true;
	    if ((x3 < fil && y3 < colum) && (x3>=0 && y3>=0) && (tablero[x3][y3] == value)) return true;
	    if ((x4 < fil && y4 < colum) && (x4>=0 && y4>=0) && (tablero[x4][y4] == value)) return true;

	    return false;
	}


};

#endif // SAMEGAME_H 