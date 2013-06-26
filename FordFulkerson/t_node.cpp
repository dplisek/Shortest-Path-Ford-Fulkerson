//
//  t_node.cpp
//  JarnikPrim
//
//  Created by Dominik Plíšek on 5/20/13.
//  Copyright (c) 2013 Dominik Plíšek. All rights reserved.
//

#include "t_node.h"

ostream& operator<<(ostream& os, const t_node & node) {
	os << node.type;
	return os;
}