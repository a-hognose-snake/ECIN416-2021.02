#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat dest, gray;
	Mat imagen = imread("kids.png");

	CascadeClassifier detector;

	if (!detector.load("haarcascade_frontalface_alt.xml"))
		cout << "No se puede abrir clasificador." << endl;

	cvtColor(imagen, gray, COLOR_BGR2GRAY);
	equalizeHist(gray, dest);

	vector<Rect> rect;
	detector.detectMultiScale(dest, rect);

	for (Rect rc : rect)
	{
		rectangle(imagen,
			Point(rc.x, rc.y),
			Point(rc.x + rc.width, rc.y + rc.height),
			CV_RGB(255, 4, 0), 2);
	}

	imshow("Imagen original", imagen);
	
	
	waitKey(0);
	return 1;
}