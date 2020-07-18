
#include "stats.h"

stats::stats(PNG & im){
    
    sumRed.resize(im.height());
    sumGreen.resize(im.height());
    sumBlue.resize(im.height());
    sumsqRed.resize(im.height());
    sumsqGreen.resize(im.height());
    sumsqBlue.resize(im.height());
    sumRed[0].resize(im.width());
    sumGreen[0].resize(im.width());
    sumBlue[0].resize(im.width());
    sumsqRed[0].resize(im.width());
    sumsqGreen[0].resize(im.width());
    sumsqBlue[0].resize(im.width());
    sumRed[0][0] = im.getPixel(0,0)->r;
    sumGreen[0][0] = im.getPixel(0,0)->g;
    sumBlue[0][0] = im.getPixel(0,0)->b; 
    sumsqRed[0][0] = im.getPixel(0,0)->r * im.getPixel(0,0)->r;
    sumsqGreen[0][0] = im.getPixel(0,0)->g * im.getPixel(0,0)->g;
    sumsqBlue[0][0] = im.getPixel(0,0)->b * im.getPixel(0,0)->b;
    // sumRed[0][0]= (im.getPixel(0,0)->r);
    // sumGreen[0][0]= (im.getPixel(0,0)->g);
    // sumBlue[0][0]= (im.getPixel(0,0)->b); 
    // sumsqRed[0][0]= (im.getPixel(0,0)->r * im.getPixel(0,0)->r);
    // sumsqGreen[0][0]= (im.getPixel(0,0)->g * im.getPixel(0,0)->g);
    // sumsqBlue[0][0]= (im.getPixel(0,0)->b * im.getPixel(0,0)->b);
     
    for (unsigned i = 1; i < im.width(); i++) {
        
        sumRed[0][i] = (sumRed[0][i-1] + im.getPixel(i,0)->r);
        sumGreen[0][i] = (sumGreen[0][i-1] + im.getPixel(i,0)->g);
        sumBlue[0][i] = (sumBlue[0][i-1] + im.getPixel(i,0)->b); 
        sumsqRed[0][i] = (sumsqRed[0][i-1] + im.getPixel(i,0)->r * im.getPixel(i,0)->r) ;
        sumsqGreen[0][i] = (sumsqGreen[0][i-1] + im.getPixel(i,0)->g * im.getPixel(i,0)->g);
        sumsqBlue[0][i] = (sumsqBlue[0][i-1] + im.getPixel(i,0)->b * im.getPixel(i,0)->b); 
    }
    
    for (unsigned i = 1; i < im.height(); i++) {
        sumRed[i].resize(im.width());
        sumGreen[i].resize(im.width());
        sumBlue[i].resize(im.width());
        sumsqRed[i].resize(im.width());
        sumsqGreen[i].resize(im.width());
        sumsqBlue[i].resize(im.width());
        sumRed[i][0]= (sumRed[i-1][0] + im.getPixel(0,i)->r);
        sumGreen[i][0]= (sumGreen[i-1][0] + im.getPixel(0,i)->g);
        sumBlue[i][0]= (sumBlue[i-1][0] + im.getPixel(0,i)->b); 
        sumsqRed[i][0]= (sumsqRed[i-1][0] + im.getPixel(0,i)->r * im.getPixel(0,i)->r);
        sumsqGreen[i][0]= (sumsqGreen[i-1][0] + im.getPixel(0,i)->g * im.getPixel(0,i)->g);
        sumsqBlue[i][0]= (sumsqBlue[i-1][0] + im.getPixel(0,i)->b * im.getPixel(0,i)->b); 
        
    }
    
    for (unsigned i = 1; i < im.height(); i++) {
        for (unsigned j = 1; j < im.width(); j++) {
            sumRed[i][j]= (sumRed[i-1][j] + sumRed[i][j-1] - sumRed[i-1][j-1] + im.getPixel(j, i)->r); 
            sumGreen[i][j]= (sumGreen[i-1][j] + sumGreen[i][j-1] - sumGreen[i-1][j-1] + im.getPixel(j, i)->g); 
            sumBlue[i][j]= (sumBlue[i-1][j] + sumBlue[i][j-1] - sumBlue[i-1][j-1] + im.getPixel(j, i)->b); 
            sumsqRed[i][j]= (sumsqRed[i-1][j] + sumsqRed[i][j-1] - sumsqRed[i-1][j-1] + im.getPixel(j, i)->r * im.getPixel(j, i)->r ); 
            sumsqGreen[i][j]= (sumsqGreen[i-1][j] + sumsqGreen[i][j-1] - sumsqGreen[i-1][j-1] + im.getPixel(j, i)->g * im.getPixel(j, i)->g); 
            sumsqBlue[i][j]= (sumsqBlue[i-1][j] + sumsqBlue[i][j-1] - sumsqBlue[i-1][j-1] + im.getPixel(j, i)->b * im.getPixel(j, i)->b);
        }
    }
     


}

