#include <pthread.h>



#include <unistd.h>

#include <string>
#include <list>
#include <mutex>
#include <vector>

class ScreenCapture;

class ScreenShotJob
{
private:
  ScreenShotJob() = delete;
  ScreenShotJob& operator=(const ScreenShotJob& RHS) = delete;

public:
  ScreenShotJob(ScreenCapture* tpt) : m_screenCapture(tpt) { }
  ScreenShotJob(const ScreenShotJob& copy) : m_screenCapture(copy.m_screenCapture) { }
  ~ScreenShotJob() {}

  inline bool operator==(const ScreenShotJob& RHS) const
  {
    return(m_screenCapture == RHS.m_screenCapture);
  }

public:
  uint64_t Timed();

private:
  ScreenCapture* m_screenCapture;
};

class ScreenCapture {
private:
  ScreenCapture(const ScreenCapture&) = delete;
  ScreenCapture& operator=(const ScreenCapture&) = delete;


  static void* StartThread(ScreenCapture* pObject);

public:
  ScreenCapture() = default;
  ~ScreenCapture();

  virtual const std::string Initialize();

  void Run();

  uint32_t uploadScreenCapture();

  bool getScreenShot();
private:
  std::mutex m_callMutex;


  pthread_t m_hThreadInstance;


  class TimedInfo {
  public:
    TimedInfo() = delete;

    inline TimedInfo(const  ScreenShotJob& contents)
        : m_Info(contents)
    {
    }

    inline TimedInfo(ScreenShotJob&& contents)
        : m_Info(std::move(contents))
    {
    }

    inline TimedInfo(const TimedInfo& copy)
        : m_Info(copy.m_Info)
    {
    }

    inline TimedInfo(TimedInfo&& copy) noexcept
        : m_Info(std::move(copy.m_Info))
    {
    }

    inline ~TimedInfo()
    {
    }

    TimedInfo& operator=(const TimedInfo& RHS) = delete;

    TimedInfo& operator=(TimedInfo&& RHS) = delete;

    inline ScreenShotJob& Content()
    {
      return (m_Info);
    }

  private:
    ScreenShotJob m_Info;
  };

  typedef TimedInfo TimeInfoBlocks;
  typedef typename std::list<TimeInfoBlocks> SubscriberList;

  SubscriberList m_PendingQueue;
};

const std::string ScreenCapture::Initialize()
{
  pthread_create(&m_hThreadInstance, nullptr, (void* (*)(void*))ScreenCapture::StartThread, this);

  return { };
}

ScreenCapture::~ScreenCapture()
{
  void* l_Dummy;
  ::pthread_join(m_hThreadInstance, &l_Dummy);
}

void* ScreenCapture::StartThread(ScreenCapture* cClassPointer)
{

  cClassPointer->Run();

  return nullptr;
}

void  ScreenCapture::Run()
{
  while ((m_PendingQueue.empty() == false)) {
    TimedInfo info(std::move(m_PendingQueue.front()));

    m_PendingQueue.pop_front();

    info.Content().Timed();

  }
}

uint32_t ScreenCapture::uploadScreenCapture()
{
  std::lock_guard<std::mutex> guard(m_callMutex);

  m_PendingQueue.push_back(std::move(ScreenShotJob( this)));

  return 0;
}

uint64_t ScreenShotJob::Timed()
{
  m_screenCapture->getScreenShot();

  printf("--\n");
  fflush(stdout);
  return 0;
}

bool ScreenCapture::getScreenShot()
{
  std::vector<unsigned char> png_data;
}

int main() {
  ScreenCapture screenCapture;

  screenCapture.Initialize();



  screenCapture.uploadScreenCapture();


  sleep(1);

  printf("---\n");
  fflush(stdout);
  return 0;
}
