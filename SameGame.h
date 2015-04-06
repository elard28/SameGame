<<<<<<< HEAD
#ifndef SAMEGAME_H
#define SAMEGAME_H

#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

class SameGame{
	private:
		int fil;
		int colum;

		int **tablero;
		int col_actives;

		stack<int> p_drop,p_free;
		vector<int> col_empty;
		bool is_Empty;

	public:
		SameGame(){};

		SameGame(int** mat, int f, int c)
		{
			fil=f;
			colum=c;
			col_actives = colum;
			is_Empty = 0;

			tablero=mat;
		}

		SameGame(char *txt)
		{
			fil=0;
			colum=0;
			get_text(txt);
		}

		void get_text(char *txt)
		{
			ifstream in("matrix.txt");
		    string str;
		    vector<int> mat;

		    while(getline(in,str))
		    {
		        char *chain=new char[str.length()+1];
		        strcpy(chain,str.c_str());

		        char *token=strtok(chain," ");
		        while(token!=NULL)
		        {
		            mat.push_back(atoi(token));
		            token=strtok(NULL," ");
		        }
		        fil++;
		    }

		    colum=mat.size()/fil;

		    tablero=new int*[fil];
		    for (int i = 0; i < fil; ++i)
		    {
		        tablero[i]=new int[colum];
		        for (int j = 0; j < colum; ++j)
		            tablero[i][j]=mat[(i*colum)+j];
		    }
		}

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

	void mark_position(int pos_x, int pos_y){
	    int value = tablero[pos_x][pos_y];
		//int value = tablero[fil-1-pos_x][pos_y];
	    if (value != 0){
	        if (find_next(pos_x,pos_y,value)){
	            delete_group(pos_x, pos_y, value, 0);
	            dropColumm();
	            select_col();
	        }
	    }
	}









	bool if_win()
	{
		for (int i = 0; i < fil; ++i)
		{
			for (int j = 0; j < colum; ++j)
			{
				if(tablero[i][j]!=0)
					return false;
			}
		}
		cout<<"you win"<<endl;
		return true;
	}

	bool if_end()
	{
		if(if_win())
			return true;
		for (int i = 0; i < fil; ++i)
		{
			for (int j = 0; j < colum; ++j)
			{
				if(tablero[i][j]!=0)
				{
					if(find_next(i,j,tablero[i][j]))
						return false;
				}
			}
		}
		cout<<"you lose"<<endl;
		return true;
	}

};

