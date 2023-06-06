#include <opencv2/opencv.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include <iostream>
#include <vector>
#include <string>

using boost::asio::ip::tcp;
using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

    // 입력이 잘못됨
    if(argc != 3) {
        cerr << "잘못된 입력이 들어왔습니다!" << endl;
    }

    VideoCapture capture(0);

    // 웹캠을 열 수가 없음
    if(!capture.isOpened()) {
        cerr << "웹 캠 정보를 받아올 수 없습니다!" << endl;
    }

    Mat frame;

    // [video frame] 저장 위한 Matrix 정의 + compress된 frame 저장 위한 buffer 정의 + compression 위한 parameter 정의
    vector<uchar> buffer;
    vector<int> params;

    // params에 데이터 저장
    params.push_back(IMWRITE_JPEG_QUALITY);
    params.push_back(75);

    // window 열기
    namedWindow("Webcam Stream", WINDOW_AUTOSIZE); // Create a window named "Webcam Stream"

    try {

        //*** tcp로 host와 port resolve ***//

        // io_service object가 I/O service 제공
        boost::asio::io_service io_service;

        // resolver object가 host와 port resolve
        tcp::resolver resolver(io_service);

        // host와 port resolve 하기 위한 query 생성
        tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);

        // host와 port resolve
        tcp::resolver::iterator iterator = resolver.resolve(query);


        //*** socket 열기 ***//

        // socket 생성
        tcp::socket socket(io_service);

        // host로 connection 연결
        boost::asio::connect(socket, iterator);

        // frame 전송 확인 위한 변수
        int cnt = 0;

        while(true) {
            // video frame을 capture 함
            capture >> frame;

            // frame 전송 카운트 계산
            cout << "sending frame " << cnt << endl;
            cnt = (cnt + 1) % 4;

            // video frame이 비어 있다면 연결 안되있는 거임 -> break 걸고 영상 송출 탈출
            if(frame.empty()) {
                cerr << "Video camera is disconnected" << endl;
                break;
            }

            //*** 송출되는 영상 확인 ***//

            // Capture 된 frame을 생성된 window에서 보여주기 + 종료를 위한 waitKey() 함수 호출
            imshow("Webcam Stream", frame);
            waitKey(1);

            // Frame -> JPEG로 compress
            imencode(".jpg", frame, buffer, params);

            //*** buffer의 전송 사이즈 정의 + 전송 ***//
            
            // buffer 사이즈를 network byte order로 변경
            uint32_t size = htonl(buffer.size());

            // buffer 사이즈를 socket 에 작성
            boost::asio::write(socket, boost::asio::buffer((const char*)&size, sizeof(uint32_t)));

            // buffer 데이터를 socket으로 전송
            boost::asio::write(socket, boost::asio::buffer(buffer.data(), buffer.size()));
        }
        

    } catch(exception & e) {
        cerr << e.what() << endl;
    }

    capture.release();

    return 0;
}