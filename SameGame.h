
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
#include <utility>

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

		vector< vector<pair<int,int> > > posits;

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

		int get_fil(){return fil;}
	int get_colum(){return colum;}
	int** get_table(){return tablero;}

	void delete_pos(int x,int y)
	{
		mark_position(fil-1-x,y);
	}

	bool get_empty()
	{
		return is_Empty;
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

	bool mark_position(int pos_x, int pos_y){
	    int value = tablero[pos_x][pos_y];
		//int value = tablero[fil-1-pos_x][pos_y];
	    if (value != 0){
	        if (find_next(pos_x,pos_y,value)){
	            delete_group(pos_x, pos_y, value, 0);
	            dropColumm();
	            select_col();
	            return true;
	        }
	    }
	    return false;
	}

	void drop(int pos_x, int pos_y){
	    if ((pos_x < fil && pos_y < colum) && (pos_x>=0 && pos_y>=0)){
	        int value = tablero[pos_x][pos_y];
	        if (value != 0){
	            tablero[pos_x][pos_y] = 0;
	            p_drop.push(value);
	            is_Empty = 1;
	        }

	        drop(pos_x+1,pos_y);

	        if (!p_drop.empty()){
	            tablero[pos_x][pos_y] = p_drop.top();
	            p_drop.pop();
	        }
	    }
	}

	void dropColumm(){
	    for (int i = 0; i < colum;i++){
	        drop(0,i);
	        if (is_Empty == 0){
	            col_empty.push_back(i);
	        }
	        is_Empty = 0;
	    }
	}

	void free_Colum(int pos_x, int pos_y){
	    if ((pos_x < fil && pos_y < colum) && (pos_x>=0 && pos_y>=0)){
	        int value = tablero[pos_x][pos_y];
	        tablero[pos_x][pos_y] = 0;
	        p_free.push(value);
	        free_Colum(pos_x,pos_y+1);

	        tablero[pos_x][pos_y-1] = p_free.top();
	        p_free.pop();
	    }
	}

	void select_col(){
	    if (!col_empty.empty()) {
	        sort(col_empty.begin(),col_empty.end());

	        for(int i = col_empty.size()-1; i >= 0; i--){
	            for(int j = 0; j < fil; j++){
	                free_Colum(j,col_empty[i]+1);
	            }
	            col_actives--;
	        }
	        col_empty.clear();
	    }
	}

	void show(){
	    for (int i = 0; i < fil;i++){
	        for(int j = 0; j < colum; j++)
	            cout << tablero[i][j] << " ";
	        cout << endl;
	    }
	    cout << endl;
	}

	void show_pos()
	{
		for (int i = 0; i < fil;i++)
		{
	        cout<<fil-1-i<<" | ";
	        for(int j = 0; j < colum; j++)
	            cout << tablero[i][j] << " ";
	        cout << endl;
	    }
	    cout<<"--+";
	    for (int i = 0; i < colum; ++i)
	       	cout<<"--";
	    cout<<"-"<<endl;
	    cout<<"  | ";
	    for (int i = 0; i < colum; ++i)
	       	cout<<i<<" ";

	    cout << endl<<endl;
	}

	bool if_win()
	{
		if(tablero[fil-1][0]!=0)
			return false;
		return true;
	}

	bool if_lose()
	{
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
		return true;
	}

	bool if_end()
	{
		if(if_win())
		{
			cout<<"you win"<<endl;
			return true;
		}
		if(if_lose())
		{
			cout<<"you lose"<<endl;
			return true;
		}
		return false;
	}

	void lets_play()
	{
		cout<<"Completa hasta llegar a cero."<<endl;
		show_pos();
	    while(!get_empty() && !if_end())
	    {
	        int a,b;
	        cin>>a;
	        cin>>b;
	        delete_pos(a,b);
	        show_pos();
	    }
	}

	void print_solutions()
	{
		for (int i = 0; i < posits.size(); ++i)
		{
			for (int j = 0; j < posits[i].size(); ++j)
				cout<<posits[i][j].first<<","<<posits[i][j].second<<" ";
			cout<<endl;
		}
	}

	void solutions()
	{
		vector<pair<int,int> > posiciones;
		generate_options(posiciones,tablero);
		cout<<posits.size()<<endl;
		print_solutions();
	}

	void generate_options(vector<pair<int,int> > positions, int** table)
	{
		SameGame same(table,fil,colum);
		//same.show_pos();
		
		if(same.if_win())
		{	
			posits.push_back(positions);
			cout<<"-------------------------------------"<<endl;
		}
		if (!same.if_lose())
		for (int i = 0; i < fil; ++i)
		{
			for (int j = 0; j < colum; ++j)
			{
				if(same.get_table()[i][j]!=0)
				{
					SameGame tmp=same;
					if(tmp.mark_position(i,j))
					{
						pair<int,int> pos(fil-1-i,j);
						positions.push_back(pos);
						vector<pair<int,int> > positions2=positions;
						
						cout<<fil-1-i<<" "<<j<<endl;
						generate_options(positions2,tmp.get_copy_table());
					}
				}
			}
		}
	}

};

#endif // SAMEGAME_H