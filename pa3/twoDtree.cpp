
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

// Node constructor, given.
twoDtree::Node::Node(pair<int, int> ul, pair<int, int> lr, RGBAPixel a)
        : upLeft(ul), lowRight(lr), avg(a), left(NULL), right(NULL) {}

// twoDtree destructor, given.
twoDtree::~twoDtree() {
    clear();
}

// twoDtree copy constructor, given.
twoDtree::twoDtree(const twoDtree &other) {
    copy(other);
}


// twoDtree assignment operator, given.
twoDtree &twoDtree::operator=(const twoDtree &rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

twoDtree::twoDtree(PNG &imIn) {
    width = imIn.width();
    height = imIn.height();

//    std::cout<<width<<"\n";
//    std::cout<<height<<"\n";

    stats s(imIn);
    pair<int, int> ul;
    ul.first = 0;
    ul.second = 0;
    pair<int, int> lr;
    lr.first = width - 1;
    lr.second = height - 1;
    root = buildTree(s, ul, lr, true);
}

//* vector[0][0] x of the first rec ul, vector[0][1] y of the first rec ul
//* vector[0][2] x of the first rec lr, vector[0][3] y of the first rec lr
//* vector[1][0] x of the second rec ul, vector[1][1] y of the second rec ul
//* vector[1][2] x of the second rec lr, vector[1][3] y of the second rec lr
twoDtree::Node *twoDtree::buildTree(stats &s, pair<int, int> ul, pair<int, int> lr, bool vert) {
    bool update = vert;

//    std::cout<<"before every(build)";
    Node * head = new Node(ul, lr, s.getAvg(ul, lr));
//    std::cout<<head->upLeft.first<<"\n";
    vector <vector<int>> splitRecs;

    if (head->upLeft.first == head->lowRight.first && head->upLeft.second == head->lowRight.second) {
//        std::cout<<"leave case";
        return head;                    // head is leave node dont split
    } else if (head->upLeft.first == head->lowRight.first && lr.second > ul.second) {   //the node has only one column
        update = false;
        splitRecs = split_H(s, head); // only split horizontally

    } else if (head->upLeft.second == head->lowRight.second && lr.first > ul.first) { // the node has only one row
        update = true;
        splitRecs = split_V(s, head); // only split vertically
    } else if (vert == true) {  // normal case
//        std::cout<<"before split_V(build)";
        update = false;
        splitRecs = split_V(s, head);
    } else if (vert == false) {
        update = true;
//        std::cout<<"before split_H(build)";
        splitRecs = split_H(s, head);
    }
//    std::cout<<"after split(build)";


    pair<int, int> left_ul;
    pair<int, int> left_lr;
    left_ul.first = splitRecs[0][0];
    left_ul.second = splitRecs[0][1];
    left_lr.first = splitRecs[0][2];
    left_lr.second = splitRecs[0][3]; // construct rec1 with splitResult

    pair<int, int> right_ul;
    pair<int, int> right_lr;
    right_ul.first = splitRecs[1][0];
    right_ul.second = splitRecs[1][1];
    right_lr.first = splitRecs[1][2];
    right_lr.second = splitRecs[1][3]; // construct rec2 with splitResult

    std::cout<<"before recur\n";
//    std::cout<<left_ul.first<<"\n";
//    std::cout<<left_ul.second<<"\n";
//    std::cout<<left_lr.first<<"\n";
//    std::cout<<left_lr.second<<"\n";
//    std::cout<<right_ul.first<<"\n";
//    std::cout<<right_ul.second<<"\n";
//    std::cout<<right_lr.first<<"\n";
//    std::cout<<right_lr.second<<"\n";
    head->left = buildTree(s, left_ul, left_lr, update);
    head->right = buildTree(s, right_ul, right_lr, update);
    std::cout << "head:" << head->upLeft.second;
    return head;

}

PNG twoDtree::render() {
    PNG renderResult(width, height);
//    std::cout << "before render" << root->upLeft.first;
//    std::cout << "before render" << root->upLeft.second;
//    std::cout << "before render" << root->lowRight.first;
//    std::cout << "before render" << root->lowRight.second;
    render(root, renderResult);
    return renderResult;
}

void twoDtree::render(Node *subRoot, PNG &img) {
    if(subRoot != 0) {
//        std::cout << "reached render\n";
       // std::cout << "before render" << root->left->upLeft.first;
//        std::cout << "before render" << subRoot->upLeft.second;
       std::cout << "before render" << subRoot->lowRight.first;
//        std::cout << "before render" << subRoot->lowRight.second;
        if (subRoot -> left == NULL && subRoot ->right == NULL) {
            std::cout << "reached render if\n";
            for (int x = subRoot->upLeft.first; x <= subRoot->lowRight.first; x++) {
                for (int y = subRoot->upLeft.second; y <= subRoot->lowRight.second; y++) {
                    *img.getPixel(x, y) = subRoot->avg;
                }
            }
        }
        if(subRoot->left != 0) render(root->left, img);
        if(subRoot->right != 0) render(root->right, img);
    }
}

int twoDtree::idealPrune(int leaves) {

// YOUR CODE HERE!!

}

int twoDtree::pruneSize(int tol) {

// YOUR CODE HERE!!

}

void twoDtree::prune(int tol) {

// YOUR CODE HERE!!

}

void twoDtree::clear() {

// YOUR CODE HERE!!

}

void twoDtree::copy(const twoDtree &orig) {

// YOUR CODE HERE!!

}

/**
* cut the recs into 2 recs with x range [ul.x,cutLine_X] and [cutLine, lr.x of head]
* vector[0][0] x of the first rec ul, vector[0][1] y of the first rec ul
* vector[0][2] x of the first rec lr, vector[0][3] y of the first rec lr
* vector[1][0] x of the second rec ul, vector[1][1] y of the second rec ul
* vector[1][2] x of the second rec lr, vector[1][3] y of the second rec lr
 */
vector <vector<int>> twoDtree::split_V(stats &s, twoDtree::Node *head) {
    int ul_x = head->upLeft.first; // upperleft x for both recs is the upperleft x of head
    int ul_y = head->upLeft.second; // upperleft y for both recs is the upperleft y of head

    int lr_x = head->lowRight.first; // lowerright x for both recs is the lowerright x of the head
    int lr_y = head->lowRight.second; // lowerright y for both recs is the lowerright y of the head

    pair<int, int> rec1_ul; // initianlize first rectangle and set y value for ul and lr to the head's ul and lr
    rec1_ul.second = ul_y;
    pair<int, int> rec1_lr;
    rec1_lr.second = lr_y;

    pair<int, int> rec2_ul; // initianlize second rectangle and set y value for ul and lr to the head's ul and lr
    rec2_ul.second = ul_y;
    pair<int, int> rec2_lr;
    rec2_lr.second = lr_y;


    int splitLine_X = ul_x; // starts at leftmost x + 1, so rec1 x [ul_x, ul_x + 1]
    int rightMost = lr_x - 1; // ends at right most x - 1, so rec1 x [ul_x, lr_x - 1]
    rec1_ul.first = ul_x; // rec1_ul x set to left boundry
    rec2_lr.first = lr_x; // rec2_lr x set to right boundry

    int sumOfTwo = 0;
    pair<int, int> min; // first is minimum score, second is the splitLine_x at minimum
    min.first = 0;
    min.second = splitLine_X;
    for (int i = splitLine_X; i <= rightMost; i++) {
        rec1_lr.first = i;  // split so the rec1 x range [ul_x, i]
        rec2_ul.first = i + 1;  // split so the rec2 x range [i, lr_x]

//        std::cout<<"before score";
//        std::cout<<rec1_ul.first<<"\n";
//        std::cout<<rec1_lr.first<<"\n";
//        std::cout<<rec2_ul.first<<"\n";
//        std::cout<<rec2_lr.first<<"\n";
//        std::cout<<rec1_ul.second<<"\n";
//        std::cout<<rec1_lr.second<<"\n";
//        std::cout<<rec2_ul.second<<"\n";
//        std::cout<<rec2_lr.second<<"\n";

        sumOfTwo = s.getScore(rec1_ul, rec1_lr) + s.getScore(rec2_ul, rec2_lr); // adds scores of two recs
        if (min.first == 0 || sumOfTwo <= min.first) {
            min.first = sumOfTwo;
            min.second = i;
        }
    }

    int minSplit_X = min.second;
//    std::cout<<"min-X:"<<minSplit_X<<"\n";


    vector<int> rec1{ul_x, ul_y, minSplit_X, lr_y};
    vector<int> rec2{minSplit_X + 1, ul_y, lr_x, lr_y};
    vector <vector<int>> splitResult={rec1,rec2};
    return splitResult;
}

/**
* cut the recs into 2 recs with y range [ul.y of head,cutLine_Y] and [cutLine_Y, lr.y of head]
* vector[0][0] x of the first rec ul, vector[0][1] y of the first rec ul
* vector[0][2] x of the first rec lr, vector[0][3] y of the first rec lr
* vector[1][0] x of the second rec ul, vector[1][1] y of the second rec ul
* vector[1][2] x of the second rec lr, vector[1][3] y of the second rec lr
 */
vector <vector<int>> twoDtree::split_H(stats &s, twoDtree::Node *head) {
    int ul_x = head->upLeft.first; // upperleft x for both recs is the upperleft x of head
    int ul_y = head->upLeft.second; // upperleft y for both recs is the upperleft y of head

    int lr_x = head->lowRight.first; // lowerright x for both recs is the lowerright x of the head
    int lr_y = head->lowRight.second; // lowerright y for both recs is the lowerright y of the head

    pair<int, int> rec1_ul; // initianlize first rectangle and set x value for ul and lr to the head's ul x and lr x
    rec1_ul.first = ul_x;
    pair<int, int> rec1_lr;
    rec1_lr.first = lr_x;

    pair<int, int> rec2_ul; // initianlize second rectangle and set x value for ul and lr to the head's ul x and lr x
    rec2_ul.first = ul_x;
    pair<int, int> rec2_lr;
    rec2_lr.first = lr_x;


    int splitLine_Y = ul_y; // starts at upmost y + 1, so rec1 y [ul_y, ul_y + 1]
    int downMost = lr_y - 1; // ends at downmost y - 1, so rec1 x [ul_y, lr_y - 1]
    rec1_ul.second = ul_y; // rec1_ul y set to up boundry
    rec2_lr.second = lr_y; // rec2_lr x set to down boundry

//    std::cout<<"beforeSum(split_H)";

    int sumOfTwo = 0;
    pair<int, int> min; // first is minimum score, second is the splitLine_y at minimum
    min.first = 0;
    min.second = splitLine_Y;
//    std::cout<<"split_y:"<<splitLine_Y;
    for (int i = splitLine_Y; i <= downMost; i++) {
        rec1_lr.second = i;  // split so the rec1 y range [ul_y, i]
        rec2_ul.second = i + 1;  // split so the rec2 y range [i,lr_y]

//        std::cout<<"before score";
//        std::cout<<rec1_ul.first<<"\n";
//        std::cout<<rec1_lr.first<<"\n";
//        std::cout<<rec2_ul.first<<"\n";
//        std::cout<<rec2_lr.first<<"\n";
//        std::cout<<rec1_ul.second<<"\n";
//        std::cout<<rec1_lr.second<<"\n";
//        std::cout<<rec2_ul.second<<"\n";
//        std::cout<<rec2_lr.second<<"\n";

        sumOfTwo = s.getScore(rec1_ul, rec1_lr) + s.getScore(rec2_ul, rec2_lr); // adds scores of two recs

//        std::cout<<"after score";

        if (min.first == 0 || sumOfTwo <= min.first) {
            min.first = sumOfTwo;
            min.second = i;
        }
    }


    int minSplit_Y = min.second;
//    std::cout<<"afterSum(split_H)";
//    std::cout<<"minsplit_y:" <<minSplit_Y;


    vector<int> rec1{ul_x, ul_y, lr_x, minSplit_Y};
    vector<int> rec2{ul_x, minSplit_Y + 1, lr_x, lr_y};
    vector <vector<int>> splitResult={rec1,rec2};
    return splitResult;
}
