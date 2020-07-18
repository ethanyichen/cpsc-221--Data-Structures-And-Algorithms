// File:        gridlist.cpp
// Date:        2020-01-18 00:11
// Description: Contains partial implementation of GridList class
//              CPSC 221 2019W2 PA1
//              Function bodies to be completed by yourselves
//
// ADD YOUR FUNCTION IMPLEMENTATIONS IN THIS FILE
//

#include "gridlist.h"
#include "gridlist_given.cpp"

// Creates a PNG of appropriate pixel dimensions according to the GridList's structure
//   and colours each pixel according the each GridNode's Block data.
// The fully coloured PNG is returned.
PNG GridList::Render() const {
    PNG image;
    image.resize(northwest->data.Dimension() * dimx, northwest->data.Dimension() * dimy);
    int x = 0;
    int y = 0;
    for (GridNode *curr = northwest; curr != NULL; curr = curr->next) {
        curr->data.Render(image, y * curr->data.Dimension(), x * curr->data.Dimension());
        if (x + 1 < dimx) {
            x++;
        } else if (y + 1 < dimy) {
            y++;
            x = 0;
        }
    }
    return image;
}

// Allocates a new GridNode containing bdata and
//   attaches it to end of this list.
// Be careful of the special case of inserting into an empty list.
void GridList::InsertBack(const Block &bdata) {
    if (northwest == NULL) {
        northwest = new GridNode(bdata);
        southeast = northwest;
    } else {
        GridNode *node = new GridNode(bdata);
        node->prev = southeast;
        southeast->next = node;
        southeast = node;
    }
}

// if this list has an odd number of column blocks, then the right side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two column blocks
//       inner list must have at least one column block
//       inner list must have the same vertical resolution, vertical block dimension, and block size
// POST: this list has nodes of the entire inner list in between the left and right halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_H(GridList &inner) {
    int middle = dimx / 2;
    GridNode *currInner = inner.northwest;

    GridNode *currMain = northwest;
    if (dimx < 2 || inner.dimx < 1) {
        return;
    }
    if (inner.dimy != dimy || inner.northwest->data.Dimension() != northwest->data.Dimension()) {
        return;
    }

    dimx = dimx + inner.dimx;
    for (int i = 0; i < dimy; i++) {

        for (int j = 0; j < middle - 1; j++) {
            currMain = currMain->next;
        }
        for (int x = 0; x < inner.dimx; x++) {
            GridNode *temp;
            temp = currInner;
            currInner = currInner->next;
            temp->prev = currMain;
            temp->next = currMain->next;
            currMain->next->prev = temp;
            currMain->next = temp;

            currMain = currMain->next;
            //currInner = currInner->next;

        }

        //currMain = currMain->next;
        for (int k = 0; k < dimx - inner.dimx - middle + 1; k++) {
            currMain = currMain->next;
        }


    }
    inner.northwest = NULL;
    inner.southeast = NULL;

}

// inner list must have the same horizontal resolution, horizontal block dimension, and block size
// if this list has an odd number of row blocks, then the bottom side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two row blocks
//       inner list must have at least one row block
//       inner list must have same horizontal resolution, horizontal block dimension, and block size
// POST: this list has nodes of the entire inner list in between the upper and lower halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_V(GridList &inner) {
    if (dimy <= 1 || inner.dimy < 1) { return; }
    // check if this list have at least two row blocks
    // inner list have at least one row block
    if (inner.dimx != dimx || inner.northwest->data.Dimension() != this->northwest->data.Dimension()) { return; }
    // check if inner list have same horizontal resolution, horizontal block dimension, and block size
    if (inner.Length() == 0 || Length() == 0) { return; }
    // check if innerList or thisList is emtpy
    int y = dimy + inner.dimy;
    GridNode *tempNext = FindNodeToAddAfter_V()->next;
    FindNodeToAddAfter_V()->next = inner.northwest;
    inner.northwest->prev = FindNodeToAddAfter_V();
    inner.southeast->next = tempNext;
    tempNext->prev = inner.southeast;
    inner.northwest = NULL;
    inner.southeast = NULL;
    inner.dimx = 0;
    inner.dimy = 0;
    dimy = y;

}


