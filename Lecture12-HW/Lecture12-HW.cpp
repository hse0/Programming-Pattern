#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    int count = 0;
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    chrono::steady_clock::time_point prev_end = chrono::steady_clock::now();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    int delay_time_ms = 0;

    // 처음 시작 전에 1초 대기
    this_thread::sleep_for(chrono::seconds(1));

    while (count < 10)
    {
        // 시작 시간과 끝 시간을 기록합니다.
        prev_end = end;
        end = chrono::steady_clock::now();

        // 시간 차를 구합니다.
        chrono::steady_clock::duration diff = end - prev_end;
        delay_time_ms = chrono::duration_cast<chrono::milliseconds>(diff).count();

        // 출력합니다.
        count++;
        cout << count << "초...   : " << delay_time_ms << "ms" << endl;

        // 다음 루프를 위해 시작 시간을 업데이트
        start = chrono::steady_clock::now();

        // 1초 대기 (1초를 유지하려는 목적)
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