long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){
   
    long total = 0;
    if (channel == 'r') {
            if (ul.first >0 && ul.second > 0) {
                total = sumRed[lr.first][lr.second] - sumRed[lr.first][ul.second-1] - sumRed[ul.first-1][lr.second] + sumRed[ul.first-1][ul.second-1];
            } else if (ul.first > 0) {
                total = sumRed[lr.first][lr.second] - sumRed[lr.first][ul.second-1] ;
            } else if (ul.second > 0) {
                total = sumRed[lr.first][lr.second] - sumRed[ul.first-1][lr.second];
            } else {
                total = sumRed[lr.first][lr.second];
            }
    } else if (channel == 'g') {
        
            if (ul.first >0 && ul.second > 0) {
                total = sumGreen[lr.first][lr.second] - sumGreen[lr.first][ul.second-1] - sumGreen[ul.first-1][lr.second] + sumGreen[ul.first-1][ul.second-1];
            } else if (ul.first > 0) {
                total = sumGreen[lr.first][lr.second] - sumGreen[lr.first][ul.second-1];
            } else if (ul.second > 0) {
                total = sumGreen[lr.first][lr.second] - sumGreen[ul.first-1][lr.second];
            } else {
                total = sumGreen[lr.first][lr.second];
            }     
    } else if (channel == 'b') {
            if (ul.first >0 && ul.second > 0) {
                total = sumBlue[lr.first][lr.second] - sumBlue[lr.first][ul.second-1] - sumBlue[ul.first-1][lr.second] + sumBlue[ul.first-1][ul.second-1];
            } else if (ul.first > 0) {
                total = sumBlue[lr.first][lr.second] - sumBlue[lr.first][ul.second-1];
            } else if (ul.second > 0) {
                total = sumBlue[lr.first][lr.second] - sumBlue[ul.first-1][lr.second];
            } else {
                total = sumBlue[lr.first][lr.second];
            }   
    }
    
    
    return total;
}

long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){
    long total = 0;
    if (channel == 'r') {
        
            if (ul.first >0 && ul.second > 0) {
                total = sumsqRed[lr.first][lr.second] - sumsqRed[lr.first][ul.second-1] - sumsqRed[ul.first-1][lr.second] + sumsqRed[ul.first-1][ul.second-1];
            } else if (ul.first > 0) {
                total = sumsqRed[lr.first][lr.second] - sumsqRed[lr.first][ul.second-1] ;
            } else if (ul.second > 0) {
                total = sumsqRed[lr.first][lr.second] - sumsqRed[ul.first-1][lr.second];
            } else {
                total = sumsqRed[lr.first][lr.second];
            }
    } else if (channel == 'g') {
            if (ul.first >0 && ul.second > 0) {
                total = sumsqGreen[lr.first][lr.second] - sumsqGreen[lr.first][ul.second-1] - sumsqGreen[ul.first-1][lr.second] + sumsqGreen[ul.first-1][ul.second-1];
            } else if (ul.first > 0) {
                total = sumsqGreen[lr.first][lr.second] - sumsqGreen[lr.first][ul.second-1];
            } else if (ul.second > 0) {
                total = sumsqGreen[lr.first][lr.second] - sumsqGreen[ul.first-1][lr.second];
            } else {
                total = sumsqGreen[lr.first][lr.second];
            }     
    } else if (channel == 'b') {
            if (ul.first >0 && ul.second > 0) {
                total = sumsqBlue[lr.first][lr.second] - sumsqBlue[lr.first][ul.second-1] - sumsqBlue[ul.first-1][lr.second] + sumsqBlue[ul.first-1][ul.second-1];
            } else if (ul.first > 0) {
                total = sumsqBlue[lr.first][lr.second] - sumsqBlue[lr.first][ul.second-1];
            } else if (ul.second > 0) {
                total = sumsqBlue[lr.first][lr.second] - sumsqBlue[ul.first-1][lr.second];
            } else {
                total = sumsqBlue[lr.first][lr.second];
            }   
    }
    
    
    return total;
    
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){
    
    return (long) (lr.first - ul.first + 1) * (lr.second - ul.second + 1);

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int,int> ul, pair<int,int> lr){
    long redScore = getSumSq('r', ul , lr) - getSum('r', ul, lr) *getSum('r', ul, lr)/ rectArea(ul, lr); 
    long greenScore = getSumSq('g', ul , lr) - getSum('g', ul, lr) *getSum('g', ul, lr)/ rectArea(ul, lr); 
    long blueScore = getSumSq('b', ul , lr) - getSum('b', ul, lr) *getSum('b', ul, lr)/ rectArea(ul, lr);
    return redScore + greenScore + blueScore; 
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
    
    long redAvg = getSum ('r' , ul, lr) / rectArea(ul, lr);
    long greenAvg = getSum ('g' , ul, lr) / rectArea(ul, lr);
    long blueAvg = getSum ('b' , ul, lr) / rectArea(ul, lr);
    RGBAPixel pix = RGBAPixel(redAvg, greenAvg, blueAvg);
    return pix; 
}
