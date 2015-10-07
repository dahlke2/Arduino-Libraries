//
//  4x4_cube.h
//  Cube Test
//
//  Created by Ethan Dahlke on 6/13/14.
//  Copyright (c) 2014 Ethan Dahlke. All rights reserved.
//

#ifndef __Cube_Test___x4_cube__
#define __Cube_Test___x4_cube__

#include "arduino.h"
#include "micrel.h"

class Cube_Effect
{
private:
    int Cube_pixels[4][4][4];
    void blah(int *x, int *y, int *z);
public:
    Cube_Effect();
    void single_scan(Cube_4x4 *data, Micrel *a);
    void Box(Cube_4x4 *data);
    void Full(Cube_4x4 *data);
    void Snake(Cube_4x4 *data, Micrel *a);
};


#endif /* defined(__Cube_Test___x4_cube__) */