// PRE:  this list and otherlist have the same pixel dimensions, block dimensions, and block size
// POST: this list and otherlist are checkered with each other's nodes
//       each list's dimensions remain the same
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::CheckerSwap(GridList &otherlist) {

    if (otherlist.northwest == NULL || northwest == NULL) { return; }
    // check if otherList or thisList is emtpy
    int dimensionOther = otherlist.northwest->data.Dimension();
    int dimensionThis = northwest->data.Dimension();
    if ((dimensionOther == dimensionThis) && (dimx == otherlist.dimx) && (dimy == otherlist.dimy)) {

        for (int y = 1; y <= otherlist.dimy; y++) {
            for (int x = 1; x <= otherlist.dimx; x++) {
                if (((x + y) % 2) != 0) {
                    GridNode *nodeToSwapOut = GetNode(x, y);
                    GridNode *nodeToSwapIn = otherlist.GetNode(x, y);
                    if (nodeToSwapIn->next != NULL && nodeToSwapOut->next != NULL) {
                        GridNode *nodeToSwapOutNext = nodeToSwapOut->next;
                        GridNode *nodeToSwapOutPrev = nodeToSwapOut->prev;
                        GridNode *nodeToSwapInPrev = nodeToSwapIn->prev;
                        GridNode *nodeToSwapInNext = nodeToSwapIn->next;
                        nodeToSwapInPrev->next = nodeToSwapOut;
                        nodeToSwapInNext->prev = nodeToSwapOut;
                        nodeToSwapOutPrev->next = nodeToSwapIn;
                        nodeToSwapOutNext->prev = nodeToSwapIn;
                        nodeToSwapIn->prev = nodeToSwapOutPrev;
                        nodeToSwapIn->next = nodeToSwapOutNext;
                        nodeToSwapOut->prev = nodeToSwapInPrev;
                        nodeToSwapOut->next = nodeToSwapInNext;
                    } else {
                        GridNode *nodeToSwapInPrev = nodeToSwapIn->prev;
                        nodeToSwapOut->prev->next = nodeToSwapIn;
                        nodeToSwapIn->prev = nodeToSwapOut->prev;
                        nodeToSwapOut->prev = nodeToSwapInPrev;
                        nodeToSwapInPrev->next = nodeToSwapOut;
                    }
                    }
                }
            }
        }
    }

// POST: this list has the negative effect applied selectively to GridNodes to form
//         a checkerboard pattern.
//       The northwest block is normal (does not have the negative effect applied).
// Ensure that the checkering looks correct for both odd and even horizontal block dimensions
void GridList::CheckerN() {
    int x = 0;
    int y = 0;
    bool alt = false;
    for (GridNode *curr = northwest; curr != NULL; curr = curr->next) {

        if (y % 2 == 0) {
            if (alt) {
                curr->data.Negative();
                alt = false;
            } else {
                alt = true;
            }
        } else {
            //alt = true;
            if (alt) {
                curr->data.Negative();
                alt = false;
            } else {
                alt = true;
            }
        }
        if (x + 1 < dimx) {
            x = x + 1;
        } else if (y + 1 < dimy) {
            if ((y + 1) % 2 == 0) {
                alt = false;
            } else {
                alt = true;
            }
            y = y + 1;
            x = 0;
        }
    }
}

// Deallocates any dynamic memory associated with this list
//   and re-initializes this list to an empty state
void GridList::Clear() {
    if (Length() != 0) {
        GridNode *temp = new GridNode();
        GridNode *curr = northwest;
        while (curr->next != NULL) {
            temp = curr->next;
            delete curr;
            curr = temp;

        }
        delete southeast;
        temp = NULL;
        southeast = NULL;
        northwest = NULL;
        dimx = 0;
        dimy = 0;
    }
}

// Allocates new nodes into this list as copies of all nodes from otherlist
void GridList::Copy(const GridList &otherlist) {
    if (otherlist.northwest == NULL && otherlist.southeast == NULL) { return; }
    dimx = otherlist.dimx;
    dimy = otherlist.dimy;

    GridNode *head = new GridNode(otherlist.northwest->data);
    northwest = head;
    GridNode *posInOther = otherlist.northwest->next;
    GridNode *curr = new GridNode(posInOther->data);
    while (curr != NULL) {
        GridNode *curr = new GridNode(posInOther->data);
        head->next = curr;
        curr->prev = head;
        head = curr;
        posInOther = posInOther->next;
    }
    southeast = head;
}

// PRE: this list must have at least two row blocks
GridNode *GridList::FindNodeToAddAfter_V() {
    int rowAbove = (dimy / 2);
    int x = 1;
    int rowCount = 1;

    for (GridNode *curr = northwest; curr != NULL; curr = curr->next) {
        if (x + 1 <= dimx) {
            ++x;
        } else {
            if (rowCount == rowAbove) {
                return curr;
            }
            x = 1;
            ++rowCount;
        }
    }
}

GridNode *GridList::GetNode(int columnNum, int rowNum) {
    if (northwest != NULL) {
        GridNode *curr = northwest;
        int count = 1;
        while (curr != NULL) {
            if (count == (dimx * (rowNum - 1)) + columnNum) {
                return curr;
            }
            curr = curr->next;
            count++;
        }
    }
}