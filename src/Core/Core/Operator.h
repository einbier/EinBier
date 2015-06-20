#pragma once

#include <vector>
#include <list>

#include <Common/Type.h>
#include <BIO/BIO.h>


class Operator
{
public:
    Coord shape;
    Coord Shape; // (0,0) by Coord constructor

	BIO *bio;

    void createOperator(int, int);
    Operator(int r=0, int c=0);
    Operator(Coord);

    void addBlock(int, int, Operator*);
    void addBlock(int, int, BIO*);

    void addBlock(Coord, Operator*);
    void addBlock(Coord, BIO*);

    void Print();

    Coord get_shape(){return shape;};
    Coord get_Shape(){return Shape;};

    // change with a new type but how ?
    /// so UGLY !!!
    std::list<int> rows;
    std::list<int> cols;
    std::list<Operator*> ops;

    // store the size of the banded block
    std::vector<int> banded_rows;
    std::vector<int> banded_cols;

    bool isInList(int, std::list<int>);
    bool isCheckAndUpdate_shapes(int, int, Coord);
};

