//
//		          Programming Assignment #1
//
//					Daljit Singh Dhillon
//
//
/***************************************************************************/
/* Include needed files */
# include <cmath>
#include <algorithm>
using namespace std;
/***************************************************************************/
// Forward declarations
void drawPixel(int x, int y);

void drawLineBrute(float xStart, float yStart, float xEnd, float yEnd);
void drawLineWu(int xStart, int yStart, int xEnd, int yEnd, int lineWidth);
void drawLineSlopeIntercept(float slope, float yIntercept);
void draw2dAxesAndSquare(float orgX, float orgY, float xVecE1, float xVecE2, float yVecE1, float yVecE2, float sqrBaseX, float sqrBaseY, float sqrWidth);
void draw3dAxesAndCube(float orgX, float orgY, float xVecE1, float xVecE2, float yVecE1, float yVecE2, float zVecE1, float zVecE2, float cubeBaseX, float cubeBaseY, float cubeBaseZ, float cubeWidth);
void drawStyleDottedLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth);
void drawStyleDashedLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth);
void drawStyleDotAndDashLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth);
void drawArbitraryThickPixel(int x, int y, int lineWidth);

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 800;

void drawLineBrute(float xStart, float yStart, float xEnd, float yEnd)
{
	double m = (yEnd - yStart)/(xEnd - xStart);  //slope
	double A = yEnd - yStart;
	double B = xStart - xEnd;
	double C = xEnd*yStart - xStart*yEnd;
	double N = sqrt(A*A + B*B);
	double dist = 0.0;
	const double threshold = 0.5;

	double minX = std::min(xStart, xEnd);
	double minY = std::min(yStart, yEnd);
	double maxX = std::max(xStart, xEnd);
	double maxY = std::max(yStart, yEnd);

	for (int j=0; j<=SCREEN_HEIGHT; ++j){
		for (int i=0; i<=SCREEN_WIDTH; ++i){
			if (i>=minX && i<=maxX && j>=minY && j<=maxY){
				dist = (A*i + B*j + C)/N;
				if (dist < threshold && dist>=0){
					drawPixel(i, j);
				}
			}
		}
	}
}

void drawLineWu(int xStart, int yStart, int xEnd, int yEnd, int lineWidth)
{
	drawPixel((int)xStart,(int)yStart);
	drawPixel((int)xEnd, (int)yEnd);

	//replace above two lines with your own inplementation
}

void drawLineDDA(float xStart, float yStart, float xEnd, float yEnd)
{
    float xCurr, yCurr, dX, dY;
    float slope;
    int steps = 0;

    dY = (yEnd-yStart)/abs(yEnd-yStart);
    dX = (xEnd-xStart)/abs(xEnd-xStart);

    xCurr = xStart;
    yCurr = yStart;

    if (xStart == xEnd)
    {
        dX = 0;
        steps = abs(yEnd-yStart);
    } else
    {
      slope = (yEnd-yStart)/(xEnd-xStart);

      if (abs(xEnd-xStart) > abs(yEnd-yStart))
      {
        dY = slope*dX;
        steps = abs(xEnd-xStart);
      } else
      {
        dX = dY/slope;
        steps = abs(yEnd-yStart);
      }
    }

    steps = round(steps);
    //drawPixel((int)xStart,(int)yStart);
    for (int ii=0; ii <= steps; ++ii)
    {
	drawPixel(round(xCurr),round(yCurr));
        xCurr += dX;
        yCurr += dY;
    }
}

void drawStyleDottedLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth)
{
	float xCurr, yCurr, dX, dY;
	float slope;
	int steps = 0;

	dY = (yEnd-yStart)/abs(yEnd-yStart);
	dX = (xEnd-xStart)/abs(xEnd-xStart);

	xCurr = xStart;
	yCurr = yStart;

	if (xStart == xEnd)
	{
			dX = 0;
			steps = abs(yEnd-yStart);
	} else
	{
		slope = (yEnd-yStart)/(xEnd-xStart);

		if (abs(xEnd-xStart) > abs(yEnd-yStart))
		{
			dY = slope*dX;
			steps = abs(xEnd-xStart);
		} else
		{
			dX = dY/slope;
			steps = abs(yEnd-yStart);
		}
	}

	steps = round(steps);
	bool draw_flag = true;
	//drawPixel((int)xStart,(int)yStart);
	for (int ii=0; ii <= steps;)
	{
		if (draw_flag){
			drawArbitraryThickPixel(round(xCurr),round(yCurr), lineWidth);
			xCurr += lineWidth*dX;
			yCurr += lineWidth*dY;
			ii += lineWidth;
			draw_flag = false;
		}
		else{
			draw_flag = true;
		}
		xCurr += lineWidth*dX;
		yCurr += lineWidth*dY;
		ii += lineWidth;
	}
	drawArbitraryThickPixel(round(xEnd),round(yEnd), lineWidth);
}

