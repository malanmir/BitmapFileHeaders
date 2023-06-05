#include <iostream>
#include <memory>

#include "FractalCreator.h"

using namespace caveofprogramming;
using namespace std;


int main()
{
    FractalCreator fCreator(800, 600);  

    fCreator.addRange(0.0, RGB(0, 0, 0));
    fCreator.addRange(0.3, RGB(255, 0, 0));
    fCreator.addRange(0.5, RGB(255, 255, 0));
    fCreator.addRange(1.0, RGB(255, 255, 255));
    
    fCreator.addZoom(Zoom(295, 202, 0.1));
    fCreator.addZoom(Zoom(312, 304, 0.1));

    fCreator.run("test.bmp");
    return 0;
}
