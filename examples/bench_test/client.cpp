#include <iostream>
#include <chrono>
#include "paxos++/client.hpp"


class Timer
{
public:
  Timer() : m_begin(std::chrono::high_resolution_clock::now()) {}
  void reset() { m_begin = std::chrono::high_resolution_clock::now(); }
  //默认输出毫秒
  int64_t elapsed() const
  {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
  }
  //微秒
  int64_t elapsed_micro() const
  {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
  }
  //纳秒
  int64_t elapsed_nano() const
  {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
  }
  //秒
  int64_t elapsed_seconds() const
  {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
  }
  //分
  int64_t elapsed_minutes() const
  {
    return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - m_begin).count();
  }
  //时
  int64_t elapsed_hours() const
  {
    return std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now() - m_begin).count();
  }
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;

}; // timer

int main ()
{
   paxos::client client;
   client.add ("127.0.0.1", 1337);
   constexpr int COUNTS=100000;
   int i = 0, j=COUNTS;
   Timer timer;
   while((j--)){
       std::future <std::string> future = client.send ("foo");
       assert (future.get () == "bar");
        i++;
   }
   double ops=COUNTS/((double)timer.elapsed_seconds());
   std::cout<<ops<<std::endl;
}