void drawArbitraryThickPixel(int x, int y, int lineWidth){
    int halfWidth = lineWidth/2;
    for(int i = -halfWidth; i <= halfWidth; i++){
      for(int j = -halfWidth; j <= halfWidth; j++){
        if(std::hypot(i, j) <= halfWidth){
          drawPixel(x+i, y+j);
        }
      }
    }
}

void drawStyleDashedLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth)
{
	float xCurr, yCurr, dX, dY;
	float slope;
	int steps = 0;

	dY = (yEnd-yStart)/abs(yEnd-yStart);
	dX = (xEnd-xStart)/abs(xEnd-xStart);

	xCurr = xStart;
	yCurr = yStart;

	if (xStart == xEnd)
	{
			dX = 0;
			steps = abs(yEnd-yStart);
	} else
	{
		slope = (yEnd-yStart)/(xEnd-xStart);

		if (abs(xEnd-xStart) > abs(yEnd-yStart))
		{
			dY = slope*dX;
			steps = abs(xEnd-xStart);
		} else
		{
			dX = dY/slope;
			steps = abs(yEnd-yStart);
		}
	}

	steps = round(steps);
	int dashCounter = 0;
	bool drawing = true;
	const int dashLength = 10*lineWidth;
	const int gapLength = 5*lineWidth;

	//drawPixel((int)xStart,(int)yStart);
	for (int ii = 0; ii <= steps; ++ii)
    {
      if (drawing){
        drawArbitraryThickPixel(round(xCurr), round(yCurr), lineWidth);
      }
      xCurr += dX;
      yCurr += dY;

      dashCounter++;
      if (drawing && dashCounter >= dashLength){
        drawing = false;
        dashCounter = 0;
      }
      else if (!drawing && dashCounter >= gapLength){
        drawing = true;
        dashCounter = 0;
      }
    }
	drawArbitraryThickPixel(round(xCurr),round(yCurr), lineWidth);
}

void drawStyleDotAndDashLine(float xStart, float yStart, float xEnd, float yEnd, int lineWidth)
{
	drawPixel((int)xStart,(int)yStart);
	drawPixel((int)xEnd, (int)yEnd);
}


