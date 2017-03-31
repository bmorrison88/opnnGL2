//The GridPoint class is the primary point structure of this program.
//Instead of referencing a three dimensional array of booleans, this class
//operates on that same principle but adds member functions and state variables
//necessary to draw the path.


#ifndef GRIDPOINT_H
#define GRIDPOINT_H

 class GridPoint
 {
	 public:
		GridPoint();
		GridPoint(const GridPoint& g);
		void setInPath(bool path) { inPath = path;}
		bool getInPath() {return inPath;}
		void setFCost(double cost) { F = cost;}
		double getFCost() {return F;}
		void setGCost(double cost) { G = cost;}
		double getGCost() {return G;}
		void setPosition(int p[]);
		void getPosition(int p[]);
		void setPrevious(int p[]);
		void getPrevious(int p[]);
		bool getEdge(int e);
		void setEdge(int e, bool b);
		bool operator<(GridPoint& rhs);
		void operator=(GridPoint& rhs);
		bool operator==(GridPoint& rhs);
		void reset(bool andPosition);
		void setFrom(int f){from = f;}
		unsigned short getFrom(){return from;}
		void clearPath();
	 private:
		double F;
		double G;
		int position[2];
		int previous[2];
		bool edges[9];	
		bool inPath;
		unsigned short from;
};

#endif