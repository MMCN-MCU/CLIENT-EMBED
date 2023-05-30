g++ -std=c++14 \
-I/opt/homebrew/Cellar/opencv/4.7.0_4/include/opencv4 \
-I/opt/homebrew/Cellar/boost/1.81.0_1/include \
-L/opt/homebrew/Cellar/opencv/4.7.0_4/lib \
-L/opt/homebrew/Cellar/boost/1.81.0_1/lib \
-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs \
-lboost_system \
main.cpp -o main
