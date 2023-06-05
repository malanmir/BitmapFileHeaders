#include<iostream>
#include "ZoomList.h"


caveofprogramming::ZoomList::ZoomList(int width, int height) :  m_width(width), m_height(height)
{

}

void caveofprogramming::ZoomList::add(const Zoom& zoom)
{
	m_xCenter += (zoom.x - m_width / 2) * m_scale;
	m_yCenter += (zoom.y - m_height/ 2) * m_scale;
	m_scale *= zoom.scale;

	std::cout << m_xCenter << ", " << m_yCenter << ", " << m_scale << std::endl;
	zooms.emplace_back(zoom);
}

std::pair<double, double> caveofprogramming::ZoomList::doZoom(int x, int y)
{
	double xFractal = (x - m_width/2)*m_scale + m_xCenter;
	double yFractal = -(y - m_height/2)*m_scale + m_yCenter;

	return std::pair<double, double>(xFractal, yFractal);

}
