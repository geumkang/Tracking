/*
#pragma warning(disable:4996)
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

// Convert to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()

void onmouse(int event, int x, int y, int flags, void* param);
bool isSelected = false;
bool isFirstDrawing = true;
vector<Rect2d> boundary;

int main(int argc, char **argv)
{
	// List of tracker types in OpenCV 3.4.1
	string trackerTypes[8] = { "BOOSTING", "MIL", "KCF", "TLD","MEDIANFLOW", "GOTURN", "MOSSE", "CSRT" };

	// Create a tracker
	string trackerType = trackerTypes[7];

	//vector<Ptr<Tracker>> tracker;
	Ptr<MultiTracker> multiTracker = MultiTracker::create();
	// Read video
	VideoCapture video("4.mp4");

	// Exit if video is not opened
	if (!video.isOpened())
	{
		cout << "Could not read video file" << endl;
		return 1;
	}

	Mat frame;

	bool playVideo = true;
	bool isTracking = false;

	while (video.isOpened()) {
		if (isTracking) {
			video >> frame;
			if (frame.empty()) break;

			double timer = (double)getTickCount();
			vector<bool> trackingUpdated(boundary.size());

			multiTracker->update(frame, boundary);
			for (unsigned i = 0; i < multiTracker->getObjects().size(); i++)
			{
				rectangle(frame, multiTracker->getObjects()[i], 1, 2, 1);
			}
			/*
			// Update the tracking result
			for (int i = 0; i < boundary.size(); i++)
				trackingUpdated[i] = tracker[i]->update(frame, boundary[i]);


			// Calculate Frames per second (FPS)
			float fps = getTickFrequency() / ((double)getTickCount() - timer);

			for (int i = 0; i < boundary.size(); i++) {
				if (trackingUpdated[i])
				{
					rectangle(frame, boundary[i], Scalar(255, 0, 0), 2, 1);
				}
				else
				{
					stringstream ss;
					ss << (int)(i+1);
					putText(frame, ss.str() + " Item's Tracking failure detected", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
				}
			}
			// Display tracker type on frame
			putText(frame, trackerType + " Tracker", Point(100, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

			// Display FPS on frame
			stringstream ss;
			ss << (int)(fps);
			putText(frame, "FPS : " + ss.str(), Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);
			
			imshow("Tracking", frame);
		}
		else if (playVideo) {
			video >> frame;
			if (frame.empty()) break;
			imshow("Tracking", frame);
		}
		else {
			imshow("Tracking", frame);
			Mat tempImg = frame.clone();
			//selectROI("Tracking", tempImg, true, false);
			setMouseCallback("Tracking", onmouse, &tempImg);
			for (int i = 0; i < boundary.size(); i++)
				rectangle(tempImg, boundary[i], Scalar(255, 0, 0), 2, 1);
			imshow("Tracking", tempImg);
		}

		char key = waitKey(1);
		if (key == 'p') {
			if (!playVideo) {
				//tracker.clear();
				for (int i = 0; i < boundary.size(); i++) {
					multiTracker->add(TrackerCSRT::create(), frame, boundary[i]);
					/*
					if (trackerType == "BOOSTING")
						tracker.push_back(TrackerBoosting::create());
					if (trackerType == "MIL")
						tracker.push_back(TrackerMIL::create());
					if (trackerType == "KCF")
						tracker.push_back(TrackerKCF::create());
					if (trackerType == "TLD")
						tracker.push_back(TrackerTLD::create());
					if (trackerType == "MEDIANFLOW")
						tracker.push_back(TrackerMedianFlow::create());
					if (trackerType == "GOTURN")
						tracker.push_back(TrackerGOTURN::create());
					if (trackerType == "MOSSE")
						tracker.push_back(TrackerMOSSE::create());
					if (trackerType == "CSRT")
						tracker.push_back(TrackerCSRT::create());

					tracker[i]->init(frame, boundary[i]);
					
				}
				isTracking = true;
			}
			else {
				boundary.clear();
				isTracking = false;
			}
			playVideo = !playVideo;
		}
	}
}

void onmouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		if (isFirstDrawing) {
			boundary.push_back(Rect2d(x, y, 0, 0));
			isFirstDrawing = false;
		}
	}
	else if (event == CV_EVENT_MOUSEMOVE) {
		if (!isFirstDrawing) {
			Rect2d temp = boundary[boundary.size() - 1];
			temp.width = x - temp.x;
			temp.height = y - temp.y;
			boundary[boundary.size() - 1] = temp;
		}
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		Rect2d temp = boundary[boundary.size() - 1];
		temp.width = x - temp.x;
		temp.height = y - temp.y;
		boundary[boundary.size() - 1] = temp;

		isFirstDrawing = true;
	}
	else if (event == CV_EVENT_RBUTTONDOWN)
	{
		isSelected = true;
	}
}
*/