void drawLineSlopeIntercept(float slope, float yIntercept)
{

	double A = slope;
	double B = -1.0;
	double C = yIntercept;
	double N = sqrt(A*A + B*B);
	double dist = 0.0;
	const double threshold = 0.5;
	for (int j=0; j<SCREEN_HEIGHT; j++){
		for (int i=0; i<SCREEN_WIDTH; i++){
			dist = (A*i + B*j + C)/N;
			if (dist < threshold && dist>=0){
				drawPixel(i, j);
			}
		}
	}
}
void draw2dAxesAndSquare(float orgX, float orgY,
						 float xVecE1, float xVecE2,
						 float yVecE1, float yVecE2,
						 float cubeBaseX, float cubeBaseY, float cubeWidth)
{
	drawPixel((int)orgX,(int)orgY);
	drawPixel((int)orgX, (int)orgY);

	//replace above two lines with your own inplementation
}
void draw3dAxesAndCube(float orgX, float orgY,
					   float xVecE1, float xVecE2,
					   float yVecE1, float yVecE2,
					   float zVecE1, float zVecE2,
					   float cubeBaseX, float cubeBaseY, float cubeBaseZ, float cubeWidth)
{
	float n1 = sqrt(xVecE1*xVecE1 + xVecE2*xVecE2);
	float n2 = sqrt(yVecE1*yVecE1 + yVecE2*yVecE2);
	float n3 = sqrt(zVecE1*zVecE1 + zVecE2*zVecE2);

	//axis:
	drawLineDDA(orgX, orgY, orgX + 20*xVecE1/n1, orgY + 20*xVecE2/n1);
	drawLineDDA(orgX, orgY, orgX + 20*yVecE1/n2, orgY + 20*yVecE2/n2);
	drawLineDDA(orgX, orgY, orgX + 20*zVecE1/n3, orgY + 20*zVecE2/n3);

	//cube lines:
	drawLineDDA(cubeBaseX + orgX, cubeBaseY + orgY, cubeBaseX + cubeWidth*xVecE1 + orgX, cubeBaseY + cubeWidth*xVecE2 + orgY);
	drawLineDDA(cubeBaseX + orgX, cubeBaseY + orgY, cubeBaseX + cubeWidth*yVecE1 + orgX, cubeBaseY + cubeWidth*yVecE2 + orgY);
	drawLineDDA(cubeBaseX + cubeWidth*xVecE1 + orgX, cubeBaseY + cubeWidth*xVecE2 + orgY, cubeBaseX + cubeWidth*xVecE1 + cubeWidth*yVecE1 + orgX, cubeBaseY + cubeWidth*xVecE2 + cubeWidth*yVecE2 + orgY);
	drawLineDDA(cubeBaseX + cubeWidth*yVecE1 + orgX, cubeBaseY + cubeWidth*yVecE2 + orgY, cubeBaseX + cubeWidth*xVecE1 + cubeWidth*yVecE1 + orgX, cubeBaseY + cubeWidth*xVecE2 + cubeWidth*yVecE2 + orgY);


	drawLineDDA(cubeBaseX + orgX, cubeBaseY + orgY, cubeBaseX + cubeWidth*zVecE1 + orgX, cubeBaseY + cubeWidth*zVecE2 + orgY);
	drawLineDDA(cubeBaseX + cubeWidth*xVecE1 + orgX, cubeBaseY + cubeWidth*xVecE2 + orgY, cubeBaseX + cubeWidth*xVecE1 + cubeWidth*zVecE1 + orgX, cubeBaseY + cubeWidth*xVecE2 + cubeWidth*zVecE2 + orgY);
	drawLineDDA(cubeBaseX + cubeWidth*yVecE1 + orgX, cubeBaseY + cubeWidth*yVecE2 + orgY, cubeBaseX + cubeWidth*yVecE1 + cubeWidth*zVecE1 + orgX, cubeBaseY + cubeWidth*yVecE2 + cubeWidth*zVecE2 + orgY);
	drawLineDDA(cubeBaseX + cubeWidth*xVecE1 + cubeWidth*yVecE1 + orgX, cubeBaseY + cubeWidth*xVecE2 + cubeWidth*yVecE2 + orgY, cubeBaseX + cubeWidth*xVecE1 + cubeWidth*yVecE1 + cubeWidth*zVecE1 + orgX, cubeBaseY + cubeWidth*xVecE2 + cubeWidth*yVecE2 + cubeWidth*zVecE2 + orgY);

	drawLineDDA(cubeBaseX + cubeWidth*zVecE1 + orgX, cubeBaseY + cubeWidth*zVecE2 + orgY, cubeBaseX + cubeWidth*xVecE1 + cubeWidth*zVecE1 + orgX, cubeBaseY + cubeWidth*xVecE2 + cubeWidth*zVecE2 + orgY);
	drawLineDDA(cubeBaseX + cubeWidth*zVecE1 + orgX, cubeBaseY + cubeWidth*zVecE2 + orgY, cubeBaseX + cubeWidth*yVecE1 + cubeWidth*zVecE1 + orgX, cubeBaseY + cubeWidth*yVecE2 + cubeWidth*zVecE2 + orgY);
	drawLineDDA(cubeBaseX + cubeWidth*xVecE1 + cubeWidth*zVecE1 + orgX, cubeBaseY + cubeWidth*xVecE2 + cubeWidth*zVecE2 + orgY, cubeBaseX + cubeWidth*xVecE1 + cubeWidth*yVecE1 + cubeWidth*zVecE1 + orgX, cubeBaseY + cubeWidth*xVecE2 + cubeWidth*yVecE2 + cubeWidth*zVecE2 + orgY);
	drawLineDDA(cubeBaseX + cubeWidth*yVecE1 + cubeWidth*zVecE1 + orgX, cubeBaseY + cubeWidth*yVecE2 + cubeWidth*zVecE2 + orgY, cubeBaseX + cubeWidth*xVecE1 + cubeWidth*yVecE1 + cubeWidth*zVecE1 + orgX, cubeBaseY + cubeWidth*xVecE2 + cubeWidth*yVecE2 + cubeWidth*zVecE2 + orgY);
}
