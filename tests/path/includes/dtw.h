
#ifndef VDTW
#define VDTW

#include <vector>
#include <cmath>
#include <assert.h>
#include "messages.hpp"

typedef unsigned int uint;
using namespace std;


class VectorDTW{
private:
	vector<vector<float> > mGamma;
	int mN, mConstraint;
public:
	enum { INF = 100000000 }; //some big number

   	static inline float min (float x, float y ) { return x < y ? x : y; }

	/**
	* n is the length of the time series
	*
	* constraint is the maximum warping distance.
	* Typically: constraint = n/10.
	* If you set constraint = n, things will be slower.
	*
	*/
    	VectorDTW(uint n, uint constraint) : mGamma(n, vector<float>(n, INF)), mN(n), mConstraint(constraint) { }

  float l1_distance(const opendlv::sim::scenario::Frame &p, const opendlv::sim::scenario::Frame &p2){
		return fabs(p.x() - p2.x()) + fabs(p.y() - p2.y());
	}

	//euclidean distance
	float euclid_distance(const opendlv::sim::scenario::Frame &p, const opendlv::sim::scenario::Frame &p2){
		return sqrt((p.x() - p2.x()) * (p.x() - p2.x()) + (p.y() - p2.y()) * (p.y() - p2.y()));
	}

	inline float calculate(vector<opendlv::sim::scenario::Frame> &v, vector<opendlv::sim::scenario::Frame> &w){
  		assert(static_cast<int>(v.size()) == mN);
  		assert(static_cast<int>(w.size()) == mN);
  		assert(static_cast<int>(mGamma.size()) == mN);
  		float Best(INF);
      for (int i = 0; i < mN; ++i){
      		assert(static_cast<int>(mGamma[i].size()) == mN);
      		for(int j = max(0, i - mConstraint); j < min(mN, i + mConstraint + 1); ++j){
          		Best = INF;
          		if(i > 0) Best = mGamma[i - 1][j];
          		if(j > 0) Best = min(Best, mGamma[i][j - 1]);
          		if((i > 0) && (j > 0)) Best = min(Best, mGamma[i - 1][j - 1]);
          		if((i == 0) && (j == 0)) mGamma[i][j] = euclid_distance(v[i],w[j]);
          		else mGamma[i][j] = Best + euclid_distance(v[i],w[j]);
      		}
      	}
       	return mGamma[mN-1][mN-1];
  	}
};

#endif
