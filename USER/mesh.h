#include "definitions.h"

const uint16_t num_vertices = 6;
const uint16_t num_indices = 8;

const vertex_attr_t vertices[] = {
	VA(0,0,24574,127,127,254), VA(0,24574,0,127,254,127), VA(-24574,0,0,0,127,127), VA(0,-24574,0,127,0,127), 
	VA(24574,0,0,254,127,127), VA(0,0,-24574,127,127,0)
};

const triangle_index_t indices[] = {
	IDX(0,1,2), IDX(0,2,3), IDX(0,3,4), IDX(0,4,1), IDX(5,2,1), IDX(5,3,2), 
	IDX(5,4,3), IDX(5,1,4)
};
