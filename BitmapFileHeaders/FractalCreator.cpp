#include<iostream>

#include "FractalCreator.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include <cassert>


void caveofprogramming::FractalCreator::run(const std::string & name)
{
    calculateIteration();
    calculateTotalIterations();
    calculateRangeTotals();
    drawFractal();
    writeBitmap(name);


}

caveofprogramming::FractalCreator::FractalCreator(int width, int height) : m_width(width), m_height(height),
    m_histogram(new int [Mandelbrot::MAX_ITERATIONS] { 0 }),
    m_fractal(new int[width * height] {}),
    m_bitmap(width, height),
    m_zoomList(width, height)
{
    m_zoomList.add(Zoom(width / 2, height / 2, 4.0 / width));

}

caveofprogramming::FractalCreator::~FractalCreator()
{
}

void caveofprogramming::FractalCreator::calculateRangeTotals()
{
    int rangeIndex = 0;
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        int pixels = m_histogram[i];
        if (i >= m_ranges[rangeIndex + 1])
            rangeIndex++;
        m_rangeTotals[rangeIndex] += pixels;
    }
}

int caveofprogramming::FractalCreator::getRange(int iterations)const
{
    int range = 0;
    for (int i = 0; i < m_ranges.size(); i++) {
        range = i;
        if (m_ranges[i] > iterations) {
            break;
        }
    }
    range--;

    assert(range > -1);
    assert(range < m_ranges.size());

    return range;
}

void caveofprogramming::FractalCreator::calculateIteration()
{
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            std::pair<double, double> coords = m_zoomList.doZoom(x, y);

            int iterations = Mandelbrot::getIterations(coords.first, coords.second);

            m_fractal[y * m_width + x] = iterations;

            if (iterations != Mandelbrot::MAX_ITERATIONS) {
                m_histogram[iterations]++;
            }
        }
    }
}

void caveofprogramming::FractalCreator::drawFractal()
{
    RGB startColor(0, 0, 0);
    RGB endColor(180, 255, 255); 
    RGB colorDiff = endColor - startColor;
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {

            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            int iterations = m_fractal[y * m_width + x];
            uint8_t color = static_cast<uint8_t>(256 * static_cast<double>(iterations) / Mandelbrot::MAX_ITERATIONS);

            if (iterations != Mandelbrot::MAX_ITERATIONS) {

                double hue = 0.0;

                for (int i = 0; i <= iterations; i++) {
                    hue += static_cast<double>(m_histogram[i]) / m_total;
                }

                red = startColor.r + colorDiff.r * hue;
                green = startColor.g + colorDiff.g * hue;
                blue = startColor.b + colorDiff.b * hue;
            }
            m_bitmap.setPixel(x, y, red, green, blue);
        }
    
    }
}

void caveofprogramming::FractalCreator::calculateTotalIterations()
{
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        m_total += m_histogram[i];
    }
}

void caveofprogramming::FractalCreator::addZoom(const Zoom& zoom)
{
    m_zoomList.add(zoom);
}

void caveofprogramming::FractalCreator::writeBitmap(std::string name)
{
    if (!m_bitmap.write(name))
        std::cout << "Not written." << std::endl;
}

void caveofprogramming::FractalCreator::addRange(double rangeEnd, const RGB& rgb) {
    m_ranges.emplace_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
    m_colors.emplace_back(rgb);

    if (m_gotFirstRange) {
        m_rangeTotals.emplace_back();
    }
    m_gotFirstRange = true;
}
