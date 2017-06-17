//
//  Canvas.h
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Canvas_h
#define Canvas_h

#include <cstdint>
#include <vector>
#include "Image.h"
#include "Vector.h"

using std::vector;

class Canvas {
	Image *image;
public:
	vector<vector<Vector>> pixels;
	void setImageFormat(ImageFormat format) {
		switch (format) {
			case ppm:
				image = new PortablePixmap;
				break;
			default:
				break;
		}
	}
	void exportTo(const string &fileName) {
		image->exportTo(pixels, fileName);
	}
};

#endif /* Canvas_h */
