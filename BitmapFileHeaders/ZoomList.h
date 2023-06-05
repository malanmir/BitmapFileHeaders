#pragma once

#include<vector>
#include "Zoom.h"

namespace caveofprogramming {

	class ZoomList
	{
	public:

		ZoomList(int width, int height);
		void add(const Zoom& zoom);
		std::pair<double, double> doZoom(int x, int y);
	private:
		double m_xCenter{ 0.0 };
		double m_yCenter{ 0.0 };
		double m_scale{ 1.0 };

		int m_width { 0 };
		int m_height{ 0 };
		std::vector<Zoom> zooms;
	};
}