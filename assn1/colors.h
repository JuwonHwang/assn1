#pragma once

class Color {
private:
	float red;
	float green;
	float blue;
	float alpha;

public:
	Color() {
		this->red = 0.0f;
		this->green = 0.0f;
		this->blue = 0.0f;
		this->alpha = 0.0f;
	};

	Color(float red, float green, float blue, float alpha = 1.0f) {
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	float& operator [] (const int index)
	{
		if (index == 0) {
			return red;
		}
		else if (index == 1) {
			return green;
		}
		else if (index == 2) {
			return blue;
		}
		else if (index == 3) {
			return alpha;
		}
		return red;
	}
};